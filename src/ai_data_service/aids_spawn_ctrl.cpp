/** \file aids_spawn_ctrl.cpp
  

 	This file contains the list of command line commands for the ai_service service

 
 * $Id: aids_spawn_ctrl.cpp,v 1.4 2006/01/10 17:38:49 boucher Exp $
 */



//-------------------------------------------------------------------------
// Includes & namespaces

#include "ai_share/ai_spawn_commands.h"

using namespace NLMISC;
using namespace std;

// remove stupid VC6 warnings
void foo_aids_spawn_ctrl_cpp() {}


//-------------------------------------------------------------------------
// The CAISpawnCtrl sub-class
/*
class CAIDSSpawnCtrl: public CAISpawnCtrl
{
protected:
	virtual bool _spawn(const std::string &name);
	virtual bool _spawnMap(const std::string &name);
	virtual bool _spawnMgr(const std::string &name);
	virtual bool _spawnGrp(const std::string &name);
	virtual bool _spawnAll();

	virtual bool _despawn(const std::string &name);
	virtual bool _despawnMap(const std::string &name);
	virtual bool _despawnMgr(const std::string &name);
	virtual bool _despawnGrp(const std::string &name);
	virtual bool _despawnAll();

} AIServiceSpawnCtrl;
*/

//-------------------------------------------------------------------------
// The CAISpawnCtrl singleton data
//CAISpawnCtrl *CAISpawnCtrl::_instance=&AIServiceSpawnCtrl;


//-------------------------------------------------------------------------
// SPAWNING
/*
bool CAIDSSpawnCtrl::_spawn(const std::string &name)
{
	if (_spawnMap(name)) return true;
	if (_spawnMgr(name)) return true;
	if (_spawnGrp(name)) return true;
	return false;
}

bool CAIDSSpawnCtrl::_spawnGrp(const std::string &name)
{
	nlinfo("*** spawnGrp(%s) NOT IMPLEMENTED YET ***",name.c_str());

	return true;
}

bool CAIDSSpawnCtrl::_spawnMgr(const std::string &name)
{
	nlinfo("*** spawnMgr(%s) NOT IMPLEMENTED YET ***",name.c_str());

	return true;
}

bool CAIDSSpawnCtrl::_spawnMap(const std::string &name)
{
	nlinfo("*** spawnMap(%s) NOT IMPLEMENTED YET ***",name.c_str());

	return true;
}

bool CAIDSSpawnCtrl::_spawnAll()
{
	nlinfo("*** spawnAll() NOT IMPLEMENTED YET ***");

	return true;
}


//-------------------------------------------------------------------------
// DESPAWNING

bool CAIDSSpawnCtrl::_despawn(const std::string &name)
{
	if (_despawnMap(name)) return true;
	if (_despawnMgr(name)) return true;
	if (_despawnGrp(name)) return true;
	return false;
}

bool CAIDSSpawnCtrl::_despawnGrp(const std::string &name)
{
	nlinfo("*** despawnGrp(%s) NOT IMPLEMENTED YET ***",name.c_str());

	return true;
}

bool CAIDSSpawnCtrl::_despawnMgr(const std::string &name)
{
	nlinfo("*** despawnMgr(%s) NOT IMPLEMENTED YET ***",name.c_str());

	return true;
}

bool CAIDSSpawnCtrl::_despawnMap(const std::string &name)
{
	// for each manager if map's name found in the command arguments then spawn()
	nlinfo("*** despawnMap(%s) NOT IMPLEMENTED YET ***",name.c_str());

	return true;
}

bool CAIDSSpawnCtrl::_despawnAll()
{
	nlinfo("*** despawnAll() NOT IMPLEMENTED YET ***");

	return true;
}
*/
