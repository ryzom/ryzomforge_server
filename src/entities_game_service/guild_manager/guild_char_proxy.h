/** \file guild_char_proxy.h
 * <File description>
 *
 * $Id: guild_char_proxy.h,v 1.12 2006/10/25 08:50:15 saffray Exp $
 */

#ifndef RY_GUILD_CHAR_PROXY_H
#define RY_GUILD_CHAR_PROXY_H

#include "gameplay_module_lib/gameplay_module_lib.h"
#include "game_share/string_manager_sender.h"
#include "egs_pd.h"
//#include "player_manager/character.h"

class CCreature;

/**
 * a proxy to the character in the guild system
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CGuildCharProxy : public IModuleProxy<CCharacter>
{
public:
	/// ctor. used to build a proxy from a module ( use IModule::getProxy( CGuildCharProxy ) )
	CGuildCharProxy();
	// ctor*. Used to build the proxy from a character
	CGuildCharProxy( IModuleCore * user );

	// get a child module of the core of this proxy
	template <class T> bool getModule( T* & module )
	{
		return _ModuleCore->getModuleParent().getModule( module );
	}
	
	///\name The following methods are self-explanatory : the are just accessors to the module core
	//@{
	const EGSPD::TCharacterId & getId();
	const TDataSetRow & getRowId();
	void cancelAFK();
	CCreature * getInterlocutor();
	CModuleParent & getModuleParent();
	void sendSystemMessage( const std::string &  msg, const TVectorParamCheck & params  =  TVectorParamCheck() );
	void sendDynamicMessageToChatGroup( const std::string &  msg, CChatGroup::TGroupType type, const TVectorParamCheck & params  =  TVectorParamCheck() );
	uint64 getMoney();
	void spendMoney(uint64 money);
	void endBotChat();
	bool getTarget(CGuildCharProxy & proxy);
	void setGuildId(uint32 guildId );
	uint32 getGuildId();
	void updateTarget();
	uint16 getMainPlace();
	void updateTargetingChars();
	const TDataSetRow & getEntityRowId();
	void tpWanted( sint32 x, sint32 y, sint32 z , bool useHeading = false, float heading = 0.0f , uint8 continent = 0xFF, sint32 cell = 0);
	void updateOutpostAdminFlagInDB();
	//@}
};
#endif // RY_GUILD_CHAR_PROXY_H

/* End of guild_char_proxy.h */
