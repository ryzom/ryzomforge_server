#############################################################################
# Simple make file for compiling PD LIB

#############################################################################
# Setting up the compiler settings...

# Global variables
include ../Variables.mk

# The flags for the C++ compiler
CXXFLAGS     = $(FLAGS_CMN) $(FLAGS_DBG_$(DBG)) \
		-I/usr/include/stlport \
		-I/usr/include/libxml2 \
		-I$(HOME)/cvs/code/nel/include \
		-I$(HOME)/cvs/code/ryzom/src_v2 \
		-I./ \

# The flags for the linker
LDFLAGS      = $(LD_FLAGS_CMN) 	-L$(HOME)/install/$(DIR_DBG_$(DBG))/lib \
		-lnelnet \
		-L/usr/lib \
		-L$(HOME)/cvs/code/ryzom/src_v2/game_share \
		-L/usr/X11R6/lib \
		-lnelmisc \
		-lxml2 \
		-lstlport \
		-lpthread \
		-lgame_share

#############################################################################
# The bit that changes each time we cut paste and hack this file :o)

# The list of targets to build
TARGETS		= libpd_lib.a
DSP_TARGET	= pd_lib.dsp

# The default build rule
all:			check-deps $(TARGETS)


#libgame_share.so: $(OBJS)
#	$(CXX) -o $@ $(OBJS) -shared $(LDFLAGS)

libpd_lib.a: $(OBJS)
	ar r libpd_lib.a $(OBJS)

#############################################################################
# Rules

include ../Rules.mk

