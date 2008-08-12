/** \file creatures.cpp
 * <File description>
 *
 * $Id: creatures.cpp,v 1.10 2004/03/01 19:18:37 lecroart Exp $
 */




// Misc
#include "nel/misc/path.h"
#include "nel/misc/file.h"
#include "nel/misc/smart_ptr.h"
#include "nel/misc/command.h"
// Georges
//#include "nel/georges/u_form.h"
//#include "nel/georges/u_form_elm.h"
//#include "nel/georges/u_form_loader.h"
#include "nel/georges/load_form.h"
// Local
#include "creatures.h"


///////////
// USING //
///////////
using namespace NLMISC;
using namespace std;
using namespace NLGEORGES;

namespace AGS_TEST
{

//-------------------------------------------------------------------------
// the singleton data

std::map<CSheetId,CCreatures::CCreatureRecord> CCreatures::_creatures;
bool CCreatures::_initialised=false;


//-------------------------------------------------------------------------
// init

void CCreatures::init()
{
	if (_initialised)
		return;

	std::vector<std::string> filters;
	filters.push_back("creature");
	filters.push_back("player");

	loadForm(filters, "ags.packed_sheets", _creatures);

	_initialised=true;
}


//-------------------------------------------------------------------------
// display

void CCreatures::display()
{
	nlassert(_initialised);

	std::map<CSheetId,CCreatures::CCreatureRecord>::iterator it;
	for(it=_creatures.begin();it!=_creatures.end();++it)
	{
		nlinfo("CREATURE: %s Walk: %f Run: %f",(*it).first.toString().c_str(),
			(*it).second._walkSpeed,(*it).second._runSpeed);
	}
}


//-------------------------------------------------------------------------
// lookup

const CCreatures::CCreatureRecord *CCreatures::lookup( CSheetId id )
{
	nlassert(_initialised);

	// setup an iterator and lookup the sheet id in the map
	std::map<CSheetId,CCreatures::CCreatureRecord>::iterator it;
	it=_creatures.find(id);

	// if we found a valid entry return a pointer to the creature record otherwise 0
	if (it!=_creatures.end())
		return &((*it).second);
	else
		return 0;
}



} // end of namespace AGS_TEST
