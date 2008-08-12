/** \file gus_module.cpp
 *
 * $id$
 *
 */

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "gus_module.h"


//-----------------------------------------------------------------------------
// GUS namespace
//-----------------------------------------------------------------------------

namespace GUS
{
	//-----------------------------------------------------------------------------
	// methods IModule
	//-----------------------------------------------------------------------------

	IModule::IModule()
	{
	}

	IModule::~IModule()
	{
	}

	
	//-----------------------------------------------------------------------------
	// utility Routines
	//-----------------------------------------------------------------------------

	NLMISC::CSString extractNamedParameter(const NLMISC::CSString& argName,NLMISC::CSString rawArgs)
	{
		while (!rawArgs.empty())
		{
			NLMISC::CSString keyword;
			NLMISC::CSString args;
			keyword= rawArgs.firstWord(true);
			rawArgs=rawArgs.strip();
			if (rawArgs[0]=='(')
			{
				args=rawArgs.matchDelimiters(true).stripBlockDelimiters();
			}

			if (keyword==argName)
			{
				return args;
			}
		}

		return NLMISC::CSString();
	}

	NLMISC::CSString extractNamedPathParameter(const NLMISC::CSString& argName,NLMISC::CSString rawArgs)
	{
		return NLMISC::CPath::standardizePath(extractNamedParameter(argName,rawArgs).unquoteIfQuoted(),false);
	}
}

