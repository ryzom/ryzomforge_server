/** \file merge_shard_merger.cpp
 *
 * $id$
 *
 */

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

// game share
#include "game_share/utils.h"

// local
#include "gus_module_manager.h"


//-------------------------------------------------------------------------------------------------
// namespaces
//-------------------------------------------------------------------------------------------------

using namespace std;
using namespace NLMISC;
using namespace NLNET;
using namespace GUS;


//-----------------------------------------------------------------------------
// class CShardMerger
//-----------------------------------------------------------------------------

class CShardMerger: public GUS::IModule
{
public:
	// IModule specialisation implementation
	bool initialiseModule(const NLMISC::CSString& rawArgs);

	NLMISC::CSString getState() const;
	NLMISC::CSString getName() const;
	NLMISC::CSString getParameters() const;
	void displayModule() const;

public:
	// remaining public interface
	CShardMerger();

private:
};


//-----------------------------------------------------------------------------
// methods CShardMerger
//-----------------------------------------------------------------------------

CShardMerger::CShardMerger()
{
}

bool CShardMerger::initialiseModule(const NLMISC::CSString& rawArgs)
{
	return true;
}

NLMISC::CSString CShardMerger::getState() const
{
	return getName()+" "+getParameters();
}

NLMISC::CSString CShardMerger::getName() const
{
	return "MERGE";
}

NLMISC::CSString CShardMerger::getParameters() const
{
	return "";
}

void CShardMerger::displayModule() const
{
}


//-----------------------------------------------------------------------------
// CShardMerger registration
//-----------------------------------------------------------------------------

REGISTER_GUS_MODULE(CShardMerger,"MERGE","","Shard merge manager")

