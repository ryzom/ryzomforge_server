/** \file effect_factory.h
 * <File description>
 *
 * $Id: effect_factory.h,v 1.7 2005/06/23 18:14:20 boucher Exp $
 */



#ifndef RY_EFFECT_FACTORY_H
#define RY_EFFECT_FACTORY_H

#include "game_share/effect_families.h"
#include "phrase_manager/s_effect.h"
#include "phrase_manager/phrase_utilities_functions.h"

/**
 * class factory for sabrina Effects, built from Effect Families
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class IEffectFactory
{
	NL_INSTANCE_COUNTER_DECL(IEffectFactory);
public:

	/// clear the class factory
	static void clear();

	/**
	 * Build the desired step from a primitive node
	 * \param prim : the primitive node used to build the step
	 * \return a pointer on the built step (NULL if failure)
	 */
	inline static CSTimedEffect * buildEffect(EFFECT_FAMILIES::TEffectFamily effectFamily)
	{
		//get appropriate factory
		for ( uint i = 0; i < Factories->size(); i++ )
		{
			if ( (*Factories)[i].first == effectFamily )
			{
				INFOLOG(" effect family %s is managed by the system. Building effect...",EFFECT_FAMILIES::toString(effectFamily).c_str());
				return (*Factories)[i].second->buildEffect();
			}
		}
		nlwarning( "<IEffectFactory buildEffect> the effect %s has no corresponding effect class", EFFECT_FAMILIES::toString(effectFamily).c_str() );
		return NULL;
	}
protected:
	///\init the factories
	inline static void init()
	{	
		if( !Factories )
			Factories = new std::vector< std::pair< EFFECT_FAMILIES::TEffectFamily , IEffectFactory* > >;
	}
	/**
	 * Create a step from parameters
	 * \param params : a vector of vector of strings describing the step params
	 * \return a pointer on the built step (NULL if failure)
	 */
	virtual CSTimedEffect * buildEffect() = 0;
	
	///the phrase factories. We use a pointer here because we cant control the order inwhich ctor of static members are called
	static std::vector< std::pair< EFFECT_FAMILIES::TEffectFamily , IEffectFactory* > >* Factories;
};

/**
 * Effect template factory
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
template <class T> class CEffectTFactory : public IEffectFactory
{
public:
	explicit CEffectTFactory(EFFECT_FAMILIES::TEffectFamily family)
	{
		IEffectFactory::init();
		
#ifdef NL_DEBUG
		// check this type isn't used yet
		for (uint i = 0; i < Factories->size(); i++ )
		{
			if ( (*Factories)[i].first == family )
			{
				nlstop;
			}
		}
#endif
		// add factory
		Factories->push_back(std::make_pair( family ,this));
	};

	/// buildEffect method
	CSTimedEffect * buildEffect()
	{
		T *instance = new T;
		if (!instance)
		{
			nlwarning("<CEffectTFactory> failed to allocate element of template type");
			return 0;
		}
		return instance;
	}
};


#endif // RY_EFFECT_FACTORY_H

/* End of effect_factory.h */


















