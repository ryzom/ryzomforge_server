#############################################################################
# Simple make file for compiling AI SHARE

#############################################################################
# Setting up the compiler settings...

# Global variables
include ../Variables.mk

# The flags for the C++ compiler
CXXFLAGS     = $(FLAGS_CMN) $(FLAGS_DBG_$(DBG)) \
		-I/usr/include/stlport \
		-I/usr/include/libxml2 \
		-I$(HOME)/cvs/code/nel/include \
		-I..

LDFLAGS      = 	$(LD_FLAGS_CMN) -L$(HOME)/install/$(DIR_DBG_$(DBG))/lib \
		-L../game_share \
		-lgame_share \
		-lnelnet \
		-lnelmisc \
		-lxml2 \
		-lstlport

# The flags for the linker
LDFLAGS2      = 	-L$(HOME)/install/$(DIR_DBG_$(DBG))/lib \
		-lnelnet \
		-lnelgeorges \
		-lnelpacs \
		-L/usr/lib \
		-L/usr/X11R6/lib \
		-L$(HOME)/cvs/code/ryzom/src_v2/game_share \
		-lnelmisc \
		-lxml2 \
		-lstlport \
		-lpthread

#############################################################################
# The bit that changes each time we cut paste and hack this file :o)

# The list of targets to build
TARGETS		= libai_share.a
DSP_TARGET	= ai_share.dsp

# The default build rule
all:			check-deps $(TARGETS)

#libgame_share.so: $(OBJS)
#	$(CXX) -o $@ $(OBJS) -shared $(LDFLAGS)

libai_share.a: $(OBJS)
	ar r libai_share.a $(OBJS)

#############################################################################
# Rules

include ../Rules.mk

