/** \file effect_message.cpp
 * <File description>
 *
 * $Id: effect_message.cpp,v 1.6 2007/03/09 09:56:52 boucher Exp $
 */



#include "stdpch.h"
#include "effect_message.h"
#include "effect_manager.h"



//--------------------------------------------------------------
//				CAddEffectsMessage::callback()  
//--------------------------------------------------------------
void CAddEffectsMessage::callback(const std::string &name, NLNET::TServiceId sid)
{
	std::vector< TDataSetRow >::const_iterator	itEntities;
	std::vector< uint32 >::const_iterator		itEffectId = EffectIds.begin();
	std::vector< uint16 >::const_iterator		itFamilies = Families.begin();
	std::vector< TDataSetRow >::const_iterator	itCreators =  Creators.begin();

	if ( Entities.size() != EffectIds.size() || EffectIds.size() != Families.size() || Creators.size() != EffectIds.size() )
	{
		nlwarning("<CAddEffectsMessage::callback> ERROR : different size for the vectors (%u entities), (%u effects), (%u families)",Entities.size(), EffectIds.size(), Families.size());
		return;
	}

	const std::vector< TDataSetRow >::const_iterator itEntitiesEnd = Entities.end();

	for (itEntities = Entities.begin() ; itEntities != itEntitiesEnd ; ++itEntities )
	{
		CBasicEffect effect( (EFFECT_FAMILIES::TEffectFamily) (*itFamilies), *itCreators ,*itEntities ,*itEffectId);
		CEffectManager::addEffect( *itEntities, effect );

		++itEffectId;
		++itFamilies;
		++itCreators;
	}

} // CAddEffectsMessage::callback //



//--------------------------------------------------------------
//				CRemoveEffectsMessage::callback()  
//--------------------------------------------------------------
void CRemoveEffectsMessage::callback(const std::string &name, NLNET::TServiceId sid)
{
	std::vector< TDataSetRow >::const_iterator	itEntities;
	std::vector< uint32 >::const_iterator		itEffectId = EffectIds.begin();

	if ( Entities.size() != EffectIds.size() )
	{
		nlwarning("<CRemoveEffectsMessage::callback> ERROR : different size for the vectors (%u entities), (%u effects id)",Entities.size(), EffectIds.size() );
		return;
	}

	const std::vector< TDataSetRow >::const_iterator itEntitiesEnd = Entities.end();

	for (itEntities = Entities.begin() ; itEntities != itEntitiesEnd ; ++itEntities )
	{
		CEffectManager::removeEffect( *itEntities, *itEffectId );

		++itEffectId;
	}
} // CRemoveEffectsMessage::callback //


