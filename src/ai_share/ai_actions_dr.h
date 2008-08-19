#ifndef AI_ACTIONS_DR_H
#define AI_ACTIONS_DR_H

//-------------------------------------------------------------------------------------------------
// class CAIActionsDataRecord
//-------------------------------------------------------------------------------------------------

#include "game_share/persistent_data.h"

// ai share
#include "ai_share.h"
#include "ai_actions.h"

namespace AI_SHARE
{

class CAIActionsDataRecordPtr
{
public:

	CAIActionsDataRecordPtr(){ _PdrPtr = 0; }
	void init(CPersistentDataRecord* pdr) { _PdrPtr = pdr ; }
	//----------------------------------------------------------------------------
	// general management interface

	void clear();
	void readFile(const std::string &fileName);
	void writeFile(const std::string &fileName);
	void display();
	void serial(NLMISC::IStream &stream);



	//----------------------------------------------------------------------------
	// interface used to setup the data record

	void addOpenFile(const std::string &fileName);
	void addCloseFile(const std::string &fileName);
	void addExecute(uint64 action,const std::vector <CAIActions::CArg> &args);
	void addBegin(uint32 contextAlias);
	void addEnd(uint32 contextAlias);


	//----------------------------------------------------------------------------
	// interface used to retrieve the contents of the data record

	void applyToExecutor(CAIActions::IExecutor& executor);


private:
	// private data
	CPersistentDataRecord* _PdrPtr;
};

class CAIActionsDataRecord : public CAIActionsDataRecordPtr
{
public:
	CAIActionsDataRecord():CAIActionsDataRecordPtr() { init( &_Pdr); }
private:	
	CPersistentDataRecordRyzomStore _Pdr;
};



} //namespace AI_SHARE

#endif

