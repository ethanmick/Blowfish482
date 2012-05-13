#
# Created by gmakemake (Sparc Oct 22 2010) on Tue Apr  3 15:32:54 2012
#

#
# Definitions
#

.SUFFIXES:
.SUFFIXES:	.a .o .c .C .cpp .s
.c.o:
		$(COMPILE.c) $<
.C.o:
		$(COMPILE.cc) $<
.cpp.o:
		$(COMPILE.cc) $<
.s.o:
		$(COMPILE.cc) $<
.c.a:
		$(COMPILE.c) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.C.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%
.cpp.a:
		$(COMPILE.cc) -o $% $<
		$(AR) $(ARFLAGS) $@ $%
		$(RM) $%

CC =		gcc
CXX =		g++

RM = rm -f
AR = ar
LINK.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)
COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) -c
COMPILE.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) -c

########## Default flags (redefine these with a header.mak file if desired)
CXXFLAGS =	-ggdb -Wall -pg
CFLAGS =	-ggdb -Wall -pg
CLIBFLAGS =	-lm
CCLIBFLAGS =	
########## End of default flags


CPP_FILES =	Blowfish.cpp
C_FILES =	
S_FILES =	
H_FILES =	BlockCipher.h Blowfish.h
SOURCEFILES =	$(H_FILES) $(CPP_FILES) $(C_FILES) $(S_FILES)
.PRECIOUS:	$(SOURCEFILES)
OBJFILES =	

#
# Main targets
#

all:	Blowfish 

Blowfish:	Blowfish.o $(OBJFILES)
	$(CXX) $(CXXFLAGS) -o Blowfish Blowfish.o $(OBJFILES) $(CCLIBFLAGS)

#
# Dependencies
#

Blowfish.o:	BlockCipher.h Blowfish.h

#
# Housekeeping
#

Archive:	archive.tgz

archive.tgz:	$(SOURCEFILES) Makefile
	tar cf - $(SOURCEFILES) Makefile | gzip > archive.tgz

clean:
	-/bin/rm $(OBJFILES) Blowfish.o core 2> /dev/null

realclean:        clean
	-/bin/rm -rf Blowfish 
