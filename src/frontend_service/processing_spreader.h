/** \file processing_spreader.h
 * Spreading an iterating process onto several game cycles.
 *
 * $Id: processing_spreader.h,v 1.2 2004/03/01 19:21:52 lecroart Exp $
 */



#ifndef NL_PROCESSING_SPREADER_H
#define NL_PROCESSING_SPREADER_H

#include "nel/misc/types_nl.h"
#include "fe_types.h"

// Test with the least frequent period even at low load (define=yes/undef=no)
#undef TEST_WORSE_EXECUTION_PERIOD


/**
 * This class is aimed to spread an iterating process onto several game cycles,
 * when it is too long to be executed in one game cycle.
 * When mustProcessNow() returns true, call getProcessingBounds() to get the
 * range, in the client map, of clients to process.
 * After processing them, call endProcessing().
 * After any cycle, call incCycle().
 * When a client leaves the front-end, call notifyClientRemoval().
 *
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2002
 */
class CProcessingSpreader
{
public:

	/// Constructor
	CProcessingSpreader();

	/// Initialization
	void					init();

	/// Execution period in game cycle
	sint32					ExecutionPeriod;

	/// Return true if the process must be executed at the current cycle
	bool					mustProcessNow()
	{
#ifdef TEST_WORSE_EXECUTION_PERIOD
		return (_Count == 0);
#else
		return true;
#endif
	}

	/// Get the range (beginning iterator, index and outer bound) for the current processing
	void					getProcessingBounds( THostMap::iterator& firstit, sint& firstindex, sint& outerboundindex );

	/// Method to call at the end of a processing
	void					endProcessing( THostMap::iterator icm )
	{
		_ClientMapIterator = icm;
#ifdef TEST_WORSE_EXECUTION_PERIOD
		_Count = ExecutionPeriod;
#endif
	}

	/// Method to call every cycle, possibly after processing
	void					incCycle()
	{
#ifdef TEST_WORSE_EXECUTION_PERIOD
		--_Count;
#endif
	}

	/// Method to call after a new client is added into the clientmap (give it clientmap.end() before the addition!)
	void					notifyClientAddition( THostMap::iterator endBeforeAddition );

	/// Method to call when a client leaves
	void					notifyClientRemoval( THostMap::iterator icm );
	
private:

#ifdef TEST_WORSE_EXECUTION_PERIOD
	/// Execution counter
	sint32					_Count;
#endif

	/// Current map index
	sint32					_ClientMapIndex;

	/// Current map iterator
	THostMap::iterator		_ClientMapIterator;

	/// True if ClientMapIterator is invalid
	bool					_Invalidated;
};


#endif // NL_PROCESSING_SPREADER_H

/* End of processing_spreader.h */
