/** \file effect_manager.cpp
 * <File description>
 *
 * $Id: effect_manager.cpp,v 1.12 2007/03/09 09:56:52 boucher Exp $
 */



#include "stdpch.h"
#include "effect_manager.h"
#include "effect_message.h"

using namespace std;
using namespace NLMISC;
using namespace NLNET;

NL_INSTANCE_COUNTER_IMPL(TEffectVector);

// init static members
TEntitiesEffectMap		CEffectManager::_Effects;
vector< CBasicEffect >	CEffectManager::_NewEffects;
vector< CBasicEffect >	CEffectManager::_RemovedEffects;
set< NLNET::TServiceId >	CEffectManager::_RegisteredServices;


//--------------------------------------------------------------
//					CEffectManager constructor
//--------------------------------------------------------------
CEffectManager::CEffectManager()
{
} // constructor //


//--------------------------------------------------------------
//				CEffectManager destructor
//--------------------------------------------------------------
CEffectManager::~CEffectManager()
{
	release();
} // destructor //


//--------------------------------------------------------------
//					CEffectManager::release
//--------------------------------------------------------------
void CEffectManager::release()
{
	TEntitiesEffectMap::iterator it = _Effects.begin();
	const TEntitiesEffectMap::iterator itEnd = _Effects.end();

	for ( ; it != itEnd ; ++it)
	{
		if ( (*it).second != NULL)
		{
			delete (*it).second;
		}
	}

	_Effects.clear();
	_RegisteredServices.clear();
	_RemovedEffects.clear();
	_NewEffects.clear();
} // release //


//--------------------------------------------------------------
//					CEffectManager::update
//--------------------------------------------------------------
void CEffectManager::update()
{
	H_AUTO(EffectManagerUpdate);

	if (  ! _RegisteredServices.empty() )
	{
		CAddEffectsMessage		addMsg;
		CRemoveEffectsMessage	removeMsg;

		std::vector< CBasicEffect >::const_iterator itNew = _NewEffects.begin();
		const std::vector< CBasicEffect >::const_iterator itNewEnd = _NewEffects.end();
		for ( ; itNew != itNewEnd ; ++itNew )
		{
			addMsg.addEffect( *itNew );
		}

		std::vector< CBasicEffect >::const_iterator itRemove = _RemovedEffects.begin();
		const std::vector< CBasicEffect >::const_iterator itRemoveEnd = _RemovedEffects.end();
		for ( ; itRemove != itRemoveEnd ; ++itRemove )
		{
			removeMsg.addEffect( *itRemove );
		}		

		set< NLNET::TServiceId >::const_iterator it;
		const set< NLNET::TServiceId >::const_iterator itEnd = _RegisteredServices.end();
		for (it = _RegisteredServices.begin() ; it != itEnd ; ++it)
		{
			if (!_NewEffects.empty())
				addMsg.send( (*it) );

			if (!_RemovedEffects.empty())
				removeMsg.send( (*it) );
		}
	}

	_NewEffects.clear();
	_RemovedEffects.clear();
} // update //>
