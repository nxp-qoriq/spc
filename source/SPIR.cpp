/* =====================================================================
 *
 * The MIT License (MIT)
 * Copyright 2018 NXP
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * File Name : SPIR.cpp
 *
 * ===================================================================*/

#include "SPIR.h"
#include "logger.hpp"

uint32_t CIR::currentUniqueName = 0;

/* ------------------------- CreateIR functions ---------------------------*/
void CIR::createIR(CTaskDef* newTask)
{
    this->task = newTask;
    this->createIR();
}

void CIR::setDebug(bool debug)
{
	fDebug = debug;
}

/*Creates IR. This function analyzes the taskDef structure, and creates an
IR instruction. The function is the second stage in the compilation process
(after parsing, and before creating pcode and dumping the assembly code*/
void CIR::createIR ()
{
    uint32_t i, j, count = 0;
    /*Create IR for each protocol*/
    for (i = 0; i < task->protocols.size(); i++)
    {
        CExecuteCode executeCode  = task->protocols[i].executeCode;
        if (executeCode.executeSections.size())
        {
            status.currentProtoIndex = count;

            /*Insert initial label*/
            CLabel labelP("START_"+task->protocols[i].name);
            CProtocolIR protoIR(labelP, task->protocols[i]);
            protoIR.ir = this;
            CStatement statement;
            statement.createLabelStatement(labelP);
            protoIR.statements.push_back(statement);

            // For each protocol name, find corresponding ProtoType
            ProtoType pt;
            for ( uint32_t k = 0; k < protoIR.protocol.prevproto.size(); k++ )
            {
            	//try to find HW protocol
            	pt = findSpecificProtocol(protoIR.protocol.prevproto[k], protoIR.protocol.line);
            	if (pt == PT_INVALID) {
            		//try to find SP protocol
            		if (findSpProtocol(protoIR.protocol.prevproto[k], protoIR.protocol.line)) {
            			pt = PT_SP_PROTOCOL;
            		} else {
            			//protocol not found
            			throw CGenericErrorLine (ERR_UNSUPPORTED_PROTOCOL, protoIR.protocol.line, protoIR.protocol.prevproto[k]);
            		}
            	}
                protoIR.protocol.prevType.push_back(pt);
            }

            protocolsIRs.push_back(protoIR);

            /*Add any special code before user sections if needed*/
            initIRProto(protocolsIRs[count].statements);

            /*Organize sections before parsing them*/
            uniteSections (executeCode.executeSections);

            /*Create IR instruction for each section in the protocol*/
            std::vector< CExecuteSection> sections=executeCode.executeSections;
            for (j = 0; j < sections.size(); j++)
                createIRSection(sections[j], protocolsIRs[count]);
            /*Mark endsection statement of last statement.
              Needed for final jump and to decide on hb advancement*/
            protocolsIRs[count].statements.back().flags.lastStatement = 1;
            count++;
        }
    }

    /*dump IR*/
    if (outFile && fDebug)
        dumpEntireIR();

    /*revise*/
    reviseEntireIR();
    if (outFile && fDebug)
        *outFile << "-------------------------------" << std::endl
                 << "---------Revised code:---------" << std::endl
                 << "-------------------------------" << std::endl;

    if (outFile)
        dumpEntireIR();
}

/*Add code that should appear before the 'before' and 'after' sections*/
void CIR::initIRProto(std::vector <CStatement> &statements)
{
    ProtoType pt = protocolsIRs[status.currentProtoIndex].protocol.prevType[0];

    //NOTE: Removed workaround on DPAA1 since not applicable on DPAA2
    //Workaround for HW issue 19895
}

/*Check if there are multiple 'before' or 'after' sections. Currently
 multiple sections are not supported, in the future they might be united
 in this function into one section (see commented code below)
 If no before action exists create a before section*/
void CIR::uniteSections (std::vector< CExecuteSection> &executeSections)
{
    bool foundBefore = 0, foundAfter = 0;
    uint32_t i       = 0;
    CExecuteSection *firstBefore;
    ProtoType pt = protocolsIRs[status.currentProtoIndex].protocol.prevType[0];
    while (i < executeSections.size())
    {
        if (executeSections[i].type == BEFORE)
        {
            /*Before not allowed when prevproto is otherl3/otherl4*/
            if (pt == PT_OTHER_L3 || pt == PT_OTHER_L4)
                throw CGenericErrorLine(ERR_BEFORE_OTHER_PREV,
                    executeSections[i].line,
                    protocolsIRs[status.currentProtoIndex].protocol.prevproto[0]);

            /*'before' not allowed after the 'after' element*/
            if (foundAfter)
                  throw CGenericErrorLine (ERR_AFTER_BEFORE_BEFORE,
                                           executeSections[i].line);
            /*Multiple before elements*/
            if (foundBefore)
            {
                throw CGenericErrorLine (ERR_MULTIPLE_BEFORE,
                                         executeSections[i].line);
                 /* This code unites all befores to one section
                 (with only one CLM) - disabled for the time being
                 std::vector<CExecuteExpression>::iterator dEnd =
                    firstBefore->executeExpressions.end();
                std::vector<CExecuteExpression>::iterator sBegin =
                    executeSections[i].executeExpressions.begin();
                std::vector<CExecuteExpression>::iterator sEnd =
                    executeSections[i].executeExpressions.end();

                firstBefore->executeExpressions.insert (dEnd, sBegin, sEnd);
                executeSections.erase(executeSections.begin()+i);
                i--;    */
            }
            foundBefore = 1;
            firstBefore = &(executeSections[i]);
        }
        else if (executeSections[i].type == AFTER)
        {
            /*Insert dummy before section unless the previous protocol is
              otherl3 or otherl4*/
            if (!foundBefore)
            {
                if (pt != PT_OTHER_L3 && pt != PT_OTHER_L4)
                {
                    executeSections.insert(executeSections.begin(),
                                           CExecuteSection(BEFORE));
                    i++;
                }
                foundBefore = 1;
                continue;
            }
            /*Multiple after elements*/
            if (foundAfter)
                throw CGenericErrorLine (ERR_MULTIPLE_AFTER,
                                         executeSections[i].line);
            foundAfter = 1;
        }
        i++;
    }
}

void CIR::createIRSection (CExecuteSection section, CProtocolIR& pIR)
{
    /*Find name of current protocol and headerSize*/
    switch(section.type)
    {
        case BEFORE:
            status.currentAfter = 0;
            /*The prevHeaderSize in set the defaultHeaderSize which
              is interperted in yacc differently in the before/after sections*/
            createIRExprValue("$defaultHeaderSize", pIR.prevHeaderSize,
                              section.line, 0);
            break;
        case AFTER:
            status.currentAfter = 1;
            createIRExprValue("$defaultHeaderSize", pIR.headerSize,
                              section.line, 0);

            break;
    }

    /*Create IR for each expression*/
    createIRExpressions(section, pIR.statements);

    /*Insert final section statement after 'before' and 'after' sections
      - needed for CLM, to update WO and HB*/
    CStatement sStatement;
    sStatement.createSectionEndStatement();
    sStatement.flags.sectionType = section.type;
    switch(section.type)
    {
          /*After the 'before' section we move to the next protocol,
          by modifying W0 and adding the EFBEFORE instruction*/
        case BEFORE:
            sStatement.expr     = pIR.prevHeaderSize->newDeepCopy();
            sStatement.label    = CLabel(PT_RETURN);
            break;
        /*Goto end parse or return hxs after the 'after' section*/
        case AFTER:
            sStatement.expr                 = pIR.headerSize->newDeepCopy();
            sStatement.label                = CLabel(PT_END_PARSE);
            break;
    }

    pIR.statements.push_back(sStatement);
}

/*This functions creates statements for a section and inserts them in the
  end of the 'statements' vector. Note: this function should only be used
  for the expression inside the sections and not to analyze the section
  type itself (before, after, etc.)*/
void CIR::createIRExpressions (CExecuteSection section, std::vector <CStatement> &statements)
{
    for (unsigned int i=0; i < section.executeExpressions.size(); i++)
    {
        CExecuteExpression ee = section.executeExpressions[i];
        if      (ee.type == IT_ACTION)
            createIRAction (ee.actionInstr, statements);
        else if (ee.type == IT_ASSIGN)
            createIRAssign (ee.assignInstr, statements);
        else if (ee.type == IT_IF)
            createIRIf     (ee.ifInstr,     statements);
        else if (ee.type == IT_LOOP)
            createIRLoop     (ee.loopInstr, statements);
        else if (ee.type == IT_INLINE)
            createIRInline (ee.inlineInstr, statements);
        else if (ee.type == IT_SWITCH)
            createIRSwitch (ee.switchInstr, statements);
		else if (ee.type == IT_GOSUB)
			createIRGosub (ee.gosubInstr, statements);
		else if (ee.type == IT_SETRESETFAF)
			createIRSetresetfaf (ee.setresetfafInstr, statements);
    }
}

