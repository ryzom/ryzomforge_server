#############################################################################
# Simple make file for compiling AI SERVICE

#############################################################################
# Setting up the compiler settings...

# Global variables
include ../../../Variables.mk

# The flags for the C++ compiler
CXXFLAGS     = $(FLAGS_CMN) $(FLAGS_DBG_$(DBG)) \
		-I/usr/include/stlport \
		-I/usr/include/libxml2 \
		-I$(HOME)/cvs/code/nel/include \
		-I..

# The flags for the linker
LDFLAGS      = $(LD_FLAGS_CMN) -L$(HOME)/install/$(DIR_DBG_$(DBG))/lib \
		-L../game_share \
		-lgame_share \
		-lnelnet \
		-lnelgeorges \
		-lnelligo \
		-lnelpacs \
		-lnelmisc \
		-lxml2 \
		-lstlport

#############################################################################
# The bit that changes each time we cut paste and hack this file :o)

# The list of targets to build
TARGETS		= ags_test
DSP_TARGET  = $(TARGETS).dsp

# The default build rule
all:			check-deps $(TARGETS)

ags_test: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

#############################################################################
# Rules

include ../../../Rules.mk

