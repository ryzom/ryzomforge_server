/** \file service_main.cpp
 *
 * $Id: service_main.cpp,v 1.7 2004/10/07 15:49:34 boucher Exp $
 */



#include "nel/misc/types_nl.h"
#include "nel/net/service.h"
#include "nel/misc/path.h"
#include "nel/ligo/primitive.h"
#include "nel/ligo/ligo_config.h"
#include "game_share/ryzom_version.h"
#include "ai_share/ai_share.h"

#include "ai_files.h"
#include "ai_manager.h"
#include "ai_service.h"
#include "aids_actions.h"
#include "messages.h"		// singleton manager for transport class messages

using namespace NLMISC;
using namespace NLNET;
using namespace std;

// The ligo config
NLLIGO::CLigoConfig LigoConfig;

static TUnifiedCallbackItem CallbackArray[] = 
{
	{	"QWERTY",			0,	},
};

extern string				OutputPath;
extern vector<string>		PacsPrimPath;
extern vector<string>		LookupPath;
extern vector<string>		LookupNoRecursePath;


/*-----------------------------------------------------------------*\
						SERVICE CLASS
\*-----------------------------------------------------------------*/

class CAIDataService : public NLNET::IService
{
public:
	void init();
	bool update();
	void release();
};

// callback for the tick service 'tick' message
static void cbTick();


/*-----------------------------------------------------------------*\
						SERVICE INIT & RELEASE
\*-----------------------------------------------------------------*/

///init

void CAIDataService::init (void)
{
	setVersion (RYZOM_VERSION);

	// this is the init for the ligo pri;itive parser lib
	NLLIGO::Register ();

	// setup the update systems
	setUpdateTimeout(200);

	// Init ligo
	if (!LigoConfig.readPrimitiveClass ("world_editor_classes.xml", false))
	{
		// Should be in l:\leveldesign\world_edit_files
		nlerror ("Can't load ligo primitive config file world_editor_classes.xml");
	}

	// init sub systems
	AI_SHARE::init(&LigoConfig);
	CMessages::init();
	CAIDSActions::init();


	//
	CConfigFile			&cf = ConfigFile;
	CConfigFile::CVar	*var;

	var = cf.getVarPtr("Paths");
	if (var != NULL)
	{
		uint	i;
		for (i=0; (sint)i<var->size(); ++i)
			LookupPath.push_back(var->asString(i));
	}

	var = cf.getVarPtr("NoRecursePaths");
	if (var != NULL)
	{
		uint	i;
		for (i=0; (sint)i<var->size(); ++i)
			LookupNoRecursePath.push_back(var->asString(i));
	}

	var = cf.getVarPtr("PacsPrimPaths");
	if (var != NULL)
	{
		uint	i;
		for (i=0; (sint)i<var->size(); ++i)
			PacsPrimPath.push_back(var->asString(i));
	}

	var = cf.getVarPtr("OutputPath");
	if (var != NULL)
	{
		OutputPath = CPath::standardizePath(var->asString());
	}
}


///release

void CAIDataService::release (void)	
{
	// release sub systems
	CMessages::release();
}


/*-----------------------------------------------------------------*\
						SERVICE UPDATES
\*-----------------------------------------------------------------*/

///update called every coplete cycle of service loop

bool CAIDataService::update (void)
{
	CAIService::update();
	return true;
}

/*-----------------------------------------------------------------*\
						NLNET_SERVICE_MAIN
\*-----------------------------------------------------------------*/
NLNET_SERVICE_MAIN (CAIDataService, "AIDS", "ai_data_service", 0, CallbackArray, "", "")

