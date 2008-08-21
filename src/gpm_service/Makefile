#############################################################################
# Simple make file for compiling GPM service

#############################################################################
# Setting up the compiler settings...

# Global variables
include ../../../Variables.mk

# The flags for the C++ compiler
CXXFLAGS     = $(FLAGS_CMN) $(FLAGS_DBG_$(DBG)) \
		-I/usr/include/stlport \
		-I/usr/include/libxml2 \
		-I$(HOME)/cvs/code/nel/include \
		-I$(HOME)/cvs/code/ryzom/src_v2

LDFLAGS      = 	$(LD_FLAGS_CMN) -L$(HOME)/install/$(DIR_DBG_$(DBG))/lib \
		-L$(HOME)/cvs/code/ryzom/src_v2/game_share \
		-L$(HOME)/cvs/code/ryzom/src_v2/r2_share \
		-L../admin_modules \
		-lgame_share \
		-ladmin_modules \
		-lr2_share \
		-lnelligo \
		-lnelpacs \
		-lnelgeorges \
		-lnelnet \
		-lnelmisc \
		-lxml2 \
		-lstlport \
		-lrt\
		-ldl

#############################################################################
# The bit that changes each time we cut paste and hack this file :o)

# The list of targets to build
TARGETS		= gpm_service
DSP_TARGET	= $(TARGETS).dsp
PACKED_SHEETS = \
	continents.packed_sheets \

# The default build rule
all: exe packed_sheets

exe: check-deps $(TARGETS)

$(TARGETS): $(OBJS) ../admin_modules/libadmin_modules.a \
		../game_share/libgame_share.a \
		../r2_share/libr2_share.a
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)
	cp -a $(TARGETS) $(TARGETS)_debug
	strip $(TARGETS)

packed_sheets: $(TARGETS)
	/bin/sh ../update_packed_sheets.sh ./$(TARGETS) $(PACKED_SHEETS)


#############################################################################
# Rules

include ../../../Rules.mk
