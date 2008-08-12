/** \file charac_modifier_effect.cpp
 * <Manage effects apply on characteristics modifiers>
 *
 * $Id: charac_modifier_effect.cpp,v 1.6 2007/01/03 16:20:28 coutelas Exp $
 */



#include "stdpch.h"
// net
#include "nel/net/message.h"
//
#include "charac_modifier_effect.h"
#include "phrase_manager/phrase_utilities_functions.h"

#include "entity_manager/entity_base.h"
#include "entity_manager/entity_manager.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;


//--------------------------------------------------------------
//		CCharacteristicModifierEffect::isTimeToUpdate()
//--------------------------------------------------------------
bool CCharacteristicModifierEffect::isTimeToUpdate()
{
	return true;
} // isTimeToUpdate //

//--------------------------------------------------------------
//		CCharacteristicModifierEffect::update()
//--------------------------------------------------------------
bool CCharacteristicModifierEffect::update( uint32 & updateFlag )
{
	if (_AffectedCharac >= CHARACTERISTICS::NUM_CHARACTERISTICS)
		return true;

	if (!TheDataset.isAccessible(_TargetRowId))
		return true;

	CEntityBase *entity = CEntityBaseManager::getEntityBasePtr(_TargetRowId);
	if (!entity)
		return true;

	entity->getCharacteristics()._PhysicalCharacteristics[_AffectedCharac].Modifier = _Modifier + entity->getCharacteristics()._PhysicalCharacteristics[_AffectedCharac].Modifier;
	if( entity->getCharacteristics()._PhysicalCharacteristics[_AffectedCharac].Modifier >= entity->getCharacteristics()._PhysicalCharacteristics[_AffectedCharac].Base )
	{
		entity->getCharacteristics()._PhysicalCharacteristics[_AffectedCharac].Modifier = entity->getCharacteristics()._PhysicalCharacteristics[_AffectedCharac].Base - 1;
	}

	return (_EndDate <= CTickEventHandler::getGameCycle());
} // update //

//--------------------------------------------------------------
//		CCharacteristicModifierEffect::removed()
//--------------------------------------------------------------
void CCharacteristicModifierEffect::removed()
{
	// send messages to clients
	PHRASE_UTILITIES::sendEffectStandardEndMessages(_CreatorRowId, _TargetRowId, _EffectName);
} // removed //

