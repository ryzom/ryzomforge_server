/** \file ai_mgr_fauna.cpp
 *
 * $Id: ai_mgr_fauna.cpp,v 1.55 2005/08/09 12:38:24 vuarand Exp $
 */

#include "stdpch.h"
#include "ai_mgr_fauna.h"
#include "ai_grp_fauna.h"
#include "timer.h"
#include "states.h"

using namespace NLMISC;
using namespace NLNET;
using namespace std;
using namespace RYAI_MAP_CRUNCH;
using namespace	AITYPES;

// Stuff used for management of log messages
static bool VerboseLog=false;
#define LOG if (!VerboseLog) {} else nlinfo

//////////////////////////////////////////////////////////////////////////////
// Local globals                                                            //
//////////////////////////////////////////////////////////////////////////////

static CAITimer VerboseMgrFaunaUpdateTimer;	// for activating verbose debug info for short periods
static uint32 PlayersPerRegion = 0;			// dummy variable for setting fake number of players per region


//////////////////////////////////////////////////////////////////////////////
// CMgrFauna                                                                //
//////////////////////////////////////////////////////////////////////////////

CMgrFauna::CMgrFauna(IManagerParent* parent, uint32 alias, std::string const& name, std::string const& filename)
: CManager(parent, alias, name, filename)
{
	registerEvents();
}

CMgrFauna::~CMgrFauna()
{
	_StateMachine.clearEventContainerContent();
	_Groups.clear();
}

void CMgrFauna::registerEvents()
{
	_StateMachine.registerEvents	();
	
	_StateMachine.addEvent(	"destination_reached",			EventDestinationReachedFirst	);
	_StateMachine.addEvent(	"destination_reached_first",	EventDestinationReachedFirst	);
	_StateMachine.addEvent(	"destination_reached_all",		EventDestinationReachedAll	);
	_StateMachine.addEvent(	"bot_killed",					EventBotKilled				);
	_StateMachine.addEvent(	"group_eliminated",				EventGrpEliminated			);
}

void CMgrFauna::init()
{
	VerboseMgrFaunaUpdateTimer.set(0);
}

void CMgrFauna::update()
{
	H_AUTO(MgrFaunaUpdate);
	
	++AISStat::MgrTotalUpdCtr;
	++AISStat::MgrFaunaUpdCtr;
	
	CManager::update(); // general update call ..
}

IAliasCont* CMgrFauna::getAliasCont(TAIType type)
{
	switch(type)
	{
	case AITypeGrp:
		return &_Groups;
	case AITypeEvent:
		return &getStateMachine()->eventReactions();
	case AITypeState:
		return &getStateMachine()->states();
	default:
		return NULL;
	}
}

CAliasTreeOwner* CMgrFauna::createChild(IAliasCont* cont, CAIAliasDescriptionNode* aliasTree)
{
	CAliasTreeOwner* child = NULL;
	
	switch (aliasTree->getType())
	{
	case AITypeGrp:
		child = new CGrpFauna(this, aliasTree, WaterAndNogo);
		break;
	case AITypeEvent:
		child = new CAIEventReaction(getStateMachine(), aliasTree);
		break;
	case AITypeState:
		child = new CAIStatePositional(getStateMachine(), aliasTree);
		break;
	}
	
	cont->addAliasChild(child);	
	return child;
}

std::string CMgrFauna::buildDebugString(uint idx)
{
	switch (idx)
	{
	case 0:
		return CManager::getIndexString() + " " + getFullName() + NLMISC::toString(": %-25s ",getName().c_str());
	default:
		break;
	}
	return std::string();
}

void CMgrFauna::display(CStringWriter& stringWriter)
{
	stringWriter.append(getFullName());
}

std::string CMgrFauna::getOneLineInfoString() const
{
	return std::string("Fauna manager '") + getName() + "'";
}

//----------------------------------------------------------------------------
// Admin commands and variables
NLMISC_DYNVARIABLE(uint32, VerboseMgrUpdate, "Dump update priority heaps and lists of groups updated for next <n> ticks")
{
	if (get)
		*pointer = VerboseMgrFaunaUpdateTimer.timeRemaining();
	else
		VerboseMgrFaunaUpdateTimer.set(*pointer);
}

NLMISC_DYNVARIABLE(uint32, SimPlayersPerRegion, "Dump update priority heaps and lists of groups updated for next <n> ticks")
{
	if (get)
		*pointer = PlayersPerRegion;
	else
		PlayersPerRegion = *pointer;
}

//----------------------------------------------------------------------------
// Control over verbose nature of logging
NLMISC_COMMAND(verboseFaunaMgrLog,"Turn on or off or check the state of verbose manager activity logging","")
{
	if(args.size()>1)
		return false;

	if(args.size()==1)
		StrToBool	(VerboseLog, args[0]);

	nlinfo("verboseLogging is %s",VerboseLog?"ON":"OFF");
	return true;
}
