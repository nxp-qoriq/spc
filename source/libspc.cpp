/* =====================================================================
 *
 * The MIT License (MIT)
 * Copyright 2018-2019,2021 NXP
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
 * File Name : libspc.cpp
 *
 * ===================================================================*/

#include <typeinfo>
#include <string.h>
#include <stdarg.h>
#include <string>
#include <sstream>

#include "spc.h"
#include "GenericError.h"
#include "TaskDef.h"
#include "PDLReader.h"
#include "ConfigReader.h"
#include "SoftParser.h"

#define DEFINE_LOGGER_INSTANCE
#include "logger.hpp"


#ifdef _MSC_VER
#pragma warning(disable : 4996)
#ifdef _DEBUG
#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.VC90.CRT' version='9.0.21022.8' processorArchitecture='x86' publicKeyToken='1fc8b3b9a1e18e3b' language='*'\"")
#endif
#endif


std::string error_text;

#ifdef __cplusplus
extern "C" {
#endif

int spc_compile(const char* nameCfg, const char* namePDL, const char* nameSP, bool genIntermCode)
{
    error_text = "";

    try {
        if ( nameCfg != 0 && std::string( nameCfg ) == "nodefault" ) {
        	nameCfg = 0;
        }

        CSoftParserTask task;

        // Process PDL and SP files
        CPDLReader pdlReader(&task);
        pdlReader.parseNetPDL(namePDL, false);

        // Process custom protocols definition - software parser
		pdlReader.parseNetPDL(nameSP, true);

		// Configuration file processing must be after SP was parsed
		// in order to be able to check if desired protocols exists in NetPDL file
        if (nameCfg) {
            // Process configuration file
            ConfigReader cfgReader(&task);
            cfgReader.parseConfig(nameCfg);
        }

        //call soft parser
        task.generateBlob(nameSP, genIntermCode);

        LOG( logger::DBG1 ) << logger::ind( -2 )
                            << "Done"
                            << std::endl;

        LOG( logger::DBG1 ) << std::endl;


        LOG( logger::DBG2 ) << "Generated init:"
                            << std::endl;
        
    }
    catch ( const CGenericError& genError )
    { 	// Catch known errors
        error_text = genError.getErrorMsg();
        LOG( logger::ERR ) << error_text << std::endl;
        return 3;
    }
    catch ( std::exception &e )
    {
        error_text  = e.what();
        error_text += " Type : ";
        error_text += typeid( e ).name();
        LOG( logger::ERR ) << error_text << std::endl;
        return 4;
    }
    catch ( ... )
    {  	// Catch unknown errors
        error_text = "Unrecognized error occurred. The program was terminated";
        LOG( logger::ERR ) << error_text << std::endl;
        return 1;
    }

    return 0;
}

const char* spc_get_error( void )
{
    return error_text.c_str();
}

int32_t spc_log( int32_t level )
{
    using namespace logger;
    
    int32_t ret = LOG_GET_LEVEL();

    LOG_INIT( std::cerr, (log_level_t)level );

    return ret;
}

void spc_log_write( int32_t level, const char* format, ... )
{
    using namespace logger;

    va_list args;
    va_start( args, format );

    if ( level <= LOG_GET_LEVEL() ) {
        char buffer[256];
        vsprintf( buffer, format, args );
        LOG( (log_level_t)level ) << (const char*)buffer << std::endl;
    }

    va_end( args );
}

#ifdef __cplusplus
} // extern "C"
#endif

