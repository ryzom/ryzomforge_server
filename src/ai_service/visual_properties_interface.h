/** \file visual_properties_interface.h
 *
 * $Id: visual_properties_interface.h,v 1.9 2004/03/01 19:19:20 lecroart Exp $
 */




#ifndef RYAI_VISUAL_PROPERTIES_INTERFACE_H
#define RYAI_VISUAL_PROPERTIES_INTERFACE_H

// Includes
/*#include "nel/misc/types_nl.h"
#include "nel/misc/entity_id.h"
#include "ai.h"
*/
//#include "ai_entity_id.h"

#include <string>

// the class
class	CVisualPropertiesInterface
{
public:
	// classic init(), update() and release()
	static void init();
	static void update();
	static void release();

	// set different visual properties for an entity
	static	void setName(const TDataSetRow&	dataSetRow,std::string name);
	
//	static void setMode(CAIEntityId id,MBEHAV::EMode mode);
//	static void setBehaviour(CAIEntityId id,MBEHAV::EBehaviour behaviour);

	// clear all visual property info for an entity when it despawns
	/*static void removeEntity(CAIEntityId id);*/
	static bool UseIdForName;
	static bool ForceNames;
};

#endif
