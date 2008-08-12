/** \file simulation_service.h
 * <File description>
 *
 * $Id: simulation_service.h, AJM, 2005/10/10
 */

#ifndef NL_SIMULATION_SERVICE_H
#define NL_SIMULATION_SERVICE_H

#include "nel/misc/types_nl.h"
#include "nel/misc/time_nl.h"
#include "nel/net/service.h"
#include "simulated_editor.h"	// for SimEditorState

namespace RSMGR
{
	class CRingSessionManager;
}

class CSimulatedClient;
class CSimulatedEditor;

typedef std::vector<CSimulatedClient*> SimClientsVector;
typedef std::vector<CSimulatedEditor*> SimEditorsVector;

// AJM in work
enum SimServiceState
{
	sssUninitialized = 0,
	sssInitialized,
	sssAwaitingDSS,
	sssStartingSimulation,
	sssRunning,
	sssQuitting
};

class CSimulationService : public NLNET::IService
{
public:
	CSimulationService();
	~CSimulationService();
	void init();
	bool update();
	void release();

	void test();
	
	void start();
	void login();
	void connect();
	void upload();
	void run();
	void next();
	void end();

	void createScenario( const std::string scenarioName );
	void runScenario();
	void endScenario();
	void joinSession( uint sessionId );

	void displayEditorStates();
	void displaySchedule();

	void onTick();
	void onInvokeResult( uint32 resultCode, const std::string &resultString );

	void setDSSup( bool bYesNo )	{ _bDSSup = bYesNo; }
	void setAISup( bool bYesNo )	{ _bAISup = bYesNo; }

	static CSimulationService &getSS()	{ return *s_pSimService; }

	void onReceiveSessionCreated( uint sessionId );
	void onReceiveStopTest( uint editorId );

protected:
	void initNetworkImpulse();

	void connectSimClients();
	void connectSimEditors();
	void createEditorSessions();

	// scheduler
	void scheduleEvent( uint editorId, SimEditorState toState );
	void processSchedule();

	// simulation state machine
	bool simulate();

	// editor state machine
	SimEditorState simulateEditor( uint editorId );
	void transition( CSimulatedEditor *ed, SimEditorState toState );

	bool startSession0( uint editorId );
	bool joinSession0( uint editorId );
	bool loadScenario0( uint editorId );
	bool uploadScenario0( uint editorId );
	bool endScenario0( uint editorId );

private:
	bool _bDSSup;
	bool _bAISup;

	// state machine for this service
	SimServiceState _sss;
	bool _bStarted;
	bool _bConnected;
	bool _bSimComplete;

	NLMISC::TLocalTime _StartTime;

	// state machine for sim editors
	SimEditorState _minSes;	// current minimum state

	uint32 _NumClients;
	uint32 _NumEditors;

	SimClientsVector _Clients;
	SimEditorsVector _Editors;

	R2::CObject *_ScenarioStub;
	R2::CObject *_ScenarioRtData;

	RSMGR::CRingSessionManager *_RSM;

	static CSimulationService *s_pSimService;

	std::set<uint32> receivedSessionCreated;
	std::set<uint32> receivedStopTest;

	// scheduler
	struct SimScheduleEvent
	{
		uint32 editorId;
		SimEditorState toState;
		SimScheduleEvent( uint32 edId, SimEditorState toSt )
		{
			editorId = edId;
			toState = toSt;
		}
	};

	typedef std::multimap<NLMISC::TLocalTime, SimScheduleEvent> SimScheduleType;
	typedef std::pair<NLMISC::TLocalTime, SimScheduleEvent> SimScheduleEntryType;
	typedef std::vector<NLMISC::TLocalTime> TimeVector;

	SimScheduleType _Schedule;
	TimeVector _LastTransitionTimeToState;	// local clock, in msec
	TimeVector _MeanArrivalTimeAtState;		// in msec
};

#endif // NL_SIMULATION_SERVICE_H

/* End of simulation_service.h */
