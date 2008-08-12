/** \file processing_spreader.cpp
 * Spreading an iterating process onto several game cycles.
 *
 * $Id: processing_spreader.cpp,v 1.4 2004/05/27 18:25:36 cado Exp $
 */



#include "stdpch.h"
#include "processing_spreader.h"
#include "frontend_service.h"


/*
 * Constructor
 */
CProcessingSpreader::CProcessingSpreader() :
	ExecutionPeriod(1), _ClientMapIndex(0), _Invalidated(true)
#ifdef TEST_WORSE_EXECUTION_PERIOD
	, _Count(0)
#endif
{
}


/*
 * Initialization
 */
void CProcessingSpreader::init()
{
	_ClientMapIterator = CFrontEndService::instance()->receiveSub()->clientMap().end();
}


/*
 * Get the range (beginning iterator, index and outer bound) for the current processing
 */
void CProcessingSpreader::getProcessingBounds( THostMap::iterator& firstit, sint& firstindex, sint& outerboundindex )
{
	THostMap& clientmap = CFrontEndService::instance()->receiveSub()->clientMap();
	sint nbClients = clientmap.size();

	// Test if the index has reached the end of the client map
	if ( _ClientMapIndex >= nbClients )
	{
		// The range begins at the beginning of the client map
		firstit = clientmap.begin();
		firstindex = 0;
	}
	else
	{
		// Return the current iterator (if it is valid)
		if ( _Invalidated )
		{
			_Invalidated = false;

			// Rescan the client map to get the new iterator
			// It is necessary when the client referenced by _ClientMapIndex left the FE.
			THostMap::iterator it = clientmap.begin();
			for ( sint i=0; i!=_ClientMapIndex; ++i, ++it );
			firstit = it;
			firstindex = _ClientMapIndex;
			//nlinfo( "%p: Scanning client map to index %d, iterator %p", this, firstindex, firstit );
		}
		else
		{
			// _ClientMapIterator is valid if and only if endProcessing() was called
			// since the previous getProcessingBounds()
			firstit = _ClientMapIterator;
			firstindex = _ClientMapIndex;
			//nlinfo( "%p: Giving back index %d, iterator %p", this, firstindex, firstit );
		}
	}

	sint maxNbClientsProcessedPerTick = MaxNbClients / ExecutionPeriod;
	outerboundindex = firstindex + min( maxNbClientsProcessedPerTick, nbClients - firstindex );
	_ClientMapIndex = outerboundindex;
}


/*
 * Method to call after a new client is added into the clientmap
 */
void CProcessingSpreader::notifyClientAddition( THostMap::iterator endBeforeAddition )
{
	THostMap& clientmap = CFrontEndService::instance()->receiveSub()->clientMap();
	//nlinfo( "%p: Addition, iterator=%p", this, _ClientMapIterator );

	// NEW: Always (because an addition may be an insertion => mismatch between index and iterator)
	_ClientMapIterator = clientmap.begin();
	_ClientMapIndex = 0;

	// If _ClientMapIterator was pointed on the end, reset it
	/*if ( _ClientMapIterator == endBeforeAddition )
	{
		// Necessary for getProcessingBounds() to work when there is no invalidation
		_ClientMapIterator = clientmap.begin();
		//nlinfo( "%p: Resetting to begin", this );
	}
	*/
}


void CProcessingSpreader::notifyClientRemoval( THostMap::iterator icm )
{
	//nlinfo( "%p: Removal", this );
	if ( (!_Invalidated) && (_ClientMapIterator == icm) ) // without the test of !_Invalidated, stldebug will cry in operator==() if calling notifyClientRemoval() twice (the second time, _ClientMapIterator points to an erased element)
	{
		_Invalidated = true;
		//nlinfo( "%p: Iterator=%p leaving => invalidate!" );
	}
}
