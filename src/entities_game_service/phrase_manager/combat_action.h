/** \file combat_action.h
 * <File description>
 *
 * $Id: combat_action.h,v 1.26 2005/06/23 18:14:20 boucher Exp $
 */


#ifndef RY_COMBAT_ACTION_H
#define RY_COMBAT_ACTION_H

//
#include "egs_sheets/egs_static_ai_action.h"
#include "entity_manager/entity_base.h"

class CCombatPhrase;

/**
 * <Class description>
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CCombatAction
{
	NL_INSTANCE_COUNTER_DECL(CCombatAction);
public:

	/// Constructor
	CCombatAction() : _CombatPhrase(NULL), _ApplyOnTargets(true)
	{}

	/// validate the combat action
	virtual bool validate(CCombatPhrase *phrase, std::string &errorCode) { return true; }

	/// apply combat action effects
	virtual void apply(CCombatPhrase *phrase) {}

	/// 
	inline bool applyOnTargets() const { return _ApplyOnTargets; }
	inline void applyOnTargets(bool b) { _ApplyOnTargets = b; }

	/// apply on entity
	virtual void applyOnEntity( CEntityBase *entity, float successFactor ) {}
protected:	
	/// action actor
	TDataSetRow		_ActorRowId;
	/// flag indicating if the action is done on the combat phrase targets or actor
	bool			_ApplyOnTargets;
	/// related combat phrase
	CCombatPhrase	*_CombatPhrase;
};


/**
 * <Class description>
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CCombatDynamicAction : public CCombatAction
{
public:
	/// Constructor
	CCombatDynamicAction() : CCombatAction(), _MinValue(1.0f), _MaxValue(1.0f), _PowerValue(0)
	{}

	/// get value to apply
	inline float getApplyValue(uint16 ref)
	{
		if (_PowerValue == 0) return _MinValue;
		if (_PowerValue>=ref) return _MaxValue; // so ref cannot be = 0 as _SabrinaValue is uint
		return (_MinValue + (_MaxValue - _MinValue) * float(_PowerValue)/ref );
	}

	inline void setDynValues(float minValue, float maxValue, uint16 powerValue)
	{
		_MinValue = minValue;
		_MaxValue = maxValue;
		_PowerValue = powerValue;
	}

protected:
	/// min value
	float	_MinValue;
	/// max value
	float	_MaxValue;
	/// power value
	uint16	_PowerValue;
};

/**
 * <Class description>
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CCombatAIActionFactory
{
	NL_INSTANCE_COUNTER_DECL(CCombatAIActionFactory);
public:

	/// clear the class factory
	static void clear();

	/**
	 * Build the desired step from a primitive node
	 * \param prim : the primitive node used to build the step
	 * \return a pointer on the built step (NULL if failure)
	 */
	static CCombatAction * buildAiAction(const CStaticAiAction *aiAction, CCombatPhrase * phrase );

protected:
	///\init the factories
	inline static void init()
	{
		if( !Factories )
			Factories = new std::vector< std::pair< AI_ACTION::TAiEffectType, CCombatAIActionFactory* > >;
	}
	/**
	 * Create a step from parameters
	 * \param params : a vector of vector of strings describing the step params
	 * \return a pointer on the built step (NULL if failure)
	 */
	virtual CCombatAction * build(const CStaticAiAction *aiAction, CCombatPhrase * phrase ) = 0;

	///the phrase factories. We use a pointer here because we cant control the order inwhich ctor of static members are called
	static std::vector< std::pair< AI_ACTION::TAiEffectType, CCombatAIActionFactory* > >* Factories;
};


/**
 * Combat action template factory
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
template <class T> class CCombatAIActionTFactory : public CCombatAIActionFactory
{
public:
	explicit CCombatAIActionTFactory(AI_ACTION::TAiEffectType type)
	{
		CCombatAIActionFactory::init();
		
#ifdef NL_DEBUG
		// check this type isn't used yet
		for (uint i = 0; i < Factories->size(); i++ )
		{
			if ( (*Factories)[i].first == type )
			{
				nlstop;
			}
		}
#endif
		// add factory
		Factories->push_back(std::make_pair( type ,this));
	};

	/// build method
	CCombatAction *build(const CStaticAiAction *aiAction, CCombatPhrase * phrase)
	{
		T *instance = new T;
		if (!instance)
		{
			nlwarning("<CCombatAIActionTFactory> failed to allocate element of template type");
			return 0;
		}
		if ( !instance->initFromAiAction(aiAction,phrase) )
		{
			delete instance;
			return 0;
		}
		return instance;
	}
};



#endif // RY_COMBAT_ACTION_H

/* End of combat_action.h */
