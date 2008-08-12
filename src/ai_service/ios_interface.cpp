/** \file egs_interface.cpp
 *
 * $Id: ios_interface.cpp,v 1.6 2004/03/01 19:19:20 lecroart Exp $
 */



// Include
#include "nel/net/unified_network.h"
#include "game_share/tick_event_handler.h"
#include "ios_interface.h"

using namespace NLMISC;
using namespace NLNET;
using namespace std;


// classic init(), update() and release()
void CIOSInterface::init()
{
}
void CIOSInterface::update()
{
	// flush output messages
}
void CIOSInterface::release()
{
}

// add entities to the world, remove them from the world or move them in the world
void CIOSInterface::addEntity(CAIEntityId id, NLMISC::CSheetId sheet)
{
	nlstop;
	
	NLMISC::CEntityId eid=id.toEntityId();

	// send creature to IOS
	CMessage msgOPS("ADD_CREATURE");
	msgOPS.serial( eid );
	msgOPS.serial( sheet );
	sendMessageViaMirror("IOS", msgOPS);

}


void CIOSInterface::removeEntity(CAIEntityId id)
{
	NLMISC::CEntityId eid=id.toEntityId();

	// remove the actor from the IOS
	CMessage msgOPS("REMOVE_CREATURE");
	msgOPS.serial( eid );
	sendMessageViaMirror( "IOS", msgOPS );
}

