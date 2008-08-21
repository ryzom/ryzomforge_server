#############################################################################
# Setting up the compiler settings...

# Global variables
include ../../../Variables.mk

# The flags for the C++ compiler
CXXFLAGS     = $(FLAGS_CMN) $(FLAGS_DBG_$(DBG)) \
		-I/usr/include/libxml2 \
		-I$(NEL_INCLUDE) \
		-I$(RYZOM_COMMON_SRC) \
		-I.. \
		-I../ai_share

# The flags for the linker
LDFLAGS      = 	$(LD_FLAGS_CMN) \
		-L$(NEL_PATH)/lib \
		-L$(RYZOM_COMMON_SRC)/game_share \
		-L../admin_modules \
		-L$(RYZOM_COMMON_SRC)/r2_share \
		-L$(RYZOM_COMMON_SRC)/r2_modules \
		-L../admin_modules \
		-L../ai_share \
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
		-lrt\
		-ldl

#############################################################################
# The bit that changes each time we cut paste and hack this file :o)

# The list of targets to build
TARGETS		= ai_service
DSP_TARGET	= $(TARGETS).vcproj
PACKED_SHEETS = \
	ais.packed_sheets \
	ais_action.packed_sheets \
	ais_fight_config.packed_sheets \
	ais_race_stats.packed_sheets

# The default build rule
all: exe packed_sheets

exe: check-deps $(TARGETS)

$(TARGETS): $(OBJS) ../admin_modules/libadmin_modules.a \
        ../../../common/src/game_share/libgame_share.a \
        ../../../common/src/r2_share/libr2_share.a \
        ../../../common/src/r2_modules/libr2_modules.a
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)
	cp -a $(TARGETS) $(TARGETS)_debug
	strip $(TARGETS)

packed_sheets: $(TARGETS)
#todo	/bin/sh ../update_packed_sheets.sh ./$(TARGETS) $(PACKED_SHEETS)


#############################################################################
# Rules

include ../../../Rules.mk
