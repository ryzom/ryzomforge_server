/** \pvp_faction.h
 * 
 *
 * $Id: pvp_faction_hof.h,v 1.4 2005/10/20 13:19:15 saffray Exp $
 */

#ifndef RY_PVP_HOF_H
#define RY_PVP_HOF_H

#include "game_share/pvp_clan.h"

class CCharacter;

/**
 * PVP Faction Hall of Fame db write interface
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2005
 */
class CPVPFactionHOF
{
	NL_INSTANCE_COUNTER_DECL(CPVPFactionHOF);
public:

	enum THOFStat
	{
		faction_point,
		kill,
		final_blow,
		lost,
		builded_spire,
		destroyed_spire,
	};

	enum TPeriodStat
	{
		daily,
		weekly,
		monthly,
		global
	};

	///\name LOW LEVEL MANAGEMENT
	//@{
	/// singleton init
	static void init();
	/// singleton release
	static void release();
	/// instance accessor
	static CPVPFactionHOF* getInstance();
	/// callback called at each tick
	void tickUpdate();
	//@}

	// return string of period
	const std::string& getPeriodStatString( TPeriodStat period ) const;

	// return string of stat
	const std::string& getStatString( THOFStat stat ) const;

	// write a value in HOF database
	void writeStatInHOFDatabase( CCharacter * pc, PVP_CLAN::TPVPClan clan, THOFStat stat, sint32 value ) const;

private:
	// constructor
	CPVPFactionHOF() { lastDayOfMonthHOFDone = 0; }
	// destructor
	~CPVPFactionHOF() {}

	// clear Daily Hall of Fame database
	void clearDailyHOFDatabase();
	// clear Weekly Hall of Fame database
	void clearWeeklyHOFDatabase();
	// clear Monthly Hall of Fame database
	void clearMonthlyHOFDatabase();

	// create Daily Hall of Fame database
	void createDailyHOFDatabase();
	// create Weekly Hall of Fame database
	void createWeeklyHOFDatabase();
	// create Monthly Hall of Fame database
	void createMonthlyHOFDatabase();
	// create Global Hall of Fame database
	void createGlobalHOFDatabase();
	// set player and guild HOF points
	void setHallOfFame( std::string sdbPvPPath, CCharacter * pc, sint32 value, THOFStat stat ) const;
	// set player and guild kill/death HOF points
	void setHallOfFameKillDeathRatio( std::string sdbPvPPath, CCharacter * pc ) const;

	// singleton pointer
	static CPVPFactionHOF * _Instance;

	static const std::string _dailyString;
	static const std::string _weeklyString;
	static const std::string _monthlyString;
	static const std::string _globalString;

	static const std::string _FactionPointString;
	static const std::string _KillString;
	static const std::string _FinalBlowString;
	static const std::string _LostString;
	static const std::string _BuildedSpire;
	static const std::string _DestroyedSpire;

	static sint32 lastDayOfMonthHOFDone;
};

#endif //RY_PVP_HOF_H
