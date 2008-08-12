#############################################################################
# Simple make file for compiling NeL examples

#############################################################################
# Setting up the compiler settings...

# Global variables
include ../Variables.mk

# The flags for the C++ compiler
CXXFLAGS     = -DFAST_MIRROR $(FLAGS_CMN) $(FLAGS_DBG_$(DBG)) \
		-I/usr/include/libxml2 \
		-I/usr/include/stlport \
		-I$(HOME)/cvs/code/nel/include \
		-I$(HOME)/cvs/code/ryzom/src_v2


LDFLAGS      = 	$(LD_FLAGS_CMN) -L$(HOME)/install/$(DIR_DBG_$(DBG))/lib \
		-L$(HOME)/cvs/code/ryzom/src_v2/game_share \
		-L../admin_modules \
		-lgame_share \
		-ladmin_modules \
		-lnelgeorges \
		-lnelnet \
		-lnelmisc \
		-lxml2 \
		-lstlport \
		-lrt\
		-ldl

# The flags for the linker
LDFLAGS2      = 	-L$(HOME)/install/$(DIR_DBG_$(DBG))/lib \
		-lnelnet \
		-lxml2 \
		-L/usr/lib \
		-L/usr/X11R6/lib \
		-L$(HOME)/cvs/code/ryzom/src_v2/game_share \
		-lc \
		-lgame_share \
		-lnelgeorges \
		-lnelmisc \
		-lxml2 \
		-lz \
		-lm \
		-lstlport \
		-lpthread \
		-lcrypt


#############################################################################
# The bit that changes each time we cut paste and hack this file :o)

# The list of targets to build
TARGETS		= frontend_service
DSP_TARGET	= $(TARGETS).dsp

# The default build rule
all: exe packed_sheets

exe: check-deps $(TARGETS)

$(TARGETS): $(OBJS) ../admin_modules/libadmin_modules.a \
		../game_share/libgame_share.a
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)
	cp -a $(TARGETS) $(TARGETS)_debug
	strip $(TARGETS)

packed_sheets:
	# this service has no packed_sheets to pack
	# ./$(TARGETS) $(PACK_SHEETS_FLAGS)


#############################################################################
# Rules

include ../Rules.mk

