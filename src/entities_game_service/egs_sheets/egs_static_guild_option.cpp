/** \file egs_static_guild_option.cpp
 * <File description>
 *
 * $Id: egs_static_guild_option.cpp,v 1.2 2004/09/03 17:42:28 guignot Exp $
 */


#include "stdpch.h"
#include "egs_static_guild_option.h"

#include "nel/misc/string_conversion.h"
#include "nel/georges/u_form_elm.h"
#include "nel/georges/load_form.h"

using namespace NLMISC;
using namespace NLGEORGES;
using namespace std;

namespace GUILD_OPTIONS
{
	NL_BEGIN_STRING_CONVERSION_TABLE (TType)
	NL_STRING_CONVERSION_TABLE_ENTRY(MainBuilding)
	NL_STRING_CONVERSION_TABLE_ENTRY(RmFight)
	NL_STRING_CONVERSION_TABLE_ENTRY(RmMagic)
	NL_STRING_CONVERSION_TABLE_ENTRY(RmHarvest)
	NL_STRING_CONVERSION_TABLE_ENTRY(RmCraft)
	NL_END_STRING_CONVERSION_TABLE(TType, Conversion, Unknown )
}

void CStaticGuildOption::readGeorges (const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const NLMISC::CSheetId &sheetId)
{
	UFormElm &root = form->getRootNode ();
	if ( !root.getValueByName( Price, "price" ) )
	{
		nlwarning("Can get value price in form '%s'",sheetId.toString().c_str());
	}
	string str;
	if ( !root.getValueByName( str, "type" ) )
	{
		nlwarning("Can get value price in form '%s'",sheetId.toString().c_str());
	}
	Type = GUILD_OPTIONS::Conversion.fromString( str );
	if( Type == GUILD_OPTIONS::Unknown )
	{
		nlwarning("sheet %s guild option : invalid type %s",sheetId.toString().c_str(),str.c_str());
	}
}

void CStaticGuildOption::serial(class NLMISC::IStream &f)
{
	f.serial(Price);
	if ( f.isReading() )
	{
		string str;
		f.serial(str);
		Type = GUILD_OPTIONS::Conversion.fromString( str );
		if( Type == GUILD_OPTIONS::Unknown )
		{
			nlwarning("guild option : invalid type %s",str.c_str());
		}
	}
	else
	{
		string str = GUILD_OPTIONS::Conversion.toString( Type );
		f.serial(str);
	}
}
