/** \file range_mirror_manager.h
 * <File description>
 *
 * $Id: range_mirror_manager.h,v 1.12 2007/03/09 09:56:57 boucher Exp $
 */



#ifndef NL_RANGE_MIRROR_MANAGER_H
#define NL_RANGE_MIRROR_MANAGER_H

#include <nel/misc/types_nl.h>
#include <nel/misc/stream.h>

#include "game_share/base_types.h"

#include <vector>
#include <string>
#include <list>
#include <map>

namespace NLNET
{
	class CMessage;
}


typedef std::list<TRowRange> TRangeList;


/*
 *
 */
class CRangeList
{
public:

	/// Default constructor
	CRangeList() : _TotalMaxRows(~0) { acquireFirstRow(); }

	/// Constructor
	CRangeList( sint32 totalMaxRows ) : _TotalMaxRows( totalMaxRows ) { acquireFirstRow(); }

	/// Acquire the row 0
	void					acquireFirstRow();

	/** Acquire a range and return the bounds, if it is possible with the limit
	 * of total max rows in the dataset.
	 */
	bool					acquireRange( NLNET::TServiceId ownerServiceId, NLNET::TServiceId mirrorServiceId, sint32 nbRows, TDataSetIndex *first, TDataSetIndex *last );

	/// Release a range previously acquired (only the first one found)
	bool					releaseOneRange( NLNET::TServiceId ownerServiceId );

	/// Release all acquired ranges
	void					releaseAllRanges();

	/// Release ranges by MS
	void					releaseRangesByMS( NLNET::TServiceId msId, std::vector<TRowRange>& erasedRanges );

	/// Reacquire ranges
	void					reacquireRange( NLNET::TServiceId ownerServiceId, NLNET::TServiceId mirrorServiceId, TDataSetIndex first, TDataSetIndex last );

	// Release the ranges for services that are not alive (return true if any)
	//bool					releaseRangesForServicesDown();

	/// Display the ranges
	void					displayRanges( NLMISC::CLog *log=NLMISC::InfoLog );

	/// Serial
	void					serial( NLMISC::IStream& s );

	/// Return the maximum number of rows in the dataset
	sint					totalMaxRows() const { return _TotalMaxRows; }

protected:

	/** Insert if possible a range with the specified arguments before iCurrentRange
	 * If iCurrentRange is _RangeList.begin(), set prevLast to -1 to try to insert at the beginning.
	 * If iCurrentRange is _RangeList.end(), appends a new range at the end of the list.
	 * At exit, iCurrentRange is set to point to the new range.
	 */
	bool					rangeInserted( NLNET::TServiceId ownerServiceId, NLNET::TServiceId mirrorServiceId, sint32 nbRows, TDataSetIndex prevLast, TRangeList::iterator& iCurrentRange )
	{
		if ( (iCurrentRange == _RangeList.end()) || (prevLast + nbRows < (*iCurrentRange).First) )
		{
			TRowRange newrange;
			newrange.First = prevLast+1;
			newrange.Last = prevLast+nbRows;
			newrange.OwnerServiceId = ownerServiceId;
			newrange.MirrorServiceId = mirrorServiceId;
			iCurrentRange = _RangeList.insert( iCurrentRange, newrange );
			return true;
		}
		else
		{
			return false;
		}
	}

private:

	/// Maximum number of rows
	sint32					_TotalMaxRows;

	TRangeList				_RangeList;
};


typedef std::map<std::string, CRangeList> TRangeListByDataSet;
#define GET_RANGE_LIST(ids) ((*ids).second)


/**
 * Manager for entity ranges by service / dataset
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2002
 */
class CRangeMirrorManager
{
public:

	/// Constructor
	CRangeMirrorManager();

	/// Init
	void		init();

	/// Get a range
	void		getRange( const std::vector<std::string>& datasetNames, sint32 nbRows, NLNET::TServiceId declaratorServiceId, NLNET::TServiceId mirrorServiceId, uint8 entityTypeId );

	/// Release a range
	void		releaseRanges( const std::vector<std::string>& datasetNames, NLNET::TServiceId declaratorServiceId, NLNET::TServiceId mirrorServiceId );

	/// Reacquire ranges after a service failure or shutdown
	void		reacquireRanges( NLNET::CMessage& msgin, NLNET::TServiceId mirrorServiceId );

	/// Release all ranges owned by a service
	void		releaseRangesByService( NLNET::TServiceId declaratorServiceId );

	/// Release all acquired ranges
	void		releaseAllRanges();

	/// Release ranges by MS
	void		releaseRangesByMS( NLNET::TServiceId msId );

	/// Display all the ranges
	void		displayRanges( NLMISC::CLog *log=NLMISC::InfoLog );

	/// Save the ranges into a data file
	void		saveRanges();

	/// Load the ranges from a data file
	void		loadRanges();

private:

	TRangeListByDataSet		_RangeListByDataSet;
};


#endif // NL_RANGE_MIRROR_MANAGER_H

/* End of range_mirror_manager.h */
