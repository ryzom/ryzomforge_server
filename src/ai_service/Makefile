#############################################################################
# Simple make file for compiling AI SERVICE

#############################################################################
# Setting up the compiler settings...

# Global variables
include ../Variables.mk

# The flags for the C++ compiler
CXXFLAGS     = $(FLAGS_CMN) $(FLAGS_DBG_$(DBG)) \
		-I/usr/include/stlport \
		-I/usr/include/libxml2 \
		-I$(HOME)/cvs/code/nel/include \
		-I.. \
		-I../ai_share

# The flags for the linker
LDFLAGS      = 	$(LD_FLAGS_CMN) -L$(HOME)/install/$(DIR_DBG_$(DBG))/lib \
		-L../game_share \
		-L../admin_modules \
		-L../ai_share \
		-L../r2_share \
		-L../r2_modules \
		-lai_share \
		-ladmin_modules \
		-lr2_modules \
		-lr2_share \
		-lgame_share \
		-lnelnet \
		-lnelgeorges \
		-lnelligo \
		-lnelmisc \
		-lxml2 \
		-lstlport \
		-lrt\
		-ldl

#############################################################################
# The bit that changes each time we cut paste and hack this file :o)

# The list of targets to build
TARGETS		= ai_service
DSP_TARGET	= $(TARGETS).dsp
PACKED_SHEETS = \
	ais.packed_sheets \
	ais_action.packed_sheets \
	ais_fight_config.packed_sheets \
	ais_race_stats.packed_sheets

# The default build rule
all: exe packed_sheets

exe: check-deps $(TARGETS)

$(TARGETS): $(OBJS) ../admin_modules/libadmin_modules.a \
		../game_share/libgame_share.a \
		../r2_share/libr2_share.a \
		../r2_modules/libr2_modules.a
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)
	cp -a $(TARGETS) $(TARGETS)_debug
	strip $(TARGETS)

packed_sheets: $(TARGETS)
	/bin/sh ../update_packed_sheets.sh ./$(TARGETS) $(PACKED_SHEETS)


#############################################################################
# Rules

include ../Rules.mk
