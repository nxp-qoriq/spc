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
 * File Name : Utils.h
 *
 * ===================================================================*/

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <utility>
#ifdef WIN32
#include <stdint.h>
#else
#include "types_linux.h"
#endif
#include "GenericError.h"

// Public functions
std::string stripBlanks( std::string str );
std::string stripDollar( std::string str );
bool innerBlanks( std::string str );
bool insensitiveCompare (std::string str1, std::string str2);
bool stringToInt  (const std::string &str, uint64_t &n, int line=NO_LINE);
std::string intToString (uint64_t num);
std::string hexToDecString (std::string &str);
char mytolower(char c);


// A helper functor for XML names comparison
struct MyXMLCharComparator
{
   bool operator()(const xmlChar * A, const xmlChar * B) const
   {
       return (std::string((char*)A) < std::string((char*)B));
   }
} ;


#endif  // UTILS_H