/*Create IR instructions for the switch element*/
void CIR::createIRSwitch (CExecuteSwitch switchElem, std::vector<CStatement> &statements)
{
    std::vector <CStatement>      executeStatments;
    std::vector <CExecuteSection> sections;
    uint8_t countInTable = 0;
    /*Switch with no case*/
    if (switchElem.cases.size() == 0)
        throw CGenericErrorLine(ERR_SWITCH_NO_CASE, switchElem.line,
                                switchElem.expr);
    /*finalLStatement is the last label related to the switch,
    we'll use finalGStatement to jump there either when we finished checking
    all cases (+default) or when we found a case and executed the
    elements inside it*/
    CStatement switchStatement,trueLStatement,finalGStatement,finalLStatement;
    finalLStatement.createLabelStatement(createUniqueName());
    finalGStatement.createGotoStatement(finalLStatement.label);

    for (unsigned int i=0; i<switchElem.cases.size(); i++)
    {
        uint64_t intValue;
        /*We currently support only int in cases*/
        if (!stringToInt(switchElem.cases[i].value, intValue,
                         switchElem.cases[i].line))
            throw CGenericErrorLine(ERR_CASE_NO_INT, switchElem.cases[i].line,
                                    switchElem.cases[i].value);
        /*We will jump to the trueLStatement label only if the value
        is in the correct range, the label will appear after all cases*/
        trueLStatement.createLabelStatement(createUniqueName());

        /*OPTION1: If value is larger than 16 bit we turn this specific
                   case into an ifInstr*/
        if ((intValue & 0xFFFFFFFFFFFF0000ull) != 0)
        {
            /*If switch table exists add it to statements and initialize it*/
            if (countInTable)
            {
                statements.push_back(switchStatement);
                countInTable = 0;
            }
            CStatement statement1;
            statement1.createIfGotoStatement(trueLStatement.label,
                                             switchElem.line);
            CExecuteIf ifInstr1(switchElem.cases[i].value + "== (" +
                                switchElem.expr +  ")");
            createIRExprValue(ifInstr1.expr, statement1.expr,
                              switchElem.cases[i].line);
            statements.push_back(statement1);
        }

        /*OPTION 2: If we have a max value we turn this
                    specific case into two ifs */
        else if (!switchElem.cases[i].maxValue.empty())
        {
            /*If switch table exists add it to statements and initialize it*/
            if (countInTable)
            {
                statements.push_back(switchStatement);
                countInTable = 0;
            }
            CStatement statement1, statement2, falseLStatement, trueGStatement;
            CExecuteIf ifInstr1("(" + switchElem.cases[i].value + ") gt ("
                                    + switchElem.expr +  ")");
            CExecuteIf ifInstr2("(" + switchElem.cases[i].maxValue + ") lt ("
                                    + switchElem.expr +  ")");
            /*This falseLStatement label will take us back to the switch to
            check more cases.*/
            falseLStatement.createLabelStatement(createUniqueName());
            trueGStatement.createGotoStatement  (trueLStatement.label);
            /*check if expr value is smaller than allowed value*/
            createIRExprValue(ifInstr1.expr, statement1.expr,
                              switchElem.cases[i].line);
            statement1.createIfGotoStatement(falseLStatement.label, NO_LINE);
            /*check if expr value is larger than max value*/
            createIRExprValue(ifInstr2.expr, statement2.expr,
                               switchElem.cases[i].line);
            statement2.createIfGotoStatement(falseLStatement.label, NO_LINE);
            /*Insert both ifs, if we failed in any of them we will jmp
              to falseLStatement, otherwise we will reach trueLStatement*/
            statements.push_back(statement1);
            statements.push_back(statement2);
            statements.push_back(trueGStatement);
            statements.push_back(falseLStatement);
        }
        else /*OPTION3: Create a switch table*/
        {
            countInTable++;
            if (countInTable == 1) /*new table*/
            {
                switchStatement.newSwitchStatement(switchElem.line);
                createIRExprValue (switchElem.expr,
                        switchStatement.expr, switchElem.line);
                if (switchStatement.expr->isCond())
                    throw CGenericErrorLine(ERR_UNEXPECTED_COND_SWITCH,
                                            switchElem.line, switchElem.expr);
            }
            /*insert values and labels to table*/
            switchStatement.switchTable->values.push_back((uint16_t)intValue);
            switchStatement.switchTable->labels.push_back(trueLStatement.label);
            /*Max table size is four (according to assembly case instruction*/
            if (countInTable == 4 || i+1 == switchElem.cases.size())
            {
                statements.push_back(switchStatement);
                countInTable = 0;
            }
        }

        /*If this case is true we will reach this label and execute
        the case's instructions*/
        executeStatments.push_back(trueLStatement);
        createIRExpressions(switchElem.cases[i].ifCase, executeStatments);
        /* After the case skip the rest of the statements related to
           the switch (as if there was a 'break' in c, or 'last' in perl*/
        executeStatments.push_back(finalGStatement);
    }   /*Finished checking cases*/

    /*If we'll reach the end of the switch without jumping we should execute
      the default case, and skip the following statements for 'true' cases*/
    if (switchElem.defaultCaseValid)
        createIRExpressions(switchElem.defaultCase, statements);
    statements.push_back(finalGStatement);
    /*Insert all the labels, and statements which should be executed
    if one of the cases was true. */
    for (unsigned int i=0; i<executeStatments.size(); i++)
        statements.push_back(executeStatments[i]);
    /*Last label related to switch, jump here when done*/
    statements.push_back(finalLStatement);
}

void CIR::createIRInline (CExecuteInline inInstr, std::vector<CStatement> &statements)
{
    CStatement  inlineStatement;
    inlineStatement.createInlineStatement(inInstr.data, inInstr.line);
    statements.push_back(inlineStatement);
}

void CIR::createIRIf (CExecuteIf ifInstr, std::vector<CStatement> &statements)
{
    CStatement  statement, gStatement, lstatement1, lstatement2, lstatement3;
    CObject     object;
    std::string newName, label1Name, label2Name, label3Name, temp;

	if (ifInstr.expr != "")
	{
		//<if expr="$">

		/*No if true*/
		if (!ifInstr.ifTrueValid)
			throw CGenericErrorLine(ERR_IF_NO_TRUE, ifInstr.line, ifInstr.expr);
		createIRExprValue (ifInstr.expr, statement.expr, ifInstr.line);
		if (!statement.expr->isCond())
			throw CGenericErrorLine(ERR_EXPECTED_COND, ifInstr.line, ifInstr.expr);

		/*Only an ifTrue label*/
		if (!ifInstr.ifFalseValid)
		{
			lstatement1.createLabelStatement(createUniqueName());
			statement.createIfNGotoStatement(lstatement1.label, ifInstr.line);
			statements.push_back(statement);
			createIRExpressions(ifInstr.ifTrue, statements);
			statements.push_back(lstatement1);
		}

		/*An ifTrue and ifFalse*/
		else if (ifInstr.ifFalseValid)
		{
			lstatement1.createLabelStatement(createUniqueName());
			statement.createIfGotoStatement(lstatement1.label, ifInstr.line);
			statements.push_back(statement);
			createIRExpressions(ifInstr.ifFalse, statements);
			lstatement2.createLabelStatement(createUniqueName());
			gStatement.createGotoStatement(lstatement2.label);
			statements.push_back(gStatement);
			statements.push_back(lstatement1);
			createIRExpressions(ifInstr.ifTrue, statements);
			statements.push_back(lstatement2);
		}
	}
	else
	{
		if (ifInstr.faf != "")
		{
			//<if faf="">

			if (ifInstr.ifTrueValid && ifInstr.ifFalseValid)
			{
				lstatement1.createLabelStatement(createUniqueName());
				statement.createIfFafGotoStatement(lstatement1.label, ifInstr.faf, ifInstr.line);
				statements.push_back(statement);
				createIRExpressions(ifInstr.ifFalse, statements);
				lstatement2.createLabelStatement(createUniqueName());
				gStatement.createGotoStatement(lstatement2.label);
				statements.push_back(gStatement);
				statements.push_back(lstatement1);
				createIRExpressions(ifInstr.ifTrue, statements);
				statements.push_back(lstatement2);
			}
			else if (ifInstr.ifTrueValid)
			{
				lstatement1.createLabelStatement(createUniqueName());
				statement.createIfFafGotoStatement(lstatement1.label, ifInstr.faf, ifInstr.line);
				statements.push_back(statement);
				lstatement2.createLabelStatement(createUniqueName());
				gStatement.createGotoStatement(lstatement2.label);
				statements.push_back(gStatement);
				statements.push_back(lstatement1);
				createIRExpressions(ifInstr.ifTrue, statements);
				statements.push_back(lstatement2);
			}
			else if (ifInstr.ifFalseValid)
			{
				lstatement1.createLabelStatement(createUniqueName());
				statement.createIfFafGotoStatement(lstatement1.label, ifInstr.faf, ifInstr.line);
				statements.push_back(statement);
				createIRExpressions(ifInstr.ifFalse, statements);
				statements.push_back(lstatement1);
			}
		}
	}
}

void CIR::createIRLoop (CExecuteLoop loopInstr, std::vector<CStatement> &statements)
{
    CStatement  statement, gStatement, lstatement1, lstatement2;
    std::string newName, label1Name, label2Name, label3Name, temp;

    lstatement1.createLabelStatement(createUniqueName());
    statements.push_back(lstatement1);
    createIRExprValue (loopInstr.expr, statement.expr, loopInstr.line);
    if (!statement.expr->isCond())
        throw CGenericErrorLine(ERR_EXPECTED_COND, loopInstr.line, loopInstr.expr);
    lstatement2.createLabelStatement(createUniqueName());
    statement.createIfNGotoStatement(lstatement2.label, loopInstr.line);
    statements.push_back(statement);
    createIRExpressions(loopInstr.loopBody, statements);
    gStatement.createGotoStatement(lstatement1.label);
    statements.push_back(gStatement);
    statements.push_back(lstatement2);
}

