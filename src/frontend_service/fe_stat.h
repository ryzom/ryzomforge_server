/** \file fe_stat.h
 * <File description>
 *
 * $Id: fe_stat.h,v 1.8 2004/03/01 19:21:52 lecroart Exp $
 */



#ifndef NL_FE_STAT_H
#define NL_FE_STAT_H


//#define MEASURE_FRONTEND_TABLES
#ifdef MEASURE_FRONTEND_TABLES


#include <nel/misc/types_nl.h>
#include <nel/misc/time_nl.h>
#include <vector>


/*
 * TEventPerSeenEntityCounterFrame
 */
struct TEventPerSeenEntityCounterFrame
{
	NLMISC::TGameCycle	Tick;
	sint32				SeenEntities [MAX_SEEN_ENTITIES_PER_CLIENT];
	float				Value; // optional value

	/// Constructor
	TEventPerSeenEntityCounterFrame() : Tick(0)
	{
		reset();
	}

	/// reset
	void				reset( sint32 def=0 )
	{
		sint i;
		for ( i=0; i!=MAX_SEEN_ENTITIES_PER_CLIENT; ++i )
			SeenEntities[i] = def;
	}

	/// setGameTick
	void				setGameTick();
	
	/// commit
	void				commit( std::vector<TEventPerSeenEntityCounterFrame>& vect )
	{
		vect.push_back( *this );
	}

	/// display
	void				display( bool withvalue=false );

	/// displayAll
	static void			displayAll( const char *name, std::vector<TEventPerSeenEntityCounterFrame>& vect, bool withvalue=false );
};



extern TEventPerSeenEntityCounterFrame				PropRecvrCntFrame1, PropRecvrCntFrame2,
													DistCntFrame,
													DeltaCntFrame,
													PrioCntFrame,
													PosSentCntFrame;

extern std::vector<TEventPerSeenEntityCounterFrame>	PropRecvrCntClt1,
													DistCntClt1,
													DeltaCntClt1,
													PrioCntClt1,
													PosSentCntClt1;

#endif

#endif // NL_FE_STAT_H

/* End of fe_stat.h */
