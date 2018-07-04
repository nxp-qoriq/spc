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
 * File Name : SPC.cpp
 *
 * ===================================================================*/

#include <tclap/CmdLine.h>
#include <typeinfo>
#include <fstream>
#include <cstring>

#include "spc.h"
#include "GenericError.h"

#ifdef _MSC_VER
#define DEFINE_LOGGER_INSTANCE
#endif
#include "logger.hpp"

#ifdef _MSC_VER
#pragma warning(disable : 4996)
#ifdef _DEBUG
#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.VC90.CRT' version='9.0.21022.8' processorArchitecture='x86' publicKeyToken='1fc8b3b9a1e18e3b' language='*'\"")
#endif
#endif

#define SPC_VERSION "0.1.1"

#include <cstdlib>

spc_model_t model      = {0};


void set_log_level( std::string log_level_name )
{
    int int_log_value = LOG_INFO;

    if ( log_level_name == "none" ) {
        int_log_value = LOG_NONE;
    }
    else if ( log_level_name == "err" ) {
        int_log_value = LOG_ERR;
    }
    else if ( log_level_name == "warn" ) {
        int_log_value = LOG_WARN;
    }
    else if ( log_level_name == "info" ) {
        int_log_value = LOG_INFO;
    }
    else if ( log_level_name == "dbg1" ) {
        int_log_value = LOG_DBG1;
    }
    else if ( log_level_name == "dbg2" ) {
        int_log_value = LOG_DBG2;
    }
    else if ( log_level_name == "dbg3" ) {
        int_log_value = LOG_DBG3;
    }
    else {
    }

#ifdef _MSC_VER
    spc_log( int_log_value );
#endif
    LOG_INIT( std::cerr, logger::log_level_t(int_log_value) );
}


int main( int argc, char* argv[] )
{
#ifdef _DEBUG
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
//    _crtBreakAlloc = 2117;
#endif

    // Wrap everything in the 'try' block.  Do this every time,
    // because exceptions will be thrown for problems.
    try {
        // Get directory name
        std::string appDir( argv[0] );
        const unsigned int pos = appDir.find_last_of( "\\/" );
        if ( std::string::npos == pos ) {
            appDir = ".";
        }
        else {
            appDir = appDir.substr( 0, pos );
        }

        // Define the command line object.
        TCLAP::CmdLine cmd( "Soft Parser Configuration Tool", ' ', SPC_VERSION );

        TCLAP::ValueArg<std::string> swOffset( "t", "sp_offset",
            "Soft Parser generated code base address", false,
            "0x20", "offset" );
        cmd.add( swOffset );


        TCLAP::ValueArg<std::string> log_level( "l", "log_level",
            "Log level: none, err, warn, info, dbg1, dbg2, dbg3",
            false, "info", "level" );
        cmd.add( log_level );

        TCLAP::ValueArg<std::string> nameSP( "s", "custom_protocol",
            "Custom protocol file name", false,
            "nodefault", "custom_protocol_file" );
        cmd.add( nameSP);

#ifdef WIN32
        TCLAP::ValueArg<std::string> namePDL( "d", "pdl",
            "PDL file name", false,
            appDir + "/etc/spc/config/hxs_pdl_v3.xml", "pdl_file" );
#else
        TCLAP::ValueArg<std::string> namePDL( "d", "pdl",
            "PDL file name", false,
            "/etc/spc/config/hxs_pdl_v3.xml", "pdl_file" );
#endif
        cmd.add( namePDL );

        TCLAP::SwitchArg interm_code( "i", "interm",
            "Generate intermediate code" );
        cmd.add( interm_code );

        cmd.parse( argc, argv );

        set_log_level( log_level.getValue() );

        // Check args
        if (!nameSP.isSet())
            throw CGenericError(ERR_SP_REQUIRED);

        int ret = spc_compile(&model,
                    namePDL.getValue().c_str(),
                    nameSP.getValue().c_str(),
                    strtoul( swOffset.getValue().c_str(), 0, 0 ),
                    interm_code.getValue());

        if ( ret != 0 ) {
			//compile error
            return ret;
        }

        return ret;
    }
    catch ( const TCLAP::ArgException& e )  // Catch exceptions for TCLAP
    {
    	spc_log_write( LOG_ERR, "%s for arg %s",
                       e.error().c_str(),
                       e.argId().c_str() );
        return 2;
    }
    catch ( const CGenericError& genError ) { // Catch known errors generated by SPC
    	spc_log_write( LOG_ERR, "%s",
                       genError.getErrorMsg().c_str() );
        return 3;
    }
    catch ( std::exception &e )
    {
    	spc_log_write( LOG_ERR, "Caught exception: %s (type: %s)",
                       e.what(), typeid( e ).name() );
        return 4;
    }
    catch ( ... ) {                     // Catch unknown errors
    	spc_log_write( LOG_ERR, "Unrecognized error occurred. The program was terminated" );
        return 1;
    }

    return 0;
}

