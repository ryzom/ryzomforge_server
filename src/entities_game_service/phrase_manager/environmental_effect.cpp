/** \file environmental_effect.cpp
 * <File description>
 *
 * $Id: environmental_effect.cpp,v 1.4 2005/06/28 17:18:00 cado Exp $
 */



#include "stdpch.h"
#include "environmental_effect.h"
#include "nel/misc/variable.h"


using namespace NLMISC;
using namespace NLNET;
using namespace std;

NL_INSTANCE_COUNTER_IMPL(CEnvironmentalEffect);
NL_INSTANCE_COUNTER_IMPL(CEnvironmentalEffectManager);

NLMISC::TGameCycle								CEnvironmentalEffect::DefaultLifetime = 200; // 20 s
NL_ISO_TEMPLATE_SPEC CSimpleEntityManager<CEnvironmentalEffect>	*	CSimpleEntityManager<CEnvironmentalEffect>::_Instance = NULL;


/*
 * Despawn the effect in mirror
 */
void CEnvironmentalEffect::despawn()
{
	// Remove from mirror
	CEntityId entityId = TheDataset.getEntityId( _DataSetRow );
	Mirror.removeEntity( entityId );
}


/*
 * Tick update. Return false if the effect's life is ended.
 */
bool CEnvironmentalEffect::update()
{
	// Test effect end
	if (_TimeToLive == 0)
	{
		despawn();
		return false;
	}
	else
	{
		--_TimeToLive;
		return true;
	}
}


NLMISC_DYNVARIABLE( uint, NbEnvironmentalEffects, "Number of environmental effects" )
{
	if ( get )
		*pointer = CEnvironmentalEffectManager::getInstance()->nbEntities();
}