void CIR::createIRGosub (CExecuteGosub gosubInstr, std::vector<CStatement> &statements)
{
	CStatement  gStatement;

	gStatement.createGosubStatement(gosubInstr.name);
	statements.push_back(gStatement);
}

void CIR::createIRSetresetfaf (CExecuteSetresetfaf setresetfafInstr, std::vector<CStatement> &statements)
{
	CStatement  gStatement;

	if (setresetfafInstr.faf)
	{
		if (setresetfafInstr.set)
			gStatement.createSetFafStatement(setresetfafInstr.name);
		else
			gStatement.createResetFafStatement(setresetfafInstr.name);
	}
	statements.push_back(gStatement);
}

void CIR::createIRAction (CExecuteAction action, std::vector<CStatement> &statements)
{
    CStatement gStatement, eStatement;
    std::string actionTypeName = action.type;
    ProtoType pt = PT_INVALID;

    if (action.type == "exit")
    {
        /*either exit to a specific protocol or return to HXS*/
        if (action.nextproto.length() != 0) {

			//try to find HW protocol
			pt = findProtoLabel(action.nextproto, action.line);
			if (pt != PT_INVALID) {
				gStatement.createGotoStatement(pt);
			}
			else {
	        	//try to find SP protocol
				std::string labelName = findSpProtoLabel(action.nextproto, action.line);
	        	if (labelName.length() > 0) {
	        		gStatement.createGotoStatement(labelName);
	        	}
	        	else {
	        		//protocol not found
	        		throw CGenericErrorLine (ERR_UNSUPPORTED_PROTOCOL, action.line, action.nextproto);
	        	}
			}
        }
        else {
            pt = PT_RETURN;
            gStatement.createGotoStatement(pt);
        }

        /* we should update HB and WO before exiting and therefore we
           add the flag and header size*/
        gStatement.flags.hasENode = 1;
        if (status.currentAfter)
            gStatement.expr = protocolsIRs[status.currentProtoIndex].
                                headerSize->newDeepCopy();
        else
            gStatement.expr = protocolsIRs[status.currentProtoIndex].
                                prevHeaderSize->newDeepCopy();

        /*Update advance option*/
        if (action.advance == "")
        {
            if (pt == PT_RETURN || pt == PT_END_PARSE)
                action.advance = "no";
            else
                action.advance = "yes";
        }

        if (action.advance == "yes")
            gStatement.flags.advanceJump = 1;
        else if (action.advance == "no")
            gStatement.flags.advanceJump = 0;
        else
            throw CGenericErrorLine (ERR_UNKNOWN_ADVANCE_OPTION,
                                     action.line, action.advance);

        /*Check for errors*/
        if (!gStatement.flags.advanceJump && (pt == PT_NEXT_ETH ||
                                              pt == PT_NEXT_IP ||
											  pt == PT_NEXT_TCP ||
											  pt == PT_NEXT_UDP))
            throw CGenericErrorLine(ERR_ADVANCE_REQUIRED, action.line,
                                    action.advance);
        if (gStatement.flags.advanceJump && (pt == PT_RETURN))
            throw CGenericErrorLine(ERR_ADVANCE_NOT_ALLOWED,
                                    action.line, action.advance);

        //NOTE: Removed workaround on DPAA1 since not applicable on DPAA2
        //Workaround for HW bug 19894

        statements.push_back(gStatement);
    }
    else
        throw CGenericErrorLine (ERR_UNSUPPORTED_ACTION,
                                 action.line, actionTypeName);
}

void CIR::createIRAssign (CExecuteAssign assign, std::vector <CStatement> &statements)
{
    CStatement  statement;

    /*Special treatment for headerSize, no statements are executed,
      only the internal value is modified*/
    if (insensitiveCompare(assign.name, "$headerSize"))
    {
        if (status.currentAfter)
            createIRExprValue(assign.value,
                protocolsIRs[status.currentProtoIndex].headerSize,
                assign.line, 1);
        else
            createIRExprValue(assign.value,
                protocolsIRs[status.currentProtoIndex].prevHeaderSize,
                assign.line, 1);
        return;
    }

    // In presence of fwoffset, create a new assignment statement
    // that sets $WO to fwoffset expression
    if ( !assign.fwoffset.empty() ) {
        CExecuteAssign assignWO( assign );
        assignWO.name     = "$WO";
        assignWO.value    = assignWO.fwoffset;
        assignWO.fwoffset = "";

        createIRAssign( assignWO, statements );
    }

    statement.newAssignStatement(assign.line);
    /*Create left side*/
    try
    {
    	createIRExprValue(assign.name, statement.expr->dyadic.left, assign.line);
    }
	catch (CGenericErrorLine& ex)
	{
		//ignore this <assign-variable name because is not supported
		LOG( logger::WARN ) << "Variable name in <assign-variable> tag is not supported: " << ex.getErrorMsg() << std::endl;
		statement.deleteStatement();
		return;
	}

    /*Check that this is a valid assign statement*/
    if (statement.expr->dyadic.left->type != EOBJREF ||
        (statement.expr->dyadic.left->objref->type != OB_RA &&
         statement.expr->dyadic.left->objref->type != OB_WO))
        throw CGenericErrorLine (ERR_UNALLOWED_LVALUE_ASSIGN,
                                 assign.line, assign.name);

    /*Create right side*/
    try
    {
    	createIRExprValue(assign.value, statement.expr->dyadic.right, assign.line);
    }
	catch (CGenericErrorLine& ex)
	{
		//ignore this <assign-variable value because is not supported
		LOG( logger::WARN ) << "Variable value in <assign-variable> tag is not supported: " << ex.getErrorMsg() << std::endl;
		statement.deleteStatement();
		return;
	}

	if (statement.expr->dyadic.right->isCond())
        throw CGenericErrorLine(ERR_UNEXPECTED_COND_ASSIGN, assign.line,
                                assign.value);
    statements.push_back(statement);

    // In presence of fwoffset, create a new assignment statement
    // that restores $WO to be zero
    if ( !assign.fwoffset.empty() ) {
        CExecuteAssign assignWO( assign );
        assignWO.name     = "$WO";
        assignWO.value    = "0";
        assignWO.fwoffset = "";

        createIRAssign( assignWO, statements );
    }
}

void CIR::createIRVariable (std::string name, CObject *object, int line)
{
    std::string newName = stripDollar (name);

    /*First check predefined variable(s)*/
    if (insensitiveCompare(newName, "prevprotoOffset"))
        findPrevprotoOffset(object, line);
    /*Then check parse array*/
    else if (RA::Instance().findNameInRA(newName, object->typeRA,
                                         object->location, line))
    {
        object->type = OB_RA;
    }
    else if (insensitiveCompare(newName, "WO"))
    {
        object->type = OB_WO;
    }
    else
        throw CGenericErrorLine (ERR_UNRECOGNIZED_OBJECT, line, name);

    /*check for errors*/
    if (object->location.end - object->location.start > 7)
        throw CGenericErrorLine (ERR_VAR_TOO_LARGE, line, name);
}

void CIR::createIRVariableAccess (std::string name, CObject *object, int line)
{
    std::string newName = stripDollar (name);
    uint32_t start, size;
    getBufferInfo (newName, start, size, line, 0);
    if (insensitiveCompare(newName, "PA"))
    {
        if (size==0)
            throw CGenericErrorLine (ERR_PA_SIZE_MISSING, line, name);
        if (start+size > 63)
            throw CGenericErrorLine (ERR_PA_SIZE_LARGE, line, name);
        object->type = OB_PA;
    }
    else if (RA::Instance().findNameInRA(newName, object->typeRA,
                                         object->location, line))
    {
        object->type = OB_RA;
        /*Make sure not to access outside the variable*/
        if (object->location.start + start + size - 1 > object->location.end)
            throw CGenericErrorLine (ERR_VAR_ACCESS_TOO_LARGE, line, newName,
                    object->location.end-object->location.start+1, name);
    }
    else
        throw CGenericErrorLine (ERR_UNRECOGNIZED_OBJECT, line, name);

    object->location.start += start;
    /*In case size==0 we return the entire buffer*/
    if (size!=0)
        object->location.end    = object->location.start + size - 1;

    if (object->location.end - object->location.start > 7)
        throw CGenericErrorLine (ERR_BUFFER_ACCESS_TOO_LARGE, line, name);
}

void CIR::createIRFWAccess (std::string name, CObject *object, int line)
{
    uint32_t size, start;
    std::string newName = name;
    getBufferInfo (newName, start, size, line, 1);
    object->location.start = start;
    if (size!=0)
        object->location.end  = start+size-1;
    else
        throw CGenericErrorLine (ERR_FW_SIZE_MISSING, line, name);
    if (start+size > 2040)
        throw CGenericErrorLine (ERR_FW_SIZE_LARGE, line, name);
    object->type = OB_FW;
}

void CIR::createIRField (std::string name, CObject *object, int line)
{
    findInFW(getCurrentProtoName(), name, object->location, line);
    object->type = OB_FW;
}

void CIR::createIRProtocolField (std::string name, CObject *object, int line)
{
    std::string protocolName, newName = name;

    int dotLoc = newName.find(".", 0);
    if (dotLoc == std::string::npos)
        protocolName = getCurrentProtoName();
    else
        protocolName = newName.substr(0, dotLoc);
    newName = newName.substr(dotLoc+1,newName.length());
    if (!insensitiveCompare (protocolName,getCurrentProtoName()))
        throw CGenericErrorLine(ERR_CANT_ACCESS_PROTOCOL, line, protocolName +
            " currently working in protocol " + getCurrentProtoName());

    findInFW(protocolName, newName, object->location, line);
    object->type = OB_FW;
}

