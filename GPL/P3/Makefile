# updated 2/14/2016

# This Makefile should work for p3 - p8
#
# It makes three assumptions:
#
# (1) the name of the directory is the phase name (e.g. p3, p4, etc)
#
# (2) every .cpp file in this directory is part of the gpl project
#     if you want to keep other .cpp files in this directory you will need to
#     replace "C++SRC = $(wildcard *.cpp)" with a list of files of the form
#     "C++SRC = file1.cpp file2.cpp file3.cpp"
#
# (3) This makefile uses the uname utility to determine if the current OS 
#     is Linux or OS X.  It expects "$ uname" to return "Linux" on a Linux 
#     computer and "Darwin" on a Mac
#

CXX = g++
CPPFLAGS = -std=c++11 -g -MMD 
CPPWARNINGS = -Wall -pedantic

KERNEL_NAME := $(shell sh -c 'uname -s 2>/dev/null || echo not')

# assume the current directory is the phase name
#   /home/.../p4   is the directory where you will keep p4
PHASE := $(notdir $(CURDIR))

# set up the command line options to define pre-processor variables
# -DSYMBOL_TABLE has same effect of adding "#define SYMBOL_TABLE" to .cpp file
# SYMBOL_TABLE and GRAPHICS are used by my public code
#   SYMBOL_TABLE turns on the symbol_table for p4-p8
#   GRAPHICS turns on graphics for p6-p8
# P5 P6 P7 P8 are used by my private code so I can use the same file for 
#   multiple phases.  You may use them if you want.
ifeq ($(PHASE),P3)
  MACRO_DEFINITIONS = -DP3
else ifeq ($(PHASE),p4)
  MACRO_DEFINITIONS = -DSYMBOL_TABLE -DP4
else ifeq ($(PHASE),p5)
  MACRO_DEFINITIONS = -DSYMBOL_TABLE -DP5
else ifeq ($(PHASE),p6)
  MACRO_DEFINITIONS = -DSYMBOL_TABLE -DGRAPHICS -DP5 -DP6
else ifeq ($(PHASE),p7)
  MACRO_DEFINITIONS = -DSYMBOL_TABLE -DGRAPHICS -DP5 -DP6 -DP7
else ifeq ($(PHASE),p8)
  MACRO_DEFINITIONS = -DSYMBOL_TABLE -DGRAPHICS -DP5 -DP6 -DP7 -DP8
else
  PHASE = UNKNOWN PHASE: THIS IS AN ERROR (bad directory name, must be p3,p4,...p8)
endif

# if this is a Linux computer, set up Linux libraries
ifeq ($(KERNEL_NAME),Linux)
  LIBDIRS  = -L/usr/X11R6/lib
  LIBS = -lX11 -lglut -lGL -lGLU -lm -lfl
endif

# if this is a Mac computer, set up Mac libraries
ifeq ($(KERNEL_NAME),Darwin)
  LIBS = -framework GLUT -framework OpenGL -lobjc
  CPPFLAGS += -I/System/Library/Frameworks/GLUT.framework/Versions/A/Headers
endif

# C++SRC is a list of all .cpp files in current directory
#   assumes every .cpp file in current directory is part of gpl
#   replace $(wildcard *.cpp) with a list of files if you keep 
#   non-gpl .cpp files in this directory
C++SRC = $(wildcard *.cpp)

# create a list of object files by substituting the .cpp in above list with .o
C++OBJ = $(C++SRC:%.cpp=%.o)

# create a list of dependency file (generated with g++ -MMD)
C++DEP = $(C++SRC:%.cpp=%.d)

# compile the gpl executable
# this Makefile depends on the source being in a directory named
#   for the current phase (p3, p4, ..., p8).  It will not work if 
#   it is in a different directory.  PHRASE set to error when the
#   directory is not a legal directory.
gpl: y.tab.o lex.yy.o $(C++OBJ)
	@echo "--------------------------------------------------------------------"
	@echo " compiling phase $(PHASE) "
	@echo "--------------------------------------------------------------------"
	$(CXX) -g -o gpl y.tab.o lex.yy.o $(C++OBJ) $(LIBDIRS) $(LIBS)

# compiling gpl.cpp is phase dependent (MACRO_DEFINITIONS (defined above) 
# holds the phase dependent macro definitions)
gpl.o: gpl.cpp Makefile y.tab.o lex.yy.o
	$(CXX) $(CPPFLAGS) $(CPPWARNINGS) $(MACRO_DEFINITIONS) -c gpl.cpp

y.tab.c y.tab.h: gpl.y
	bison -vyd gpl.y

y.tab.o: gpl.y
	bison -vyd gpl.y
	$(CXX) $(CPPFLAGS) $(MACRO_DEFINITIONS) -w -c y.tab.c

lex.yy.c: gpl.l
	flex gpl.l

lex.yy.o: lex.yy.c y.tab.h 
	$(CXX) $(CPPFLAGS) $(MACRO_DEFINITIONS) -c lex.yy.c

# pattern rule to compile all the .cpp files
%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CPPWARNINGS) $(MACRO_DEFINITIONS) -c $< -o $@
	
# include dependency files (.d file) generated by g++
-include $(C++DEP)

clean:
	rm -f $(C++OBJ) $(C++DEP) gpl lex.yy.c lex.yy.o lex.yy.d \
	y.output y.tab.h y.tab.c y.tab.d y.tab.o *.gch
	rm -rf results
