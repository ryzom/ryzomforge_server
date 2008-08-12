/** \file teleport_effect.cpp
 * <File description>
 *
 * $Id: teleport_effect.cpp,v 1.4 2005/02/22 10:22:29 besson Exp $
 */


#include "stdpch.h"
#include "teleport_effect.h"
#include "player_manager/character.h"
#include "player_manager/player_manager.h"
#include "player_manager/player.h"
#include "phrase_manager/s_effect.h"

CTeleportEffect::CTeleportEffect( const TDataSetRow & creatorRowId, 
				const TDataSetRow & targetRowId, 
				EFFECT_FAMILIES::TEffectFamily family, 
				sint32 effectValue, 
				NLMISC::TGameCycle endDate,
				const CStaticItem & form
				) :	CSTimedEffect(creatorRowId, targetRowId, family, true, effectValue,0, endDate),
					_Form( form )
				
{
}


void CTeleportEffect::removed()
{
	CCharacter * user = PlayerManager.getChar( _CreatorRowId );
	if ( user )
	{
		user->useTeleport(_Form);
	}
}
