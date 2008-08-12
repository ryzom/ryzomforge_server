/** \file server_patch_types.h
 *
 *
 */

#ifndef SERVER_PATCH_TYPES_H
#define SERVER_PATCH_TYPES_H

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/misc/types_nl.h"
#include "nel/misc/sstring.h"


namespace PATCHMAN
{
	//-----------------------------------------------------------------------------
	// handy type definitions
	//-----------------------------------------------------------------------------

	// A map of module ids to module states
	typedef std::map<NLMISC::CSString,NLMISC::CSString> TModuleStates;

	// A map of domain names to domain info records (containing version numbers for the domain)
	struct SDomainInfo
	{
		uint32 LaunchVersion;
		uint32 InstallVersion;

		SDomainInfo()
		{
			LaunchVersion= ~0u;
			InstallVersion= ~0u;
		}
	};
	typedef std::map<NLMISC::CSString,SDomainInfo> TDomains;

	// A map of version names to version info records (containing paired version numbers for the server and client)
	struct SNamedVersionInfo
	{
		uint32 ServerVersion;
		uint32 ClientVersion;

		SNamedVersionInfo()
		{
			ServerVersion= ~0u;
			ClientVersion= ~0u;
		}
	};
	typedef std::map<NLMISC::CSString,SNamedVersionInfo> TNamedVersions;
}

//-----------------------------------------------------------------------------
#endif