/*create an expression based on lex/yacc files*/
void CIR::createIRExprValue (std::string name, CENode*& eNode, int line, int replace)
{
    setIRYacc (this);
    setLineYacc(&line);
    SPExpr_scan_string (name.c_str());
    SPExprparse();
    SPExprlex_destroy ();
    if (replace && eNode)
    {
        eNode->deleteENode();
        deleteEnode (eNode);
    }
    eNode  = getExpressionYacc();
    checkExprValue (eNode, line);
}

/* ---------------------------------- Useful IR functions-------------------*/

uint32_t CIR::calculateFormatSize (int line)
{
    uint32_t ret;
    if (!status.currentAfter)
        throw CGenericErrorLine (ERR_INTERNAL_SP_ERROR, line);
    if (!protocolsIRs[status.currentProtoIndex].protocol.GetHeaderSize(ret))
        throw CGenericErrorLine (ERR_HEADER_SIZE_MISSING, line);
    else
        return ret;
}

void CIR::getBufferInfo (std::string &name, uint32_t &startByte, uint32_t &sizeByte, int line, bool bits)
{
    std::string oName   = name;
    int indexLoc        = name.find("[",0);
    int midIndexLoc     = name.find(":", 0);
    int endLoc          = name.find("]",0);
    if (midIndexLoc<=indexLoc || endLoc<=midIndexLoc)
        throw CGenericErrorLine (ERR_INVALID_INDEX, line, name);
    std::istringstream stringS1(name.substr(indexLoc + 1,
                                midIndexLoc - indexLoc - 1));
    stringS1 >> startByte;
    std::istringstream stringS2(name.substr(midIndexLoc + 1,
                                endLoc - midIndexLoc - 1));
    stringS2 >> sizeByte;
    name=name.substr(0,indexLoc);
    if (!bits && sizeByte > 8)
        throw CGenericErrorLine (ERR_BUFFER_ACCESS_TOO_LARGE, line, oName);
    else if (bits && sizeByte > 64)
        throw CGenericErrorLine (ERR_BUFFER_ACCESS_TOO_LARGE, line, oName);
}

void CIR::setTask (CTaskDef *task1)
{
    task = task1;
}


/*Find errors in expressions*/
void CIR::checkExprValue (CENode* eNode, int line) const
{
    eNode->line = line;
    if (eNode->type == ESHL || eNode->type == ESHR)
    {
        if (eNode->dyadic.right->type != EINTCONST)
            throw CGenericErrorLine (ERR_SHIFT_BY_IMM, line);
        if (eNode->dyadic.right->type == EINTCONST &&
            (eNode->dyadic.right->intval < 1 ||
             eNode->dyadic.right->intval > 64))
            throw CGenericErrorLine (ERR_SHIFT_BY_VALUE, line);
    }
    else if (eNode->type == ESHLAND)
    {
        if (eNode->dyadic.right->type != EINTCONST &&
            eNode->dyadic.right->type != EOBJREF)
            throw CGenericErrorLine (ERR_CONCAT_VALUE, line);
    }
    else if (eNode->type == EADD || eNode->type == ESUB)
    {
        if (eNode->dyadic.left->isMoreThan32() ||
            eNode->dyadic.right->isMoreThan32())
            CGenericErrorLine::printWarning(WARN_MORE_THAN32, line);
    }
    else if (eNode->type == EADDCARRY)
    {
        if (eNode->dyadic.left->isMoreThan16() ||
            eNode->dyadic.right->isMoreThan16())
                throw CGenericErrorLine (ERR_ADDC_SIZE, line);
    }
    else if (eNode->type == ECHECKSUM_LOC)
    {
        if (eNode->dyadic.left->type   == EINTCONST &&
            eNode->dyadic.right->type  == EINTCONST &&
            eNode->dyadic.left->intval  > 256 ||
            eNode->dyadic.right->intval > 256)
               throw CGenericErrorLine(ERR_CHECKSUM_SECOND_THIRD, line);
    }
    else if (eNode->type == ECHECKSUM)
    {
        if (eNode->dyadic.left->type   == EINTCONST &&
            eNode->dyadic.left->intval  > 0xffff)
                throw CGenericErrorLine (ERR_CHECKSUM_FIRST, line);
    }

    /*Check for errors related to mix of arithmetic/logical operators*/
    if (eNode->isMonadic() || eNode->isDyadic())
    {
        if (eNode->type == ENOT)
        {
            if (!eNode->monadic->isCond())
                throw CGenericErrorLine (ERR_EXPECTED_COND_NOT, line);
        }
        else if (eNode->type == EAND || eNode->type == EOR)
        {
            if((!eNode->dyadic.left->isCond()) ||
               (!eNode->dyadic.right->isCond()))
                throw CGenericErrorLine (ERR_EXPECTED_COND_AND, line);
        }
        else
        {
            if ((eNode->isMonadic() && eNode->monadic->isCond())    ||
                (eNode->isDyadic()  && eNode->dyadic.left->isCond()) ||
                (eNode->isDyadic()  && eNode->dyadic.right->isCond()))
                throw CGenericErrorLine (ERR_UNEXPECTED_COND, line);
        }
    }
    if (eNode->isDyadic())
    {
        checkExprValue (eNode->dyadic.left, line);
        checkExprValue (eNode->dyadic.right, line);
    }
    if (eNode->isMonadic())
        checkExprValue (eNode->monadic, line);
}

void CIR::findInFW(std::string protocolName, std::string fieldName, CLocation &location, int line) const
{
    for (unsigned int i = 0; i < task->protocols.size(); i++)
    {
        uint32_t     bitsize;
        uint32_t     bitoffset;
        /*Find the correct protocol*/
        if (insensitiveCompare (task->protocols[i].name, protocolName))
        {
            /*Check if field exists*/
            if (!task->protocols[i].FieldExists(fieldName))
                throw CGenericErrorLine (ERR_UNRECOGNIZED_FIELD,
                                         line, fieldName);
            else
            {
                task->protocols[i].GetFieldProperties( fieldName,
                                                       bitsize, bitoffset );
                location.start = bitoffset;
                location.end = bitoffset+bitsize-1;
                if (location.end - location.start > 63)
                    throw CGenericErrorLine (ERR_FIELD_TOO_LARGE,
                                             line, fieldName);
                return;
            }
        }
    }
    throw CGenericErrorLine (ERR_UNRECOGNIZED_OBJECT, line, fieldName);
}

std::string CIR::getCurrentProtoName() const
{
    if (status.currentAfter)
        return protocolsIRs[status.currentProtoIndex].protocol.name;
    else
        return protocolsIRs[status.currentProtoIndex].protocol.prevproto[0];
}

void CIR::findPrevprotoOffset (CObject *object, int line) const
{
    ProtoType pt = protocolsIRs[status.currentProtoIndex].
                                        protocol.prevType[0];
    int eCode = 0;
    object->type = OB_RA;
    RAType lookForRAType;

    switch (pt)
    {
    	case PT_NONE:       lookForRAType = RA_EMPTY;       	break;
    	case PT_SP_PROTOCOL:lookForRAType = RA_EMPTY;       	break;
    	case PT_ETH:        lookForRAType = RA_ETHOFFSET;       break;
        case PT_VLAN:       lookForRAType = RA_VLANTCIOFFSET_N; break;
        case PT_VxLAN:      lookForRAType = RA_EMPTY; 			break;
        case PT_LLC_SNAP:   lookForRAType = RA_LLC_SNAPOFFSET;  break;
        case PT_MPLS:       lookForRAType = RA_MPLSOFFSET_N;    break;
		case PT_ARP:        lookForRAType = RA_ARPOFFSET;       break;
        case PT_IP:         lookForRAType = RA_IPOFFSET_N;      break;
        case PT_IPV4:       lookForRAType = RA_IPOFFSET_N;      break;
        case PT_IPV6:       lookForRAType = RA_IPOFFSET_N;      break;
        case PT_TCP:        lookForRAType = RA_L4OFFSET;        break;
        case PT_UDP:        lookForRAType = RA_L4OFFSET;        break;
        case PT_GRE:        lookForRAType = RA_GREOFFSET;       break;
        case PT_PPPOE_PPP:  lookForRAType = RA_PPPOEOFFSET;     break;
        case PT_MINENCAP:   lookForRAType = RA_MINENCAPOFFSET;  break;
        case PT_SCTP:       lookForRAType = RA_L4OFFSET;        break;
        case PT_DCCP:       lookForRAType = RA_L4OFFSET;        break;
        case PT_IPSEC_AH:   lookForRAType = RA_L4OFFSET;        break;
        case PT_IPSEC_ESP:  lookForRAType = RA_L4OFFSET;        break;
        case PT_OTHER_L3:   lookForRAType = RA_NXTHDROFFSET;    break;
        case PT_OTHER_L4:   lookForRAType = RA_NXTHDROFFSET;    break;
		case PT_GTP:        lookForRAType = RA_GTPOFFSET;       break;
		case PT_ESP:        lookForRAType = RA_ESPOFFSET;       break;
		case PT_OTHER_L5:   lookForRAType = RA_NXTHDROFFSET;    break;
		case PT_FINAL_SHELL: lookForRAType = RA_NXTHDROFFSET;    break;
        default: throw CGenericErrorLine (ERR_INTERNAL_SP_ERROR, line);
    }

    if (lookForRAType != RA_EMPTY) {
		eCode = RA::Instance().findTypeInRA(lookForRAType, object->location);
		if (!eCode)
			throw CGenericError (ERR_INTERNAL_SP_ERROR);
    }
}

