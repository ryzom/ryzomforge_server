/** \file ais_spawn_ctrl.cpp
  

 	This file contains the list of command line commands for the ai_service service

 
 * $Id: ais_spawn_ctrl.cpp,v 1.18 2004/11/23 21:58:00 boucher Exp $
 */



//-------------------------------------------------------------------------
// Includes & namespaces

#include "stdpch.h"
#include "ai_share/ai_spawn_commands.h"
#include "ai_grp.h"

using namespace NLMISC;
using namespace std;


//-------------------------------------------------------------------------
// The CAISpawnCtrl sub-class

//class CAISSpawnCtrl: public CAISpawnCtrl
//{
//protected:
//	virtual bool _spawn		(int	aiInstance, const std::string &name);
//	virtual bool _spawnMap	(int	aiInstance, const std::string &name);
//	virtual bool _spawnMgr	(int	aiInstance, const std::string &name);
//	virtual bool _spawnGrp	(int	aiInstance, const std::string &name);
//	virtual bool _spawnAll	(int	aiInstance);
//
//	virtual bool _despawn		(int	aiInstance, const std::string &name);
//	virtual bool _despawnMap	(int	aiInstance, const std::string &name);
//	virtual bool _despawnMgr	(int	aiInstance, const std::string &name);
//	virtual bool _despawnGrp	(int	aiInstance, const std::string &name);
//	virtual bool _despawnAll	(int	aiInstance);
//
//} AIServiceSpawnCtrl;


//-------------------------------------------------------------------------
// The CAISpawnCtrl singleton data
//CAISpawnCtrl *CAISpawnCtrl::_instance=&AIServiceSpawnCtrl;


//-------------------------------------------------------------------------
// SPAWNING

