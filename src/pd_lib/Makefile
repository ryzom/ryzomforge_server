#############################################################################
# Simple make file for compiling PD LIB

#############################################################################
# Setting up the compiler settings...

# Global variables
include ../../../Variables.mk

# The flags for the C++ compiler
CXXFLAGS     = $(FLAGS_CMN) $(FLAGS_DBG_$(DBG)) \
        -I$(HOME)/code/nel/include \
        -I$(RYZOM_PATH)/common/src \
		-I/usr/include/libxml2 \
		-I./

# The flags for the linker
LDFLAGS      = $(LD_FLAGS_CMN) \
        -L$(NEL_PATH)/lib \
        -L$(RYZOM_PATH)/common/src/game_share \
		-lnelnet \
		-L/usr/lib \
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
DSP_TARGET	= pd_lib.vcproj

# The default build rule
all:			check-deps $(TARGETS)


#libgame_share.so: $(OBJS)
#	$(CXX) -o $@ $(OBJS) -shared $(LDFLAGS)

libpd_lib.a: $(OBJS)
	ar r libpd_lib.a $(OBJS)

#############################################################################
# Rules

include ../../../Rules.mk
