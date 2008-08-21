/** \file gm_tp_pending_command.cpp
 * 
 *
 * $Id: gm_tp_pending_command.cpp,v 1.9 2006/07/12 14:37:37 boucher Exp $
 */

#include "stdpch.h"

// misc
#include "nel/misc/file.h"
#include "nel/net/service.h"
#include "game_share/backup_service_interface.h"

#include "player_manager/gm_tp_pending_command.h"
#include "player_manager/character.h"
#include "zone_manager.h"

CGmTpPendingCommand * CGmTpPendingCommand::_Instance = 0;

using namespace std;
using namespace NLMISC;
using namespace NLNET;

NL_INSTANCE_COUNTER_IMPL(CGmTpPendingCommand);

//-----------------------------------------------------------------------------
CGmTpPendingCommand::CGmTpPendingCommand()
{
	CIFile f;
	string fileName = Bsi.getLocalPath() + toString("gm_pending_tp.bin");
	bool open = f.open(fileName);
	if( open )
	{
		f.serialCont( _CharacterTpPending );
	}
	f.close();
}

//-----------------------------------------------------------------------------
CGmTpPendingCommand::~CGmTpPendingCommand()
{
	_CharacterTpPending.clear();
}

//-----------------------------------------------------------------------------
CGmTpPendingCommand * CGmTpPendingCommand::getInstance()
{ 
	if( _Instance == 0 )
	{
		_Instance = new CGmTpPendingCommand();
	}
	return _Instance;
}

//-----------------------------------------------------------------------------
void CGmTpPendingCommand::saveMap()
{
	CMemStream stream;
	string fileName = toString("gm_pending_tp.bin");
	
	stream.serialCont( _CharacterTpPending );

	CBackupMsgSaveFile msg( fileName, CBackupMsgSaveFile::SaveFile, Bsi );
	msg.DataMsg.serialBuffer((uint8*)stream.buffer(), stream.size());
	Bsi.sendFile( msg );
}

//-----------------------------------------------------------------------------
bool CGmTpPendingCommand::getTpPendingforCharacter( const std::string& CharacterName, COfflineEntityState& state, CCharacter& character )
{
	TCharacterTpPending::iterator it = _CharacterTpPending.find( CharacterName );
	if( it == _CharacterTpPending.end() )
	{
		return false;
	}
	else
	{
		state = (*it).second;
		_CharacterTpPending.erase( it );
		saveMap();
		if( character.getCurrentContinent() == CONTINENT::NEWBIELAND )
		{
			CContinent * cont = CZoneManager::getInstance().getContinent(state.X, state.Y);
			if(cont == 0)
				return false;
			if((CONTINENT::TContinent)cont->getId() != CONTINENT::NEWBIELAND )
				return false;
		}
		return true;
	}
}

//-----------------------------------------------------------------------------
void CGmTpPendingCommand::addTpPendingforCharacter( const std::string& CharacterName, const COfflineEntityState& state )
{
	TCharacterTpPending::iterator it = _CharacterTpPending.find( CharacterName );
	if( it == _CharacterTpPending.end() )
	{
		_CharacterTpPending.insert( make_pair( CharacterName, state ) );
	}
	else
	{
		(*it).second = state;
	}
	saveMap();
}
