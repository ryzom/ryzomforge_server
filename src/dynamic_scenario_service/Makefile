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
		-L../game_share \
		-L../admin_modules \
		-L../ai_share \
		-L../r2_share \
		-L../r2_modules \
		-lr2_modules \
		-lr2_share \
		-lai_share \
		-lgame_share \
		-ladmin_modules \
		-lnelnet \
		-lnelgeorges \
		-lnelligo \
		-lnelmisc \
		-lxml2 \
		-lrt\
		-ldl\
		-lz

#############################################################################
# The bit that changes each time we cut paste and hack this file :o)

# The list of targets to build
TARGETS		= dynamic_scenario_service
DSP_TARGET	= $(TARGETS).vcproj

# The default build rule
all: exe packed_sheets

exe: check-deps $(TARGETS)

$(TARGETS): $(OBJS) ../admin_modules/libadmin_modules.a \
		../game_share/libgame_share.a \
		../ai_share/libai_share.a \
		../r2_share/libr2_share.a \
		../r2_modules/libr2_modules.a
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)
	cp -a $(TARGETS) $(TARGETS)_debug
	strip $(TARGETS)

packed_sheets:
	# this service has no packed_sheets to pack
	# ./$(TARGETS) $(PACK_SHEETS_FLAGS)


#############################################################################
# Rules

include ../../../Rules.mk