/*Find a SP Protocol */
bool CIR::findSpProtocol(std::string nextproto, int line) const
{
	for (int i = 0; i < protocolsIRs.size(); i++)
    {
    	if (nextproto.compare(protocolsIRs[i].protocol.name) == 0) {
    		return true;
    	}
    }
	return false;
}

/*Find a SP Protocol label */
std::string CIR::findSpProtoLabel(std::string nextproto, int line) const
{
	std::string label = "";

	for (int i = 0; i < protocolsIRs.size(); i++)
    {
    	if (nextproto.compare(protocolsIRs[i].protocol.name) == 0) {
    		label = protocolsIRs[i].label.name;
    		break;
    	}
    }
	return label;
}

/*Find a protocol*/
ProtoType CIR::findProtoLabel (std::string nextproto, int line) const
{
    int i = 0;

    std::string newName = stripBlanks (nextproto);
    if (insensitiveCompare(newName, "end_parse") ||
        insensitiveCompare(newName, "none"))
        return PT_END_PARSE;
    else if (insensitiveCompare(newName, "return"))
        return PT_RETURN;
    else if (insensitiveCompare(newName, "after_ethernet"))
        return PT_NEXT_ETH;
    else if (insensitiveCompare(newName, "after_ip"))
        return PT_NEXT_IP;
	else if (insensitiveCompare(newName, "after_tcp"))
		return PT_NEXT_TCP;
	else if (insensitiveCompare(newName, "after_udp"))
		return PT_NEXT_UDP;
    else
        return findSpecificProtocol(newName, line);
}

ProtoType CIR::findSpecificProtocol(std::string name, int line) const
{
    std::map< std::string, ProtoType >::iterator protocolsLabelsIterator;
    std::map< std::string, ProtoType> protocolsLabels;
    std::string newName = name;
    std::transform(newName.begin(), newName.end(), newName.begin(), mytolower);

    protocolsLabels["none"]     	= PT_NONE;
    protocolsLabels["ethernet"]     = PT_ETH;
    protocolsLabels["llc_snap"]     = PT_LLC_SNAP;
    protocolsLabels["vlan"]         = PT_VLAN;
    protocolsLabels["vxlan"]        = PT_VxLAN;
    protocolsLabels["pppoe"]        = PT_PPPOE_PPP;
    protocolsLabels["mpls"]         = PT_MPLS;
	protocolsLabels["arp"]          = PT_ARP;
	protocolsLabels["ip"]           = PT_IP;
    protocolsLabels["ipv4"]         = PT_IPV4;
    protocolsLabels["ipv6"]         = PT_IPV6;
    protocolsLabels["gre"]          = PT_GRE;
    protocolsLabels["minencap"]     = PT_MINENCAP;
    protocolsLabels["otherl3"]      = PT_OTHER_L3;
    protocolsLabels["tcp"]          = PT_TCP;
    protocolsLabels["udp"]          = PT_UDP;
    protocolsLabels["ipsec_ah"]     = PT_IPSEC_AH;
    protocolsLabels["ipsec_esp"]    = PT_IPSEC_ESP;
    protocolsLabels["sctp"]         = PT_SCTP;
    protocolsLabels["dccp"]         = PT_DCCP;
    protocolsLabels["otherl4"]      = PT_OTHER_L4;
	protocolsLabels["gtp"]          = PT_GTP;
	protocolsLabels["esp"]          = PT_ESP;
	protocolsLabels["otherl5"]      = PT_OTHER_L5;
	protocolsLabels["finalshell"]   = PT_FINAL_SHELL;

    protocolsLabelsIterator = protocolsLabels.find(newName);
    if (protocolsLabelsIterator == protocolsLabels.end())
    	return PT_INVALID; 	//throw CGenericErrorLine (ERR_UNSUPPORTED_PROTOCOL, line, name);
    else
        return protocolsLabels[newName];
}

std::string CIR::createUniqueName()
{
    return std::string("LABEL_" + intToString(++currentUniqueName));
}

CENode* CIR::createENode()
{
    return new CENode;
}

/* ------------------------ CReg---------------------------------*/

/*Return the other working register or R_WR1 by default*/
CReg CReg::other()
{
    if      (type == R_WR0)
        return CReg(R_WR1);
    else if (type == R_WR1)
        return CReg(R_WR0);
    else if (type == R_EMPTY)
        return CReg(R_WR1);
    else
        throw CGenericError (ERR_INTERNAL_SP_ERROR);
}

std::string CReg::getName() const
{
    switch (type)
    {
        case R_WR1:  return "WR1";
        case R_WR0:  return "WR0";
        case R_WO:   return "WO";
        default:
            throw CGenericError (ERR_INTERNAL_SP_ERROR, "wrong register type");
    }
}

/* ------------------------ CFaf---------------------------------*/


CFaf::CFaf(std::string fafname)
{
	init();

	type = FAF_Reserved;
	std::map <FafType, std::string>::const_iterator it;
	for (it = mapFafInfo.begin(); it != mapFafInfo.end(); it++)
	{
		if (it->second == fafname)
		{
			type = it->first;
			break;
		}
	}
}

