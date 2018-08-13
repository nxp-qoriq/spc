#==========================================================================
#
# The MIT License (MIT)
# Copyright 2018 NXP
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
# 
# The above copyright notice and this permission notice shall be included
# in all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
# IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
# CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
# TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
# SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#==========================================================================
# For host mode only compilation, set FMCHOSTMODE variable. For example:
#     make FMCHOSTMODE=1
#
# Also, use variables below in accordance to your environment

NET_USPACE_HEADER_PATH ?= ./include/net
LIBXML2_HEADER_PATH    ?= /usr/include/libxml2
TCLAP_HEADER_PATH      ?= /usr/include

PKG_NAME = spc
PKG_RELEASE = 1

PLATFORM_FLAG = -DLS1043

ifeq ($(MACHINE),p1023rds)
  PLATFORM_FLAG = -DP1023
endif

ifeq ($(MACHINE),b4860qds)
  PLATFORM_FLAG = -DFMAN_V3H
endif

ifeq ($(MACHINE),t4240qds)
  PLATFORM_FLAG = -DFMAN_V3H
endif

ifeq ($(MACHINE),t1040qds)
  PLATFORM_FLAG = -DFMAN_V3L
endif

ifeq ($(MACHINE),ls1043)
  PLATFORM_FLAG = -DLS1043
endif

ifeq ($(MACHINE),ls1046)
  PLATFORM_FLAG = -DLS1043
endif

CFLAGS += $(PLATFORM_FLAG)

ifdef M64BIT
  CFLAGS += -m64
endif

CFLAGS += -DNCSW_LINUX -O2 -D__STDC_LIMIT_MACROS\
          -I$(TCLAP_HEADER_PATH) \
          -I$(LIBXML2_HEADER_PATH) \
          -I$(NET_USPACE_HEADER_PATH)
LDLIBS   = -lspc -lxml2 -lm

ifdef FMCHOSTMODE
  LDFLAGS += -L.
  LDLIBS  += -lz
else
  CFLAGS += -fPIC
  LDFLAGS += -L.
endif

ifdef M64BIT
  LDFLAGS += -m64
endif

CXXFLAGS = $(CFLAGS)

.PHONY: default
ifdef FMCHOSTMODE
default: libspc.a spc
else
default: libspc.a spc
endif

objects = ./libspc.o                                                    \
     ./PDLReader.o ./ConfigReader.o                                                   \
     ./SPCreateCode.o ./SPDumpCode.o ./SPDumpIR.o              \
     ./SPDumpParse.o ./SPIR.o                        \
     ./SPReviseCode.o ./SPReviseIR.o ./SoftParser.o                    \
     ./SPExpr.o ./SPExprLexer.o                                   \
     ./SPModel.o                                                    \
     ./TaskDef.o ./Utils.o ./GenericError.o                    \
     ./spa/dll.o ./spa/sp.o ./spa/sp_assembler.tab.o              \
     ./spa/sp_private.o ./spa/htbl.o ./spa/lex._sp_assembler_yy.o

headers = spc.h GenericError.h \
          SPModel.h PDLReader.h ConfigReader.h SoftParser.h      \
          SPCreateCode.h SPIR.h TaskDef.h Utils.h      \
          SPExpr.hpp logger.hpp 

other_files = ./spc ./softparse.h ./libspc.a ./SPC.o

spc : ./SPC.o ./GenericError.o libspc.a
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

$(objects) : $(headers)

libspc.a : libspc.a($(objects))

.PHONY: clean
clean:
	rm -f $(other_files) $(objects)

.PHONY: dist
dist: clean
	mkdir -p $(PKG_NAME);
	mkdir -p $(PKG_NAME)/source
	mkdir -p $(PKG_NAME)/source/spa;
	mkdir -p $(PKG_NAME)/etc
	cp *.c *.cpp *.h *.hpp Makefile    $(PKG_NAME)/source
	cp spa/*.c spa/*.h                 $(PKG_NAME)/source/spa
	cp -r ../etc/*                     $(PKG_NAME)/etc
	cp ../INSTALL ../COPYING ../README $(PKG_NAME)
	find $(PKG_NAME) -name  CVS   -print0 | xargs -0 /bin/rm -R -f
	find $(PKG_NAME) -name .svn   -print0 | xargs -0 /bin/rm -R -f
	find $(PKG_NAME) -name \*.o   -print0 | xargs -0 /bin/rm -R -f
	find $(PKG_NAME) -name \*.bak -print0 | xargs -0 /bin/rm -R -f
	find $(PKG_NAME) -name \*.org -print0 | xargs -0 /bin/rm -R -f
	tar -czf $(PKG_NAME)-$(PKG_RELEASE).tgz $(PKG_NAME)
	rm -Rf $(PKG_NAME)
