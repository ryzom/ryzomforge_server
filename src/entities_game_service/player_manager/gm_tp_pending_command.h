/** \file gm_tp_pending_command.h
 * 
 *
 * $Id: gm_tp_pending_command.h,v 1.8 2006/07/12 14:37:37 boucher Exp $
 */

#ifndef GM_TP_PENDING_COMMAND_H
#define GM_TP_PENDING_COMMAND_H

#include "server_share/entity_state.h"

#include <map>
#include <string>

class CCharacter;

/**
 * CGmTpPendingCommand
 *
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2004
 */
class CGmTpPendingCommand
{
	NL_INSTANCE_COUNTER_DECL(CGmTpPendingCommand);
public:

	typedef std::map< std::string, COfflineEntityState > TCharacterTpPending;
	
	// constructor
	CGmTpPendingCommand();
	
	// destructor
	~CGmTpPendingCommand();
	
	// get singleton instance
	static CGmTpPendingCommand * getInstance();
	
	// return true if we have tp pending and file state
	bool getTpPendingforCharacter( const std::string& CharacterName, COfflineEntityState& state, CCharacter& character );

	// add tp pending command
	void addTpPendingforCharacter( const std::string& CharacterName, const COfflineEntityState& state );

	// save map of tp pending
	void saveMap();

	// release
	static void release() { if( _Instance != 0 ) delete _Instance; } 

protected:

private:
	TCharacterTpPending _CharacterTpPending;

	static CGmTpPendingCommand * _Instance;
};

//typedef NLMISC::CDbgPtr<IEntity> IEntityPtr;

#endif //GM_TP_PENDING_COMMAND_H