void CFaf::init()
{
	mapFafInfo[FAF_User_Defined_0] = 			"custom_0";
	mapFafInfo[FAF_User_Defined_1] = 			"custom_1";
	mapFafInfo[FAF_User_Defined_2] = 			"custom_2";
	mapFafInfo[FAF_User_Defined_3] = 			"custom_3";
	mapFafInfo[FAF_User_Defined_4] = 			"custom_4";
	mapFafInfo[FAF_User_Defined_5] = 			"custom_5";
	mapFafInfo[FAF_User_Defined_6] = 			"custom_6";
	mapFafInfo[FAF_User_Defined_7] = 			"custom_7";
	mapFafInfo[FAF_Shim_Shell_Soft_Parsing_Error] = "shim_soft_parsing_error";
	mapFafInfo[FAF_Parsing_Error] = 			"parsing_error";
	mapFafInfo[FAF_Ethernet_MAC_Present] = 		"Ethernet_MAC_present";
	mapFafInfo[FAF_Ethernet_Unicast] = 			"Ethernet_unicast";
	mapFafInfo[FAF_Ethernet_Multicast] = 		"Ethernet_multicast";
	mapFafInfo[FAF_Ethernet_Broadcast] = 		"Ethernet_broadcast";
	mapFafInfo[FAF_BPDU_Frame] = 				"BPDU_frame";
	mapFafInfo[FAF_FCoE_Detected] = 			"FCoE_detected";
	mapFafInfo[FAF_FIP_Detected] = 				"FIP_detected";
	mapFafInfo[FAF_Ethernet_Parsing_Error] = 	"Ethernet_parsing_error";
	mapFafInfo[FAF_LLC_SNAP_Present] = 			"LLC_SNAP_present";
	mapFafInfo[FAF_Unknown_LLC_OUI] = 			"unknown_LLC_OUI";
	mapFafInfo[FAF_LLC_SNAP_Error] = 			"LLC_SNAP_error";
	mapFafInfo[FAF_VLAN_1_Present] = 			"VLAN_1_present";
	mapFafInfo[FAF_VLAN_n_Present] = 			"VLAN_n_present";
	mapFafInfo[FAF_GRE_Ethernet] = 				"GRE_ethernet";
	mapFafInfo[FAF_VLAN_Parsing_Error] = 		"VLAN_parsing_error";
	mapFafInfo[FAF_PPPoE_PPP_Present] = 		"PPPoE_PPP_present";
	mapFafInfo[FAF_PPPoE_PPP_Parsing_Error] = 	"PPPoE_PPP_parsing_error";
	mapFafInfo[FAF_MPLS_1_Present] = 			"MPLS_1_present";
	mapFafInfo[FAF_MPLS_n_Present] = 			"MPLS_n_present";
	mapFafInfo[FAF_MPLS_Parsing_Error] = 		"MPLS_parsing_error";
	mapFafInfo[FAF_ARP_Frame_Present] = 		"ARP_present";
	mapFafInfo[FAF_ARP_Parsing_Error] = 		"ARP_parsing_error";
	mapFafInfo[FAF_L2_Unknown_Protocol] = 		"L2_unknown_protocol";
	mapFafInfo[FAF_L2_Soft_Parsing_Error] = 	"L2_soft_parsing_error";
	mapFafInfo[FAF_IPv4_1_Present] = 			"IPv4_1_present";
	mapFafInfo[FAF_IPv4_1_Unicast] = 			"IPv4_1_unicast";
	mapFafInfo[FAF_IPv4_1_Multicast] = 			"IPv4_1_multicast";
	mapFafInfo[FAF_IPv4_1_Broadcast] = 			"IPv4_1_broadcast";
	mapFafInfo[FAF_IPv4_n_Present] = 			"IPv4_n_present";
	mapFafInfo[FAF_IPv4_n_Unicast] = 			"IPv4_n_unicast";
	mapFafInfo[FAF_IPv4_n_Multicast] = 			"IPv4_n_multicast";
	mapFafInfo[FAF_IPv4_n_Broadcast] = 			"IPv4_n_broadcast";
	mapFafInfo[FAF_IPv6_1_Present] = 			"IPv6_1_present";
	mapFafInfo[FAF_IPv6_1_Unicast] = 			"IPv6_1_unicast";
	mapFafInfo[FAF_IPv6_1_Multicast] = 			"IPv6_1_multicast";
	mapFafInfo[FAF_IPv6_n_Present] = 			"IPv6_n_present";
	mapFafInfo[FAF_IPv6_n_Unicast] = 			"IPv6_n_unicast";
	mapFafInfo[FAF_IPv6_n_Multicast] = 			"IPv6_n_multicast";
	mapFafInfo[FAF_IP_1_Option_Present] = 		"IP_1_option_present";
	mapFafInfo[FAF_IP_1_Unknown_Protocol] = 	"IP_1_unknown_protocol";
	mapFafInfo[FAF_IP_1_Packet_Is_A_Fragment] = "IP_1_packet_is_fragment";
	mapFafInfo[FAF_IP_1_Packet_Is_An_Initial_Fragment] = "ip_1_packet_is_initial_fragment";
	mapFafInfo[FAF_IP_1_Parsing_Error] = 		"IP_1_parsing_error";
	mapFafInfo[FAF_IP_n_Option_Present] = 		"IP_n_option_present";
	mapFafInfo[FAF_IP_n_Unknown_Protocol] = 	"IP_n_unknown_protocol";
	mapFafInfo[FAF_IP_n_Packet_Is_A_Fragment] = "IP_n_packet_is_fragment";
	mapFafInfo[FAF_IP_n_Packet_Is_An_Initial_Fragment] = "IP_n_packet_is_initial_fragment";
	mapFafInfo[FAF_ICMP_Detected] = 			"ICMP_detected";
	mapFafInfo[FAF_IGMP_Detected] = 			"IGMP_detected";
	mapFafInfo[FAF_ICMPv6_Detected] = 			"ICMPv6_detected";
	mapFafInfo[FAF_UDP_Light_Detected] = 		"UDP_light_detected";
	mapFafInfo[FAF_IP_n_Parsing_Error] = 		"IP_n_parsing_error";
	mapFafInfo[FAF_Min_Encap_Present] = 		"Min_encap_present";
	mapFafInfo[FAF_Min_Encap_S_flag_Set] = 		"Min_encap_s_flag_set";
	mapFafInfo[FAF_Min_Encap_Parsing_Error] = 	"Min_encap_parsing_error";
	mapFafInfo[FAF_GRE_Present] = 				"GRE_present";
	mapFafInfo[FAF_GRE_R_Bit_Set] = 			"GRE_R_bit_set";
	mapFafInfo[FAF_GRE_Parsing_Error] = 		"GRE_parsing_error";
	mapFafInfo[FAF_L3_Unknown_Protocol] = 		"L3_unknown_protocol";
	mapFafInfo[FAF_L3_Soft_Parsing_Error] =	 	"L3_soft_parsing_error";
	mapFafInfo[FAF_UDP_Present] = 				"UDP_present";
	mapFafInfo[FAF_UDP_Parsing_Error] = 		"UDP_parsing_error";
	mapFafInfo[FAF_TCP_Present] = 				"TCP_present";
	mapFafInfo[FAF_TCP_Options_Present] = 		"TCP_options_present";
	mapFafInfo[FAF_TCP_Control_Bits_6_11_Set] = "TCP_control_bits_6_11_Set";
	mapFafInfo[FAF_TCP_Control_Bits_3_5_Set] = 	"TCP_control_bits_3_5_Set";
	mapFafInfo[FAF_TCP_Parsing_Error] = 		"TCP_parsing_error";
	mapFafInfo[FAF_IPSec_Present] = 			"IPSec_present";
	mapFafInfo[FAF_IPSec_ESP_Found] = 			"IPSec_ESP_found";
	mapFafInfo[FAF_IPSec_AH_Found] = 			"IPSec_AH_found";
	mapFafInfo[FAF_IPSec_Parsing_Error] = 		"IPSec_parsing_error";
	mapFafInfo[FAF_SCTP_Present] = 				"SCTP_present";
	mapFafInfo[FAF_SCTP_Parsing_Error] = 		"SCTP_parsing_error";
	mapFafInfo[FAF_DCCP_Present] = 				"DCCP_present";
	mapFafInfo[FAF_DCCP_Parsing_Error] = 		"DCCP_parsing_error";
	mapFafInfo[FAF_L4_Unknown_Protocol] = 		"L4_unknown_protocol";
	mapFafInfo[FAF_L4_Soft_Parsing_Error] =		"L4_soft_parsing_error";
	mapFafInfo[FAF_GTP_Present] = 				"GTP_present";
	mapFafInfo[FAF_GTP_Parsing_Error] = 		"GTP_parsing_error";
	mapFafInfo[FAF_ESP_Present] = 				"ESP_present";
	mapFafInfo[FAF_ESP_Parsing_Error] = 		"ESP_parsing_error";
	mapFafInfo[FAF_iSCSI_Detected] = 			"iSCSI_detected";
	mapFafInfo[FAF_Capwap_Control_Detected] = 	"Capwap_control_detected";
	mapFafInfo[FAF_Capwap_Data_Detected] = 		"Capwap_data_detected";
	mapFafInfo[FAF_L5_Soft_Parsing_Error] = 	"L5_soft_parsing_error";
	mapFafInfo[FAF_IPv6_Route_Hdr1_Present] = 	"IPv6_route_hdr1_present";
	mapFafInfo[FAF_IPv6_Route_Hdr2_Present] = 	"IPv6_route_hdr2_present";
	mapFafInfo[FAF_GTP_Primed_Detected] = 		"GTP_primed_detected";
	mapFafInfo[FAF_VLAN_Prio_Detected] = 		"VLAN_prio_detected";
	mapFafInfo[FAF_PTP_Detected] = 				"PTP_detected";
	mapFafInfo[FAF_VXLAN_Present] = 			"VxLAN_present";
	mapFafInfo[FAF_VXLAN_Parsing_error] = 		"VxLAN_parsing_error";
	mapFafInfo[FAF_Ethernet_slow_protocol] = 	"Ethernet_slow_protocol";
	mapFafInfo[FAF_IKE_Present] = 				"IKE_present";
	mapFafInfo[FAF_Reserved] = 					"Reserved";

}

std::string CFaf::getName() const
{
	std::map <FafType, std::string>::const_iterator it = mapFafInfo.find(type);
	return it->second;
}

bool CFaf::isUserDefined()
{
	return (FAF_User_Defined_0 <= type && type <= FAF_User_Defined_7);
}

/* ------------------------ CObject -----------------------------*/

/*Returns string with object name (type and location)*/
std::string CObject::getName() const
{
    std::string objTypeName;
    std::string midChar;
    std::stringstream ss;
    std::string ret;
    if (type == OB_FW)
    {
        objTypeName = "FW";
        midChar = "..";
    }
    else if (type == OB_RA)
    {
        objTypeName = "RA";
        midChar = ":";
    }
    else if (type == OB_PA)
    {
        objTypeName = "PA";
        midChar = ":";
    }
    ss << objTypeName << "[" << std::dec << location.start
       << midChar << std::dec << location.end << "]";
    ss >> ret;
    return ret;
}

bool CObject::isMoreThan32 () const
{
    if ((type == OB_PA || type == OB_RA) &&
        location.end-location.start>3)
        return 1;
    else if (type == OB_FW &&
             location.end-location.start>31)
         return 1;
    else
        return 0;
}

bool CObject::isMoreThan16 () const
{
    if ((type == OB_PA || type == OB_RA) &&
        location.end-location.start>1)
        return 1;
    else if (type == OB_FW &&
             location.end-location.start>15)
         return 1;
    else
        return 0;
}

/*------------------------ CENode Section--------------------------------*/

CENode::CENode (ENodeType newType, CENode* unary)
{
    *this = CENode();
    type       = newType;
    monadic    = unary;
	dyadic.left    = NULL;
	dyadic.right   = NULL;
	objref     = NULL;
}

CENode::CENode (ENodeType newType, CENode* left, CENode* right)
{
    *this = CENode();
    type           = newType;
    dyadic.left    = left;
    dyadic.right   = right;
    dyadic.dir     = 0;
	monadic		   = NULL;
	objref         = NULL;
}

void CENode::createIntENode(uint64_t intval1)
{
    this->type      = EINTCONST;
    this->intval    = intval1;
}

void CENode::newMonadicENode (ENodeType newType)
{
    this->type      = newType;
    this->monadic   = new CENode;
}

void CENode::newDyadicENode ()
{
    this->dyadic.left   = new CENode;
    this->dyadic.right  = new CENode;
    this->dyadic.dir    = 0;
}

void CENode::newDyadicENode (ENodeType newType)
{
    this->newDyadicENode();
    this->type          = newType;
}

void CENode::newObjectENode ()
{
    this->type      = EOBJREF;
    this->objref    = new CObject;
}

void CENode::newObjectENode (CLocation loc)
{
    this->type      = EOBJREF;
    this->objref    = new CObject(loc);
}

void CENode::newObjectENode (CObject obj)
{
    this->type      = EOBJREF;
    this->objref    = new CObject(obj);
}

void CENode::newObjectENode (RAType rat)
{
    this->type      = EOBJREF;
    this->objref    = new CObject(rat);
    RA::Instance().findTypeInRA(rat, this->objref->location);
}

/*Create a new copy of this ENode*/
CENode* CENode::newDeepCopy()
{
    CENode* retNode = newENode(type);
    retNode->line   = this->line;
    retNode->flags  = this->flags;
    retNode->reg    = this->reg;
    retNode->intval = this->intval;
    if (type == EOBJREF)
        retNode->newObjectENode(*(this->objref));
    else if (isDyadic())
    {
        retNode->dyadic.left  = this->dyadic.left->newDeepCopy();
        retNode->dyadic.right = this->dyadic.right->newDeepCopy();
    }
    else if (isMonadic())
        retNode->monadic = this->monadic->newDeepCopy();
    return retNode;
}

