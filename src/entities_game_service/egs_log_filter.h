#ifndef RY_EGS_LOG_FILTER_H
#define RY_EGS_LOG_FILTER_H

#include "nel/net/cvar_log_filter.h"

// Filter to allow control of log by the config file
NL_DECLARE_CVAR_INFO_LOG_FUNCTION(egs_nminfo,  NameManagerLogEnabled,          true)
NL_DECLARE_CVAR_INFO_LOG_FUNCTION(egs_giinfo,  GameItemLogEnabled,             true)
NL_DECLARE_CVAR_INFO_LOG_FUNCTION(egs_ecinfo,  EntityCallbacksLogEnabled,      true)
NL_DECLARE_CVAR_INFO_LOG_FUNCTION(egs_eminfo,  EntityManagerLogEnabled,        true)
NL_DECLARE_CVAR_INFO_LOG_FUNCTION(egs_gminfo,  GuildManagerLogEnabled,         true)
NL_DECLARE_CVAR_INFO_LOG_FUNCTION(egs_feinfo,  ForageExtractionLogEnabled,     true)
NL_DECLARE_CVAR_INFO_LOG_FUNCTION(egs_pminfo,  PhraseManagerLogEnabled,        true)
NL_DECLARE_CVAR_INFO_LOG_FUNCTION(egs_chinfo,  CharacterLogEnabled,            true)
NL_DECLARE_CVAR_INFO_LOG_FUNCTION(egs_plinfo,  PlayerLogEnabled,               true)
NL_DECLARE_CVAR_INFO_LOG_FUNCTION(egs_shinfo,  ShoppingLogEnabled,             true)
NL_DECLARE_CVAR_INFO_LOG_FUNCTION(egs_pvpinfo, PVPLogEnabled,                  true)
NL_DECLARE_CVAR_INFO_LOG_FUNCTION(egs_ppdinfo, PersistentPlayerDataLogEnabled, true)




#endif
