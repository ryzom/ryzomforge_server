/** \file sheets.cpp
 * implementation of CCombatSheet
 *
 * $Id: sheets.cpp,v 1.10 2006/09/21 10:22:12 coutelas Exp $
 */




// Misc
#include "nel/misc/path.h"
#include "nel/misc/file.h"
#include "nel/misc/smart_ptr.h"
#include "nel/misc/command.h"
// Georges
#include "nel/georges/u_form.h"
#include "nel/georges/u_form_elm.h"
#include "nel/georges/u_form_loader.h"
#include "nel/georges/load_form.h"

#include "nel/net/service.h"
// Local
#include "sheets.h"


///////////
// USING //
///////////
using namespace NLMISC;
using namespace NLNET;
using namespace std;
using namespace NLGEORGES;

//-------------------------------------------------------------------------
// the singleton data

std::map<CSheetId,CSheets::CSheet> CSheets::_sheets;
bool CSheets::_initialised=false;


//-------------------------------------------------------------------------
// init

void CSheets::init()
{
	if (_initialised)
		return;

	CSheetId::init(0);

	std::vector<std::string> filters;
	filters.push_back("creature");
	filters.push_back("player");

	loadForm(filters, IService::getInstance()->WriteFilesDirectory.toString()+"gpms.packed_sheets", _sheets);

	_initialised=true;
}


//-------------------------------------------------------------------------
// display

void CSheets::display()
{
	nlassert(_initialised);

	std::map<CSheetId,CSheets::CSheet>::iterator it;
	for(it=_sheets.begin();it!=_sheets.end();++it)
	{
		nlinfo("SHEET:%s Walk:%f Run:%f Radius:%f Height:%f Bounding:%f Scale:%f",(*it).first.toString().c_str(),
			(*it).second.WalkSpeed, (*it).second.RunSpeed, (*it).second.Radius, (*it).second.Height, (*it).second.BoundingRadius, (*it).second.Scale);
	}
}


//-------------------------------------------------------------------------
// lookup

const CSheets::CSheet *CSheets::lookup( CSheetId id )
{
	nlassert(_initialised);

	// setup an iterator and lookup the sheet id in the map
	std::map<CSheetId,CSheets::CSheet>::iterator it;
	it=_sheets.find(id);

	// if we found a valid entry return a pointer to the creature record otherwise 0
	if (it!=_sheets.end())
		return &((*it).second);
	else
		return 0;
}


