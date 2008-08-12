/** \file ec_event_chat.cpp
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
// class CEventChat
//-----------------------------------------------------------------------------

class CEventChat: public GUS::IModule
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
	CEventChat();

private:
};


//-----------------------------------------------------------------------------
// methods CEventChat
//-----------------------------------------------------------------------------

CEventChat::CEventChat()
{
}

bool CEventChat::initialiseModule(const NLMISC::CSString& rawArgs)
{
	return true;
}

NLMISC::CSString CEventChat::getState() const
{
	return getName()+" "+getParameters();
}

NLMISC::CSString CEventChat::getName() const
{
	return "EC";
}

NLMISC::CSString CEventChat::getParameters() const
{
	return "";
}

void CEventChat::displayModule() const
{
}


//-----------------------------------------------------------------------------
// CEventChat registration
//-----------------------------------------------------------------------------

REGISTER_GUS_MODULE(CEventChat,"EC")

