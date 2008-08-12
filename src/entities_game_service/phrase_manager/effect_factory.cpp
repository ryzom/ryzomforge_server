/** \file effect_factory.cpp
 * <File description>
 *
 * $Id: effect_factory.cpp,v 1.5 2005/02/22 10:22:30 besson Exp $
 */



#include "stdpch.h"
#include "phrase_manager/effect_factory.h"

NL_INSTANCE_COUNTER_IMPL(IEffectFactory);

std::vector< std::pair< EFFECT_FAMILIES::TEffectFamily , IEffectFactory* > >* IEffectFactory::Factories = NULL;
