/** \file visual_properties_interface.cpp
 *
 * $Id: visual_properties_interface.cpp,v 1.19 2006/09/14 17:06:18 cado Exp $
 */



#include "stdpch.h"
#include "visual_properties_interface.h"
#include "ai.h"
#include "mirrors.h"
#include "ai_instance.h"
#include "ai_mgr.h"
#include "game_share/synchronised_message.h"

//#include "nel/misc/ucstring.h"

/*
// Nel Include
#include "nel/net/unified_network.h"
#include "game_share/mode_and_behaviour.h"
#include "visual_properties_interface.h"
*/

using namespace NLMISC;
using namespace NLNET;
using namespace std;


//-----------------------------------------------
/// Macro to read a Bool from the CFG.
/// variableName : Variable Name to Read and Set.
//-----------------------------------------------
#define READ_BOOL(variableName)												\
	/* Read the Variable Value From Script */								\
	{CConfigFile::CVar *varPtr = IService::getInstance()->ConfigFile.getVarPtr(#variableName);	\
	/* Value found, set the Variable */										\
	if(varPtr)																\
		variableName = varPtr->asInt() ? true : false;						\
	nlinfo("IOS Entity naming constrol: "#variableName" %d",variableName?"1":"0");}

bool CVisualPropertiesInterface::UseIdForName=false;
bool CVisualPropertiesInterface::ForceNames=false;

// classic init(), update() and release()
void CVisualPropertiesInterface::init()
{
	READ_BOOL(UseIdForName);
	READ_BOOL(ForceNames);
}

void	CVisualPropertiesInterface::update()
{
}

void	CVisualPropertiesInterface::release()
{
}

//	set different visual properties for a bot.
void	CVisualPropertiesInterface::setName(const TDataSetRow&	dataSetRow,std::string name)
{
	if (!IOSHasMirrorReady)
		return;
	
	NLNET::CMessage	msgout("CHARACTER_NAME");
	CEntityId		eid=CMirrors::DataSet->getEntityId(dataSetRow);
	msgout.serial	(const_cast<TDataSetRow&>(dataSetRow));
	ucstring uname;
	uname.fromUtf8(name);	
	msgout.serial	(uname);	// Daniel: TODO update all name dependencies to ucstring in your service.	
	sendMessageViaMirror("IOS",msgout);
}
