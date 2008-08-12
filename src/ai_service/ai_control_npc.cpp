/** \file ai_control_npc.cpp
 *
 * $Id: ai_control_npc.cpp,v 1.5 2006/12/06 17:22:05 boucher Exp $
 */

#include "stdpch.h"
#include "game_share/mode_and_behaviour.h"
#include "ai_control_npc.h"
#include "ai_bot_npc.h"
#include "ai_player.h"
#include "ai_profile_npc.h"
#include "ais_control.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////////
// CPlayerControlNpc                                                        //
//////////////////////////////////////////////////////////////////////////////

CPlayerControlNpc::CPlayerControlNpc(CBotPlayer* player, CSpawnBotNpc* bot)
{
	_Player = player;
	_Bot = bot;
	_LastPathUpdate = 0;
	_CPlayerEntityId = player->getEntityId();
	_CNpcEntityId = bot->getEntityId();
	IAisControl::getInstance()->reportNpcControl(_CPlayerEntityId, _CNpcEntityId);
}

CPlayerControlNpc::~CPlayerControlNpc()
{
	IAisControl::getInstance()->reportStopNpcControl(_CPlayerEntityId, _CNpcEntityId);
}

bool CPlayerControlNpc::isValid() const
{
	if (_Player == NULL)
		return false;

	if (_Bot == NULL)
		return false;

	return true;
}

void CPlayerControlNpc::updateControl(uint ticks)
{
	nlassert(isValid());

//	static double baseDist = 1.0;
//	const double wantedDist = baseDist + _Bot->radius() + _Player->radius();
	const AITYPES::TVerticalPos vertPos = AITYPES::vp_auto;
	
	RYAI_MAP_CRUNCH::CMapPosition mapPos(CAIVector(_Player->pos()));
	RYAI_MAP_CRUNCH::CWorldPosition wantedWPos( mapPos.x(), mapPos.y());		

	//const RYAI_MAP_CRUNCH::CWorldPosition wantedWPos = _Player->wpos();

	// :BUG: _Player->wpos().x() == 0 && _Player->wpos().x() == 0 where colision are wrong (like prime roots)
	if (wantedWPos.x() == 0 && wantedWPos.y()==0)
	{
		_Player = NULL;
		_Bot = NULL;
		return;
	}
 
//	CBotProfileMoveTo* moveToProfile = dynamic_cast<CBotProfileMoveTo*>(_ControlProfileManager.getAIProfile());
//
//	// do not path finding more than once per second
//	const uint32 currentTime = CTimeInterface::gameCycle();
//	const uint32 dt = currentTime - _LastPathUpdate;
//	if (	moveToProfile == NULL
//		||	dt >= 10)
//	{
//		moveToProfile = new CBotProfileMoveTo(vertPos, wantedWPos, _Bot);
//		_ControlProfileManager.setAIProfile(moveToProfile);
//		_LastPathUpdate = currentTime;
//	}
//
//	breakable
//	{
//		if (!moveToProfile->destinationReach())
//		{
//			const double dist = _Bot->pos().quickDistTo( wantedWPos.toAIVector() );
//			if (dist > wantedDist)
//			{
//				_ControlProfileManager.updateProfile(ticks);
//				break;
//			}
//		}

		_Bot->setPos(_Player->pos());
		_Bot->setTheta(_Player->theta());
		_Bot->setMode(_Player->getMode());
		CMirrorPropValueRO<MBEHAV::CBehaviour> playerBehaviour( TheDataset, _Player->dataSetRow(), DSPropertyBEHAVIOUR );
		CMirrorPropValue<MBEHAV::CBehaviour> npcBehaviour( TheDataset, _Bot->dataSetRow(), DSPropertyBEHAVIOUR );
		npcBehaviour = playerBehaviour.getValue();
//	}
}


CSpawnBotNpc* CPlayerControlNpc::getSpawnBot() const
{
	return _Bot;
}
