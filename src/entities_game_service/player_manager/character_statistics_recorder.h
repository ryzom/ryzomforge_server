/** \file character_statistics_recorder.h
 *
 * $Id: character_statistics_recorder.h,v 1.2 2004/12/08 13:26:43 besson Exp $
 */

#ifndef CHARACTER_STATISTICS_RECORDER_H
#define CHARACTER_STATISTICS_RECORDER_H


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

// game share
#include "game_share/ryzom_entity_id.h"
#include "game_share/character_summary.h"
#include "game_share/gender.h"
#include "game_share/persistent_data.h"

//-----------------------------------------------------------------------------
// advanced class declarations
//-----------------------------------------------------------------------------

class CCharacter;


//-----------------------------------------------------------------------------
// class CCharaterStatisticsRecorderRecord
//-----------------------------------------------------------------------------

class CCharaterStatisticsRecorderRecord
{
public:
	// Start by declaring methods for persistent load/ save operations
	// The following macro is defined in persistent_data.h
	// At time of writing it evaluated to:
	//	void store(CPersistentDataRecord &pdr) const;
	//	void apply(CPersistentDataRecord &pdr);

	DECLARE_PERSISTENCE_METHODS

	CCharaterStatisticsRecorderRecord();
	~CCharaterStatisticsRecorderRecord();

	void clear();
	void build(const CCharaterStatisticsRecorderRecord& last, CCharacter* character);
	
private:
	uint32 _TicksInGame;
	uint64 _TimeInGame;
	uint32 _TotalXP;
};


//-----------------------------------------------------------------------------
// class CCharaterStatisticsRecorderContainer
//-----------------------------------------------------------------------------

class CCharaterStatisticsRecorderContainer
{
public:
	// Start by declaring methods for persistent load/ save operations
	// The following macro is defined in persistent_data.h
	// At time of writing it evaluated to:
	//	void store(CPersistentDataRecord &pdr) const;
	//	void apply(CPersistentDataRecord &pdr);

	DECLARE_PERSISTENCE_METHODS

	CCharaterStatisticsRecorderContainer();
	~CCharaterStatisticsRecorderContainer();

	void clear();
	void add(CCharacter* character);
	
private:
	uint32 _Counter;
	std::vector<CCharaterStatisticsRecorderRecord> _Sessions1;
	std::vector<CCharaterStatisticsRecorderRecord> _Sessions10;
	std::vector<CCharaterStatisticsRecorderRecord> _Sessions100;
};


//-----------------------------------------------------------------------------
#endif
