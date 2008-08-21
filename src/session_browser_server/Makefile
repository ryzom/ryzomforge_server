#############################################################################
# Simple make file for compiling SESSION BROWSER SERVER service

#############################################################################
# Setting up the compiler settings...

# Global variables
include ../../../Variables.mk

# The flags for the C++ compiler
CXXFLAGS     = $(FLAGS_CMN) $(FLAGS_DBG_$(DBG)) \
		-I/usr/include/stlport \
		-I/usr/include/libxml2 \
		-I/usr/include/mysql \
		-I$(HOME)/cvs/code/nel/include \
		-I$(HOME)/cvs/code/ryzom/src_v2 \
		-I./ 

LDFLAGS      = $(LD_FLAGS_CMN) 	-L$(HOME)/install/$(DIR_DBG_$(DBG))/lib \
		-L$(HOME)/cvs/code/ryzom/src_v2/game_share \
		-L$(HOME)/cvs/code/ryzom/src_v2/admin_modules \
		-L$(HOME)/cvs/code/ryzom/src_v2/r2_share \
		-lmysqlclient \
		-lgame_share \
		-ladmin_modules \
		-lr2_share \
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
TARGETS		= session_browser_server
DSP_TARGET	= $(TARGETS).dsp

# The default build rule
all: exe packed_sheets

exe: check-deps $(TARGETS)

$(TARGETS): $(OBJS) \
		../admin_modules/libadmin_modules.a \
		../game_share/libgame_share.a \
		../r2_share/libr2_share.a
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)
	cp -a $(TARGETS) $(TARGETS)_debug
	strip $(TARGETS)

packed_sheets:
	# this service has no packed_sheets to pack
	# ./$(TARGETS) $(PACK_SHEETS_FLAGS)


#############################################################################
# Rules

include ../../../Rules.mk