bool CENode::isMonadic () const
{
    if (type == ENOT    || type == EBITNOT)
        return 1;
    else
        return 0;
}

bool CENode::isDyadic () const
{
    if (this->isCondi()     || this->isCondNoti()
     || type == EAND        || type == EOR          || type == EXOR
     || type == ESHL        || type == ESHR         || type == ESHLAND
     || type == EADD        || type == EADDCARRY    || type == ESUB
     || type == ECHECKSUM   || type == ECHECKSUM_LOC
     || type == EBITOR      || type == EBITAND
     || type == EASS        )
        return 1;
    else
        return 0;
}

bool CENode::isCond () const
{
    if (this->isCondi() || this->isCondNoti() ||
        type == EAND    || type == EOR        || type == ENOT)
        return 1;
    else
        return 0;
}

bool CENode::isCondi () const
{
    if (type == ELESS || type == EGREATER || type == EEQU || type == ENOTEQU)
        return 1;
    else
        return 0;
}

bool CENode::isCondNoti () const
{
    if (type == ELESSEQU || type == EGREATEREQU)
        return 1;
    else
        return 0;
}

bool CENode::isMoreThan16 () const
{
    if (type == EINTCONST && ((intval & 0xffffffffffff0000ull) != 0))
        return 1;
    else if (type == EOBJREF && objref->isMoreThan16())
         return 1;
    else
        return 0;
}

bool CENode::isMoreThan32 () const
{
    if (type == EINTCONST &&
        ((intval & 0xffffffff00000000ull) != 0))
        return 1;
    else if (type == EOBJREF && objref->isMoreThan32())
         return 1;
    else
        return 0;
}

CENode* CENode::first() const
{
    if (!isDyadic())
        throw CGenericErrorLine (ERR_INTERNAL_SP_ERROR, line);
    if (dyadic.dir)
        return dyadic.right;
    else
        return dyadic.left;
}

CENode* CENode::second() const
{
    if (!isDyadic())
        throw CGenericErrorLine (ERR_INTERNAL_SP_ERROR, line);
    if (dyadic.dir)
        return dyadic.left;
    else
        return dyadic.right;
}


/*------------------------ Global function--------------------------------*/

CENode* newObjectENode()
{
    CENode* node = new CENode;
    node->newObjectENode();
    return node;
}

CENode* newENode(ENodeType type)
{
    CENode* node = new CENode;
    node->type = type;
    return node;
}

void    deleteEnode(CENode* expr)
{
    delete expr;
    expr = 0;
}


/*--------------------CStatement Section ---------------------------*/

void CStatement::newIfGotoStatement ()
{
    this->type              = ST_IFGOTO;
    this->expr              = new CENode;
    this->flags.hasENode    = 1;
}

void CStatement::newIfGotoStatement (CLabel label1, int line1)
{
    createIfGotoStatement(label1, line1);
    this->expr              = new CENode;
}

void CStatement::newExpressionStatement (int line1)
{
    this->type              = ST_EXPRESSION;
    this->expr              = new CENode;
    this->line              = line1;
    this->expr->line        = line1;
    this->flags.hasENode    = 1;
}

void CStatement::newAssignStatement (int line1)
{
    newExpressionStatement (line1);
    this->expr->type = EASS;
}

void CStatement::newSwitchStatement (int line1)
{
    this->type              = ST_SWITCH;
    this->switchTable       = new CSwitchTable;
    this->line              = line1;
    this->flags.hasENode    = 1;
}

void CStatement::createIfGotoStatement (CLabel label1, int line1)
{
    this->type              = ST_IFGOTO;
    this->label             = label1;
    this->line              = line1;
    this->flags.hasENode    = 1;
}

void CStatement::createIfFafGotoStatement (CLabel label1, std::string faf, int line1)
{
	this->type              = ST_FAFGOTO;
	this->label             = label1;
	this->line              = line1;
	this->text				= faf;
}

void CStatement::createIfNGotoStatement (CLabel label1, int line1)
{
    this->type              = ST_IFNGOTO;
    this->label             = label1;
    this->line              = line1;
    this->flags.hasENode    = 1;
}

void CStatement::createInlineStatement (std::string data, int line1)
{
    this->type  = ST_INLINE;
    this->text  = data;
    this->line  = line1;
}


void CStatement::createExpressionStatement (CENode *enode)
{
    this->type              = ST_EXPRESSION;
    this->expr              = enode;
    this->flags.hasENode    = 1;
}

void CStatement::createLabelStatement ()
{
    this->type = ST_LABEL;
}

void CStatement::createLabelStatement (std::string labelName)
{
    this->type = ST_LABEL;
    this->label.name = labelName;
}

void CStatement::createLabelStatement (CLabel label)
{
    this->type = ST_LABEL;
    this->label = label;
}

void CStatement::createGotoStatement (CLabel newLabel)
{
    this->type  = ST_GOTO;
    this->label = newLabel;
}

void CStatement::createGotoStatement (std::string labelName)
{
    this->type  = ST_GOTO;
    this->label = CLabel (labelName);
}

void CStatement::createGotoStatement (ProtoType type)
{
    this->type              = ST_GOTO;
    this->label             = CLabel (type);
    this->flags.externJump  = 1;
}

void CStatement::createGosubStatement   (CLabel newLabel)
{
	this->type  = ST_GOSUB;
	this->label = newLabel;
}

void CStatement::createGosubStatement   (std::string labelName)
{
	this->type  = ST_GOSUB;
	this->label = CLabel (labelName);
}

void CStatement::createRetsubStatement  ()
{
	this->type  = ST_RETSUB;
}

void CStatement::createSetFafStatement  (std::string faf)
{
	this->type  = ST_SETFAF;
	this->text = faf;
}

void CStatement::createResetFafStatement (std::string faf)
{
	this->type  = ST_RESETFAF;
	this->text = faf;
}

void CStatement::createSectionEndStatement ()
{
    this->type              = ST_SECTIONEND;
    this->flags.hasENode    = 1;
}

bool CStatement::isGeneralExprStatement () const
{
    if (this->flags.hasENode)
        return 1;
    else
        return 0;
}


/* ------------------- delete  --------------------------------------*/

void CENode::deleteObjectENode ()
{
    if (objref)
    {
        delete objref;
        objref = 0;
    }
}

void CENode::deleteMonadicENode ()
{
    if (monadic)
    {
        monadic->deleteENode();
        delete monadic;
        monadic = 0;
    }
}

void CENode::deleteDyadicENode ()
{
    if (dyadic.left)
    {
        dyadic.left->deleteENode();
        delete dyadic.left;
        dyadic.left = 0;
    }
    if (dyadic.right)
    {
        dyadic.right->deleteENode();
        delete dyadic.right;
        dyadic.right = 0;
    }
}

void CENode::deleteENode ()
{
    if (this->isDyadic())
        this->deleteDyadicENode();
    if (this->isMonadic())
        this->deleteMonadicENode();
    else if (type==EOBJREF)
        this->deleteObjectENode();
}

void CStatement::deleteStatementNonRecursive ()
{
    if (isGeneralExprStatement() && expr)
    {
        delete expr;
        expr = 0;
    }
    if (type == ST_SWITCH && switchTable)
    {
        delete switchTable;
        switchTable = 0;
    }
}


CStatement::CStatement()
    : type(ST_EMPTY), text(""), line(NO_LINE)
{
	expr = NULL;
	switchTable = NULL;
};


void CStatement::deleteStatement ()
{
    if (isGeneralExprStatement() && expr)
    {
        expr->deleteENode();
        delete expr;
        expr = 0;
    }
    if (type == ST_SWITCH && switchTable)
    {
        delete switchTable;
        switchTable = 0;
    }
}

void CIR::deleteIR ()
{
    uint32_t i=0, j=0;
    for (i = 0; i < protocolsIRs.size(); i++)
    {
        if (protocolsIRs[i].prevHeaderSize)
        {
            protocolsIRs[i].prevHeaderSize->deleteENode();
            delete protocolsIRs[i].prevHeaderSize;
            protocolsIRs[i].prevHeaderSize = 0;
        }
        if (protocolsIRs[i].headerSize)
        {
            protocolsIRs[i].headerSize->deleteENode();
            delete protocolsIRs[i].headerSize;
            protocolsIRs[i].headerSize = 0;
        }
        for (j = 0; j < protocolsIRs[i].statements.size(); j++)
            protocolsIRs[i].statements[j].deleteStatement();
    }
    deleteDumpPath();
}

/*-------------------- RA section------------------------------------*/

