#############################################################################
# Setting up the global compiler settings...

# The names of the executables
CXX           = c++
RM            = rm -f
MAKE          = make

DBG           = off

ifeq (RyzomCompilerFlags.mk,$(wildcard RyzomCompilerFlags.mk))
include RyzomCompilerFlags.mk
endif
FLAGS_CMN     = -g -pipe -Wno-ctor-dtor-privacy -Wno-multichar -D_REENTRANT -D_GNU_SOURCE $(RYZOM_VERSION_COMPILER_FLAGS)
LD_FLAGS_CMN  = -rdynamic 

FLAGS_DBG_on  = -O0 -finline-functions -DNL_DEBUG -DNL_DEBUG_FAST
FLAGS_DBG_off = -O3 -ftemplate-depth-24 -funroll-loops -DNL_RELEASE_DEBUG
DIR_DBG_on    = debug
DIR_DBG_off   = release

PACK_SHEETS_FLAGS = -A/home/nevrax/cvs/code/ryzom -L/home/nevrax/cvs/code/ryzom -C/home/nevrax/cvs/code/ryzom/sheet_pack_cfg -Q --nons

ifeq (Objects.mk,$(wildcard Objects.mk))
include Objects.mk
endif
