/** \file world_container.cpp
 * <File description>
 *
 * $Id: world_container.cpp,v 1.33 2007/06/18 12:25:11 distrib Exp $
 */



#include "stdpch.h"
#include "world_container.h"

#include "nel/misc/path.h"
#include "nel/misc/file.h"
//	#include "nel/misc/hierarchical_timer.h"
#include "game_share/msg_ai_service.h"


using namespace std;
using namespace NLMISC;
using namespace RYAI_MAP_CRUNCH;

RYAI_MAP_CRUNCH::CWorldMap	CWorldContainer::_WorldMaps/*[3]*/;

std::vector<std::string>	CWorldContainer::_ContinentNames;

extern	bool	EGSHasMirrorReady;

/*
 * Constructor
 */
CWorldContainer::CWorldContainer()
{
	clear();
}


/*
 * Clear
 */
void	CWorldContainer::clear()
{
	_WorldMaps.clear();
}


/*
 * Load Continent
 */
void	CWorldContainer::loadContinent(const string &name)
{
	nlinfo("Loading continent '%s' in WorldContainer", name.c_str());

	if (find(_ContinentNames.begin(), _ContinentNames.end(), name) != _ContinentNames.end())
	{
		nldebug("CWorldContainer::loadContinent : continent '%s' is already loaded, ignoring repeat load request", name.c_str());
		return;
	}

	try
	{
		CIFile		f0(CPath::lookup(name+"_0.cwmap2"));

		_WorldMaps.serial(f0);

		_ContinentNames.push_back(name);

		if (EGSHasMirrorReady)
		{
			// if EGS is up, send the new list of available continent
			CReportAICollisionAvailableMsg msg;
			msg.ContinentsCollision = _ContinentNames;
			msg.send("EGS");
		}
	}
	catch (Exception &e)
	{
		nlwarning("Unable to load continent '%s', aborted (%s)", name.c_str(), e.what());
	}
}
