/** \file fdc_cache.cpp
 *
 */


//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

#include "nel/misc/command.h"
#include "game_share/utils.h"
#include "fdc_cache.h"


//-------------------------------------------------------------------------------------------------
// namespaces
//-------------------------------------------------------------------------------------------------

using namespace std;
using namespace NLMISC;


//-------------------------------------------------------------------------------------------------
// methods CFdcCache
//-------------------------------------------------------------------------------------------------

const CFileDescriptionContainer& CFdcCache::getFdc() const
{
	return _Fdc;
}

void CFdcCache::addFileSpec(const NLMISC::CSString& fspec,bool recurse)
{
	_Fdc.addFileSpec(fspec,recurse);
}

void CFdcCache::addFile(const NLMISC::CSString& fileName)
{
	_Fdc.addFile(fileName);
}


void CFdcCache::clear()
{
	_Fdc.clear();
}


//-------------------------------------------------------------------------------------------------
// COMMANDS for CFdcCache
//-------------------------------------------------------------------------------------------------

NLMISC_CATEGORISED_COMMAND(Stats,fdcCacheClear,"clear out the file description cache","")
{
	if (!args.empty())
		return false;

	CFdcCache::getInstance().clear();

	return true;
}

NLMISC_CATEGORISED_COMMAND(Stats,fdcCacheAddFileSpec,"add a filespecs to the FDC cache","<filespec>")
{
	if (args.size()!=1)
		return false;

	nldebug("fdcCacheAddFileSpec: %s",args[0].c_str());
	uint32 oldSize= CFdcCache::getInstance().getFdc().size();

	CFdcCache::getInstance().addFileSpec(args[0],false);

	uint32 newSize= CFdcCache::getInstance().getFdc().size();
	nlinfo("fdcCacheAddFileSpec: %s: added %u files => %u files total",args[0].c_str(),newSize-oldSize,newSize);

	return true;
}

NLMISC_CATEGORISED_COMMAND(Stats,fdcCacheAddFileSpecRecurse,"add a filespecs to the FDC cache","<filespec>")
{
	if (args.size()!=1)
		return false;

	nldebug("fdcCacheAddFileSpecRecurse: %s",args[0].c_str());
	uint32 oldSize= CFdcCache::getInstance().getFdc().size();

	CFdcCache::getInstance().addFileSpec(args[0],true);

	uint32 newSize= CFdcCache::getInstance().getFdc().size();
	nlinfo("fdcCacheAddFileSpecRecurse: %s: added %u files => %u files total",args[0].c_str(),newSize-oldSize,newSize);

	return true;
}

NLMISC_CATEGORISED_COMMAND(Stats,fdcCacheAddFileList,"add the list of files contained in the 'list file' to the FDC cache","<list_file_name>")
{
	if (args.size()!=1)
		return false;

	nldebug("fdcCacheAddFileList: %s",args[0].c_str());

	NLMISC::CSString fileList;
	fileList.readFromFile(args[0]);

	uint32 oldSize= CFdcCache::getInstance().getFdc().size();

	NLMISC::CVectorSString files;
	fileList.splitLines(files);
	for(uint32 i=0;i<files.size();++i)
	{
		NLMISC::CSString theFile= files[i].splitTo("//").strip();
		if (theFile.empty())
			continue;
		CFdcCache::getInstance().addFile(theFile);
	}

	uint32 newSize= CFdcCache::getInstance().getFdc().size();
	nlinfo("fdcCacheAddFileList: %s: added %u files => %u files total",args[0].c_str(),newSize-oldSize,newSize);

	return true;
}

