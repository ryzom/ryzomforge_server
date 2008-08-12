/** \file server_control_modules.h
 *
 * $id$
 *
 */

#ifndef SERVER_CONTROL_MODULES_H
#define SERVER_CONTROL_MODULES_H


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "nel/misc/types_nl.h"
#include "nel/misc/sstring.h"


//-----------------------------------------------------------------------------
// utility routines
//-----------------------------------------------------------------------------

NLMISC::CSString rrBusyMarkerFileName(const NLMISC::CSString& targetDirectory,const NLMISC::CSString& reName);
bool rrBusyMarkerFilesExist(const NLMISC::CSString& targetDirectory);


//-----------------------------------------------------------------------------
// class CServerDirectories
//-----------------------------------------------------------------------------

class CServerDirectories
{
public:
	CServerDirectories();
	CServerDirectories(const NLMISC::CSString& rootDirectory,const NLMISC::CSString& domainName);
	void init(const NLMISC::CSString& rootDirectory,const NLMISC::CSString& domainName);

	NLMISC::CSString getDomainName() const;
	NLMISC::CSString getRootDirectory() const;

	NLMISC::CSString patchDirectoryName() const;
	NLMISC::CSString liveDirectoryName() const;
	NLMISC::CSString installDirectoryName() const;

	NLMISC::CSString liveVersionFileName() const;
	NLMISC::CSString installVersionFileName() const;
	NLMISC::CSString launchRequestVersionFileName() const;
	NLMISC::CSString installRequestVersionFileName() const;

	bool isPatchDirectoryReady() const;
	bool isLaunchRequestValid() const;
	bool isLaunchRequestLive() const;
	bool isInstallRequestInstalled() const;

	uint32 getLiveVersion() const;
	uint32 getInstalledVersion() const;
	uint32 getLaunchRequestVersion() const;
	uint32 getInstallRequestVersion() const;

	void writeInstallVersion(uint32 version) const;

private:
	NLMISC::CSString _RootDirectory;
	NLMISC::CSString _DomainName;
	bool _Initialised;
};

#endif
