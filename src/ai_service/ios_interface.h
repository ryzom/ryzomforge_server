/** \file egs_interface.h
 *
 * $Id: ios_interface.h,v 1.4 2004/03/01 19:19:20 lecroart Exp $
 */




#ifndef RYAI_IOS_INTERFACE_H
#define RYAI_IOS_INTERFACE_H

// Include
#include "nel/net/unified_network.h"
#include "nel/misc/types_nl.h"
#include "nel/misc/entity_id.h"
#include "nel/misc/sheet_id.h"

//#include "ai_entity_id.h"


// the class
class CIOSInterface
{
public:
	// classic init(), update() and release()
	static void init();
	static void update();
	static void release();

	// add bots to the world, remove them from the world or move them
	static void addEntity(CAIEntityId id, NLMISC::CSheetId sheet);
	static void removeEntity(CAIEntityId id);

private:
	// messages that are filled up by the above static methods
	// messages are dispatched when a threshold size is reached
	// the messages are also flushed by update()
	//static NLNET::CMessage _addEntityMsg;
	//static NLNET::CMessage _removeEntityMsg;
};

#endif