void RA::initRA()
{
	RAInInfo["gpr1"]                  = RA_GPR1;
	RAInInfo["gpr2"]                  = RA_GPR2;
	RAInInfo["nxthdr"]                = RA_NXTHDR;
	RAInInfo["runningsum"]            = RA_RUNNINGSUM;
	RAInInfo["fragoffset"]            = RA_FRAGOFFSET;
	RAInInfo["routtype"]              = RA_ROUTTYPE;
	RAInInfo["shimoffset_1"]          = RA_SHIMOFFSET_1;
	RAInInfo["shimoffset_2"]          = RA_SHIMOFFSET_2;
#ifdef FM_SHIM3_SUPPORT
	RAInInfo["shimoffset_3"]          = RA_SHIMOFFSET_3;
#else  /* FM_SHIM3_SUPPORT */
	RAInInfo["ip_pidoffset"]          = RA_IP_PIDOFFSET;
#endif /* FM_SHIM3_SUPPORT */
	RAInInfo["ethoffset"]             = RA_ETHOFFSET;
	RAInInfo["llc_snapoffset"]        = RA_LLC_SNAPOFFSET;
	RAInInfo["vlantcioffset_1"]       = RA_VLANTCIOFFSET_1;
	RAInInfo["vlantcioffset_n"]       = RA_VLANTCIOFFSET_N;
	RAInInfo["lastetypeoffset"]       = RA_LASTETYPEOFFSET;
	RAInInfo["pppoeoffset"]           = RA_PPPOEOFFSET;
	RAInInfo["mplsoffset_1"]          = RA_MPLSOFFSET_1;
	RAInInfo["mplsoffset_n"]          = RA_MPLSOFFSET_N;
	RAInInfo["ipoffset_1"]            = RA_IPOFFSET_1;
	RAInInfo["ipoffset_n"]            = RA_IPOFFSET_N;
	RAInInfo["minencapo"]             = RA_MINENCAPOFFSET;
	RAInInfo["minencapoffset"]        = RA_MINENCAPOFFSET;
	RAInInfo["greoffset"]             = RA_GREOFFSET;
	RAInInfo["l4offset"]              = RA_L4OFFSET;
	RAInInfo["nxthdroffset"]          = RA_NXTHDROFFSET;
	RAInInfo["sperc"]                 = RA_SPERC;
	RAInInfo["iplength"]              = RA_IPLENGTH;
	RAInInfo["attr"]                  = RA_ATTR;
	RAInInfo["ipv4sa"]                = RA_IPV4SA;
	RAInInfo["ipv4da"]                = RA_IPV4DA;
	RAInInfo["ipv6sa1"]               = RA_IPV6SA1;
	RAInInfo["ipv6sa2"]               = RA_IPV6SA2;
	RAInInfo["ipv6da1"]               = RA_IPV6DA1;
	RAInInfo["ipv6da2"]               = RA_IPV6DA2;
	RAInInfo["fafext"]                = RA_FAF_EXT;
	RAInInfo["fafflags"]              = RA_FAF_FLAGS;
	RAInInfo["arpoffset"]			  = RA_ARPOFFSET;
	RAInInfo["gtpoffset"]             = RA_GTPOFFSET;
	RAInInfo["espoffset"]             = RA_ESPOFFSET;
	RAInInfo["ipsecoffset"]           = RA_IPSECOFFSET;
	RAInInfo["routhdroffset1"]        = RA_ROUTHDROFFSET1;
	RAInInfo["routhdroffset2"]        = RA_ROUTHDROFFSET2;
	RAInInfo["grossrunningsum"]       = RA_GROSSRUNNINGSUM;
	RAInInfo["parseerrcode"]          = RA_PARSEERRCODE;
	RAInInfo["softparsectx"]          = RA_SOFTPARSECTX;
	RAInInfo["fdlength"]              = RA_FDLENGTH;
	RAInInfo["parseerrstat"]          = RA_PARSEERRSTAT;

	//Parse Array
	RATypeInfo[RA_GPR1]                  = CLocation(0,7);
	RATypeInfo[RA_GPR2]                  = CLocation(8,15);
	//Parse Result:
	RATypeInfo[RA_NXTHDR]				 = CLocation(16,17);
	RATypeInfo[RA_FAF_EXT]				 = CLocation(18,19);
	RATypeInfo[RA_FAF_FLAGS]			 = CLocation(20,31);
	RATypeInfo[RA_SHIMOFFSET_1]			 = CLocation(32,32);
	RATypeInfo[RA_SHIMOFFSET_2]			 = CLocation(33,33);
#ifdef FM_SHIM3_SUPPORT
	RATypeInfo[RA_SHIMOFFSET_3]          = CLocation(34,34);
#else  /* FM_SHIM3_SUPPORT */
	RATypeInfo[RA_IP_PIDOFFSET]          = CLocation(34,34);
#endif /* FM_SHIM3_SUPPORT */
	RATypeInfo[RA_L2OFFSET]			 	 = CLocation(35,35);
	RATypeInfo[RA_ETHOFFSET]			 = CLocation(35,35);
	RATypeInfo[RA_LLC_SNAPOFFSET]		 = CLocation(36,36);
	RATypeInfo[RA_VLANTCIOFFSET_1]		 = CLocation(37,37);
	RATypeInfo[RA_VLANTCIOFFSET_N]		 = CLocation(38,38);
	RATypeInfo[RA_LASTETYPEOFFSET]		 = CLocation(39,39);
	RATypeInfo[RA_PPPOEOFFSET]			 = CLocation(40,40);
	RATypeInfo[RA_MPLSOFFSET_1]			 = CLocation(41,41);
	RATypeInfo[RA_MPLSOFFSET_N]			 = CLocation(42,42);
	RATypeInfo[RA_L3OFFSET]			 	 = CLocation(43,43);
	RATypeInfo[RA_ARPOFFSET]			 = CLocation(43,43);
	RATypeInfo[RA_IPOFFSET_1]			 = CLocation(43,43);
	RATypeInfo[RA_IPOFFSET_N]			 = CLocation(44,44);
	RATypeInfo[RA_MINENCAPOFFSET]	     = CLocation(44,44);
	RATypeInfo[RA_GREOFFSET]			 = CLocation(45,45);
	RATypeInfo[RA_L4OFFSET]				 = CLocation(46,46);
	RATypeInfo[RA_GTPOFFSET]			 = CLocation(47,47);
	RATypeInfo[RA_ESPOFFSET]			 = CLocation(47,47);
	RATypeInfo[RA_IPSECOFFSET]			 = CLocation(47,47);
	RATypeInfo[RA_ROUTHDROFFSET1]		 = CLocation(48,48);
	RATypeInfo[RA_ROUTHDROFFSET2]		 = CLocation(49,49);
	RATypeInfo[RA_NXTHDROFFSET]			 = CLocation(50,50);
	RATypeInfo[RA_FRAGOFFSET]			 = CLocation(51,51);
	RATypeInfo[RA_GROSSRUNNINGSUM]		 = CLocation(52,53);
	RATypeInfo[RA_RUNNINGSUM]			 = CLocation(54,55);
	RATypeInfo[RA_PARSEERRCODE]			 = CLocation(56,56);
	RATypeInfo[RA_SOFTPARSECTX]			 = CLocation(57,63);
	//Parse Array cont: 0x50
	RATypeInfo[RA_IPV4SA]                = CLocation(80,83);
	RATypeInfo[RA_IPV4DA]                = CLocation(84,87);
	RATypeInfo[RA_IPV6SA1]               = CLocation(80,87);
	RATypeInfo[RA_IPV6SA2]               = CLocation(88,95);
	RATypeInfo[RA_IPV6DA1]				 = CLocation(96,103);
	RATypeInfo[RA_IPV6DA2]               = CLocation(104,111);
	RATypeInfo[RA_SPERC]				 = CLocation(112,113);
	RATypeInfo[RA_IPLENGTH]				 = CLocation(114,115);
	RATypeInfo[RA_ROUTTYPE]				 = CLocation(116,116);
	RATypeInfo[RA_FDLENGTH]				 = CLocation(123,125);
	RATypeInfo[RA_PARSEERRSTAT]			 = CLocation(127,127);

}

RA::RA () {}
RA::~RA () {}

bool RA::findTypeInRA (const RAType type, CLocation &location, int line)
{
    if (type == RA_GPR2)
        CGenericErrorLine::printWarning(WARN_GPR2, line);

    RATypeIterator = RATypeInfo.find (type);
    if (RATypeIterator == RATypeInfo.end())
        throw CGenericError(ERR_INTERNAL_SP_ERROR);
    else
    {
        location.start  = RATypeInfo[type].start;
        location.end    = RATypeInfo[type].end;
        return 1;
    }
}

bool RA::findNameInRA (const std::string name, RAType &type, CLocation &location, int line)
{
    std::string newName = name;
    std::transform(newName.begin(), newName.end(), newName.begin(), mytolower);
    RAInIterator = RAInInfo.find (newName);
    if (RAInIterator == RAInInfo.end())
        return 0;
    else
        type = RAInInfo[newName];

    findTypeInRA (type, location, line);
    return 1;
}


/* -----------------------------General functions (no class)-----------*/
CLocation CLocation::operator+ (const CLocation location) const
{
    CLocation returnLoc;
    returnLoc.start = this->start + location.start;
    returnLoc.end = this->end + location.end;
    return returnLoc;
}

CLocation & CLocation::operator+= (const CLocation location)
{
    start += location.start;
    end   += location.end;
    return *this;
}

CLocation & CLocation::operator-= (const CLocation location)
{
    start -= location.start;
    end   -= location.end;
    return *this;
}


/* ------------------------------------- Lex/Yacc ---------------------*/
CENode*      exprYacc;
CIR*         irYacc;
int*         lineYacc;

void setExpressionYacc(CENode* expr1)
{
    exprYacc = expr1;
}

CENode* getExpressionYacc()
{
    return exprYacc;
}

void setIRYacc(CIR* ir)
{
    irYacc = ir;
}

CIR *getIRYacc()
{
    return irYacc;
}

void setLineYacc(int* line)
{
    lineYacc = line;
}

int *getLineYacc()
{
    return lineYacc;
}