//bool CAISSpawnCtrl::_spawn(int	aiInstance, const std::string &name)
//{
//	if (_spawnMap(aiInstance, name)) return true;
//	if (_spawnMgr(aiInstance, name)) return true;
//	if (_spawnGrp(aiInstance, name)) return true;
//	return false;
//}
//
//bool CAISSpawnCtrl::_spawnGrp(int	aiInstance, const std::string &name)
//{
//	bool	returnVal=false;
//
//	if	(aiInstance==-1)	// all aiInstance are concerned.
//	{
//		CCont<CAIInstance>::iterator	instanceIt=CAIS::instance().AIList().begin(), instanceItEnd=CAIS::instance().AIList().end();
//		while (instanceIt!=instanceItEnd)
//		{
//			CGroup*	grpPtr=(*instanceIt)->tryToGetGroup(name.c_str());
//			if (grpPtr)
//			{
//				grpPtr->spawn	();	// check error only if not a npc group.
//				returnVal=true;
//			}
//			++instanceIt;
//		}
//		
//	}
//	else
//	{
//		if (CAIS::instance().AIList()[aiInstance])
//		{
//			CGroup*	grpPtr=CAIS::instance().AIList()[aiInstance]->tryToGetGroup(name.c_str());
//			if (grpPtr)
//			{
//				grpPtr->spawn	();	// check error only if not a npc group.
//				returnVal=true;
//			}
//			
//		}
//		
//	}
//
//	if (!returnVal)
//	{
//		nlinfo("Failed to identify groupe from id: %s",name.c_str());
//	}
//	return	returnVal;
//}
//
//bool CAISSpawnCtrl::_spawnMgr(int	aiInstance, const std::string &name)
//{
//	bool	returnVal=false;
//	
//	if	(aiInstance==-1)	// all aiInstance are concerned.
//	{
//		CCont<CAIInstance>::iterator	instanceIt=CAIS::instance().AIList().begin(), instanceItEnd=CAIS::instance().AIList().end();
//		while (instanceIt!=instanceItEnd)
//		{
//			CManager*	mgrPtr=(*instanceIt)->tryToGetManager(name.c_str());
//			if (mgrPtr)
//			{
//				mgrPtr->spawn	();	// check error only if not a npc group.
//				returnVal=true;
//			}
//			++instanceIt;
//		}
//		
//	}
//	else
//	{
//		if (CAIS::instance().AIList()[aiInstance])
//		{
//			CManager*	mgrPtr=CAIS::instance().AIList()[aiInstance]->tryToGetManager(name.c_str());
//			if (mgrPtr)
//			{
//				mgrPtr->spawn	();	// check error only if not a npc group.
//				returnVal=true;
//			}
//			
//		}
//		
//	}
//	
//	if (!returnVal)
//	{
//		nlinfo("Failed to identify mgr from id: %s",name.c_str());
//	}
//	return	returnVal;
//}
//
//bool CAISSpawnCtrl::_spawnMap(int	aiInstance, const std::string &name)
//{
//#ifdef NL_DEBUG
//	nlassert(false);
//#endif
////	// for each manager if map's name found in the command arguments then spawn()
////	for (CAIEntityId it=CAIEntityId::firstMgr();!it.isInvalid();it=it.nextMgr())
////		if (it.mgrPtr()->getMap()->Name==name)
////			it.mgrPtr()->spawn();
//	return	true;
//}
//
//bool	CAISSpawnCtrl::_spawnAll	(int	aiInstance)
//{
//	if	(aiInstance==-1)	// all aiInstance are concerned.
//	{
//		CCont<CAIInstance>::iterator	instanceIt=CAIS::instance().AIList().begin(), instanceItEnd=CAIS::instance().AIList().end();
//		while (instanceIt!=instanceItEnd)
//		{
//			(*instanceIt)->spawnAll();
//			++instanceIt;
//		}
//		
//	}
//	else
//	{
//		if (CAIS::instance().AIList()[aiInstance])
//		{
//			CAIS::instance().AIList()[aiInstance]->spawnAll();
//		}
//		
//	}
//	return true;
//}
//
//
////-------------------------------------------------------------------------
//// DESPAWNING
//
//bool CAISSpawnCtrl::_despawn(int	aiInstance, const std::string &name)
//{
//	if (_despawnMap(aiInstance, name)) return true;
//	if (_despawnMgr(aiInstance, name)) return true;
//	if (_despawnGrp(aiInstance, name)) return true;
//	return false;
//}
//
//bool CAISSpawnCtrl::_despawnGrp(int	aiInstance, const std::string &name)
//{
//
//	bool	returnVal=false;
//	
//	if	(aiInstance==-1)	// all aiInstance are concerned.
//	{
//		CCont<CAIInstance>::iterator	instanceIt=CAIS::instance().AIList().begin(), instanceItEnd=CAIS::instance().AIList().end();
//		while (instanceIt!=instanceItEnd)
//		{
//			CGroup*	grpPtr=(*instanceIt)->tryToGetGroup(name.c_str());
//			if (grpPtr)
//			{
//				grpPtr->despawnGrp	();	// check error only if not a npc group.
//				returnVal=true;
//			}			
//			++instanceIt;
//		}
//		
//	}
//	else
//	{
//		if (CAIS::instance().AIList()[aiInstance])
//		{
//			CGroup*	grpPtr=CAIS::instance().AIList()[aiInstance]->tryToGetGroup(name.c_str());
//			if (grpPtr)
//			{
//				grpPtr->despawnGrp	();	// check error only if not a npc group.
//				returnVal=true;
//			}
//			
//		}
//		
//	}
//	
//	if (!returnVal)
//	{
//		nlinfo("Failed to identify groupe from id: %s",name.c_str());
//	}
//	return	returnVal;
//}
//
//bool CAISSpawnCtrl::_despawnMgr(int	aiInstance, const std::string &name)
//{
//	bool	returnVal=false;
//	
//	if	(aiInstance==-1)	// all aiInstance are concerned.
//	{
//		CCont<CAIInstance>::iterator	instanceIt=CAIS::instance().AIList().begin(), instanceItEnd=CAIS::instance().AIList().end();
//		while (instanceIt!=instanceItEnd)
//		{
//			CManager*	mgrPtr=(*instanceIt)->tryToGetManager(name.c_str());
//			if (mgrPtr)
//			{
//				mgrPtr->despawnMgr();	// check error only if not a npc group.
//				returnVal=true;
//			}			
//			++instanceIt;
//		}
//		
//	}
//	else
//	{
//		if (CAIS::instance().AIList()[aiInstance])
//		{
//			CManager*	mgrPtr=CAIS::instance().AIList()[aiInstance]->tryToGetManager(name.c_str());
//			if (mgrPtr)
//			{
//				mgrPtr->despawnMgr();	// check error only if not a npc group.
//				returnVal=true;
//			}
//			
//		}
//		
//	}
//	
//	if (!returnVal)
//	{
//		nlinfo("Failed to identify mgr from id: %s",name.c_str());
//	}
//	return	returnVal;
//}
//
//bool CAISSpawnCtrl::_despawnMap(int	aiInstance, const std::string &name)
//{
//#ifdef	NL_DEBUG
//	nlwarning("Not Implemented");
//#endif
//	
////	// for each manager if map's name found in the command arguments then spawn()
////	for (CAIEntityId it=CAIEntityId::firstMgr();!it.isInvalid();it=it.nextMgr())
////		if (it.mgrPtr()->getMap()->Name==name)
////			it.mgrPtr()->despawn();
//
//	return true;
//}
//
//bool CAISSpawnCtrl::_despawnAll(int	aiInstance)
//{
//	if	(aiInstance==-1)	// all aiInstance are concerned.
//	{
//		CCont<CAIInstance>::iterator	instanceIt=CAIS::instance().AIList().begin(), instanceItEnd=CAIS::instance().AIList().end();
//		while (instanceIt!=instanceItEnd)
//		{
////			NLMEMORY::CheckHeap(true);
//			(*instanceIt)->despawnAll();
//			++instanceIt;
//		}
//		
//	}
//	else
//	{
//		if (CAIS::instance().AIList()[aiInstance])
//		{
//			CAIS::instance().AIList()[aiInstance]->despawnAll();
//		}
//		
//	}
//	return true;
//}
