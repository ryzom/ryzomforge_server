/** \file spell_message.h
 * <File description>
 *
 * $Id: effect_message.h,v 1.7 2007/03/09 09:56:52 boucher Exp $
 */



#ifndef RY_EFFECT_MESSAGE_H
#define RY_EFFECT_MESSAGE_H


#include "nel/misc/types_nl.h"

#include "game_share/base_types.h"
#include "game_share/synchronised_message.h"
#include "basic_effect.h"


/**
 * <Class description>
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CAddEffectsMessage: public CMirrorTransportClass
{
public:
	/// Constructor
	CAddEffectsMessage() {}

	/// add an effect
	inline void addEffect( const CBasicEffect &effect )
	{
		Entities.push_back( effect.targetRowId() );
		Creators.push_back( effect.creatorRowId() );
		EffectIds.push_back( effect.effectId() );
		Families.push_back( (uint16) effect.family() );
	}

	/// add a vector of effects
	inline void addEffect( const std::vector< CBasicEffect> &effects )
	{
		std::vector< CBasicEffect>::const_iterator it = effects.begin();
		const std::vector< CBasicEffect>::const_iterator itEnd = effects.end();
		for ( ; it != itEnd ; ++it)
		{
			Entities.push_back( (*it).targetRowId() );
			Creators.push_back( (*it).creatorRowId() );
			EffectIds.push_back( (*it).effectId() );
			Families.push_back( (uint16) (*it).family() );
		}		
	}

	virtual void description ()
	{
		className ("CAddEffectsMessage");

		propertyCont ("Entities", PropDataSetRow, Entities);
		propertyCont ("Creators", PropDataSetRow, Creators);
		propertyCont ("EffectIds", PropUInt32, EffectIds);
		propertyCont ("Families", PropUInt16, Families);
	}
	virtual void callback (const std::string &name, NLNET::TServiceId id);

public:
	std::vector< TDataSetRow >		Creators;
	std::vector< TDataSetRow >		Entities;
	std::vector< uint32 >			EffectIds;
	std::vector< uint16 >			Families;
};


/**
 * <Class description>
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CRemoveEffectsMessage: public CMirrorTransportClass
{
public:
	/// Constructor
	CRemoveEffectsMessage() {}

	virtual void description ()
	{
		className ("CRemoveEffectsMessage");

		propertyCont ("Entities", PropDataSetRow, Entities);
		propertyCont ("EffectIds", PropUInt32, EffectIds);
		propertyCont ("Families", PropUInt16, Families);
	}

	/// add an effect
	inline void addEffect( const CBasicEffect &effect )
	{
		Entities.push_back( effect.targetRowId() );
		EffectIds.push_back( effect.effectId() );
		Families.push_back( (uint16) effect.family() );
	}

	/// add a vector of effects
	inline void addEffect( const std::vector< CBasicEffect> &effects )
	{
		std::vector< CBasicEffect>::const_iterator it = effects.begin();
		const std::vector< CBasicEffect>::const_iterator itEnd = effects.end();
		for ( ; it != itEnd ; ++it)
		{
			Entities.push_back( (*it).targetRowId() );
			EffectIds.push_back( (*it).effectId() );
			Families.push_back( (uint16) (*it).family() );
		}		
	}

	virtual void callback (const std::string &name, NLNET::TServiceId id);

public:
	std::vector< TDataSetRow >	Entities;
	std::vector< uint32 >		EffectIds;
	std::vector< uint16 >		Families;
};


#endif // RY_EFFECT_MESSAGE_H

/* End of effect_message.h */
