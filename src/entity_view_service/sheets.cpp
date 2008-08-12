/** \file sheets.cpp
 * implementation of CCombatSheet
 *
 * $Id: sheets.cpp,v 1.2 2004/03/01 19:21:35 lecroart Exp $
 */




// Misc
#include "nel/misc/path.h"
#include "nel/misc/file.h"
#include "nel/misc/smart_ptr.h"
#include "nel/misc/command.h"
#include "nel/misc/path.h"

#include "nel/net/service.h"
// Georges
#include "nel/georges/u_form.h"
#include "nel/georges/u_form_elm.h"
#include "nel/georges/u_form_loader.h"
#include "nel/georges/load_form.h"
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

std::map<CSheetId,CSheets::CSheet> CSheets::_Sheets;
bool CSheets::_Initialised=false;

//-------------------------------------------------------------------------
// init

void CSheets::init()
{
	if (_Initialised)
		return;

	CSheetId::init();

	std::vector<std::string> filters;
	filters.push_back("creature");
	filters.push_back("player");

	loadForm(filters, IService::getInstance()->WriteFilesDirectory+"evs.packed_sheets", _Sheets);

	_Initialised=true;
}


//-------------------------------------------------------------------------
// display

void CSheets::display()
{
	nlassert(_Initialised);

	std::map<CSheetId,CSheets::CSheet>::iterator it;
	for(it=_Sheets.begin();it!=_Sheets.end();++it)
	{
		nlinfo("SHEET:%s Walk:%f Run:%f Radius:%f Height:%f Bounding:%f",(*it).first.toString().c_str(),
			(*it).second.WalkSpeed, (*it).second.RunSpeed, (*it).second.Radius, (*it).second.Height, (*it).second.BoundingRadius);
	}
}


//-------------------------------------------------------------------------
// lookup

const CSheets::CSheet *CSheets::lookup( CSheetId id )
{
	nlassert(_Initialised);

	// setup an iterator and lookup the sheet id in the map
	std::map<CSheetId,CSheets::CSheet>::iterator it=_Sheets.find(id);

	// if we found a valid entry return a pointer to the creature record otherwise 0
	if (it!=_Sheets.end())
		return &((*it).second);
	else
		return NULL;
}
