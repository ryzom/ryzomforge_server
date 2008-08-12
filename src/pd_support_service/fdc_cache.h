/** \file fdc_cache.h
 *
 */


#ifndef FDC_CACHE_H
#define FDC_CACHE_H


//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

#include "nel/misc/singleton.h"
#include "game_share/file_description_container.h"


//-------------------------------------------------------------------------------------------------
// class CFdcCache
//-------------------------------------------------------------------------------------------------

class CFdcCache: public NLMISC::CSingleton<CFdcCache>
{
public:
	const CFileDescriptionContainer& getFdc() const;
	void CFdcCache::addFileSpec(const NLMISC::CSString& fspec,bool recurse);
	void CFdcCache::addFile(const NLMISC::CSString& fileName);
	void CFdcCache::clear();

private:
	CFileDescriptionContainer _Fdc;
};


//-------------------------------------------------------------------------------------------------

#endif // FDC_CACHE_H
