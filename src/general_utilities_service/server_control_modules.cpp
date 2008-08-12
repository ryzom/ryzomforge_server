/** \file server_control_modules.cpp
 *
 * $id$
 *
 */

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

// local
#include "game_share/file_description_container.h"
#include "server_control_modules.h"


//-----------------------------------------------------------------------------
// private utility routines
//-----------------------------------------------------------------------------

static uint32 readVersionFile(const NLMISC::CSString& fileName)
{
	if (!NLMISC::CFile::fileExists(fileName))
	{
		return 0;
	}

	NLMISC::CSString s;
	s.readFromFile(fileName);
	return s.strip().atoi();
}


//-----------------------------------------------------------------------------
// public utility routines
//-----------------------------------------------------------------------------

static NLMISC::CSString _rrBusyMarkerFileNameBase(const NLMISC::CSString& targetDirectory)
{
	return targetDirectory+(targetDirectory.right(1)=="/"?"":"/")+"rr_busy_";
}

NLMISC::CSString rrBusyMarkerFileName(const NLMISC::CSString& targetDirectory,const NLMISC::CSString& emitterName)
{
	return _rrBusyMarkerFileNameBase(targetDirectory)+emitterName;
}

bool rrBusyMarkerFilesExist(const NLMISC::CSString& targetDirectory)
{
	CFileDescriptionContainer fdc;
	fdc.addFileSpec(_rrBusyMarkerFileNameBase(targetDirectory)+"*",false);
	return !fdc.empty();
}


//-----------------------------------------------------------------------------
// methods CServerDirectories
//-----------------------------------------------------------------------------

CServerDirectories::CServerDirectories()
{
	_Initialised= false;
}

CServerDirectories::CServerDirectories(const NLMISC::CSString& rootDirectory,const NLMISC::CSString& domainName)
{
	_Initialised= false;
	init(rootDirectory,domainName);
}

void CServerDirectories::init(const NLMISC::CSString& rootDirectory,const NLMISC::CSString& domainName)
{
	// setup our data
	_RootDirectory= NLMISC::CPath::standardizePath(rootDirectory.strip());
	_DomainName= domainName.strip();

	// flag ourselves as initialised
	_Initialised= true;

	// create any missing directories
	NLMISC::CFile::createDirectoryTree(patchDirectoryName());
	NLMISC::CFile::createDirectoryTree(liveDirectoryName());
	NLMISC::CFile::createDirectoryTree(installDirectoryName());
}


//-----------------------------------------------------------------------------

NLMISC::CSString CServerDirectories::getDomainName() const
{
	return _DomainName;
}

NLMISC::CSString CServerDirectories::getRootDirectory() const
{
	return _RootDirectory;
}


//-----------------------------------------------------------------------------

NLMISC::CSString CServerDirectories::patchDirectoryName() const
{
	nlassert(_Initialised);

	return _RootDirectory+"patch/";
}

NLMISC::CSString CServerDirectories::liveDirectoryName() const
{
	nlassert(_Initialised);

	return _RootDirectory+"live/";
}

NLMISC::CSString CServerDirectories::installDirectoryName() const
{
	nlassert(_Initialised);

	return _RootDirectory+"next/";
}


//-----------------------------------------------------------------------------

NLMISC::CSString CServerDirectories::liveVersionFileName() const
{
	nlassert(_Initialised);

	return liveDirectoryName()+"version";
}

NLMISC::CSString CServerDirectories::installVersionFileName() const
{
	nlassert(_Initialised);

	return installDirectoryName()+"version";
}

NLMISC::CSString CServerDirectories::launchRequestVersionFileName() const
{
	nlassert(_Initialised);

	return patchDirectoryName()+"cmd_"+_DomainName+"_version_launch";
}

NLMISC::CSString CServerDirectories::installRequestVersionFileName() const
{
	nlassert(_Initialised);

	return patchDirectoryName()+"cmd_"+_DomainName+"_version_install";
}


//-----------------------------------------------------------------------------

bool CServerDirectories::isPatchDirectoryReady() const
{
	nlassert(_Initialised);

	return !rrBusyMarkerFilesExist(patchDirectoryName());
}

bool CServerDirectories::isLaunchRequestValid() const
{
	nlassert(_Initialised);

	return (isLaunchRequestLive() || getLaunchRequestVersion()==getInstallRequestVersion());
}

bool CServerDirectories::isLaunchRequestLive() const
{
	nlassert(_Initialised);

	return getLaunchRequestVersion()== getLiveVersion();
}

bool CServerDirectories::isInstallRequestInstalled() const
{
	nlassert(_Initialised);

	return getInstallRequestVersion()== getInstalledVersion();
}


//-----------------------------------------------------------------------------

uint32 CServerDirectories::getLiveVersion() const
{
	nlassert(_Initialised);

	return readVersionFile(liveVersionFileName());
}

uint32 CServerDirectories::getInstalledVersion() const
{
	nlassert(_Initialised);

	return readVersionFile(installVersionFileName());
}

uint32 CServerDirectories::getLaunchRequestVersion() const
{
	nlassert(_Initialised);

	return readVersionFile(launchRequestVersionFileName());
}

uint32 CServerDirectories::getInstallRequestVersion() const
{
	nlassert(_Initialised);

	return readVersionFile(installRequestVersionFileName());
}


//-----------------------------------------------------------------------------

void CServerDirectories::writeInstallVersion(uint32 version) const
{
	NLMISC::CSString(NLMISC::toString(version)).writeToFile(installVersionFileName());
}

