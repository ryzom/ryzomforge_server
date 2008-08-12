 /* \file modifiers_in_db.h
 * 
 *
 * $Id: modifiers_in_db.h,v 1.8 2005/02/22 10:22:31 besson Exp $
 */


#ifndef RY_MODIFIERS_DB_H
#define RY_MODIFIERS_DB_H

// Game Share
#include "game_share/persistent_data.h"
//
#include "player_manager/cdb.h"
#include "player_manager/cdb_synchronised.h"

// struct for modifier written in DB
struct CModifierInDB
{
	NLMISC::TGameCycle	ActivationDate;
	NLMISC::CSheetId	SheetId;
	bool				Disabled;
	
	// Start by declaring methods for persistent load/ save operations
	// The following macro is defined in persistent_data.h
	// At time of writing it evaluated to:
	//	void store(CPersistentDataRecord &pdr) const;
	//	void apply(CPersistentDataRecord &pdr);

	DECLARE_PERSISTENCE_METHODS

	CModifierInDB();

	void clear();

	void init();

	void serial(NLMISC::IStream &f) throw(NLMISC::EStream);
};

/// struct for disabled modifiers
struct CModifiersInDB
{
	std::vector<CModifierInDB>	Bonus;
	std::vector<CModifierInDB>	Malus;
	
	// Start by declaring methods for persistent load/ save operations
	// The following macro is defined in persistent_data.h
	// At time of writing it evaluated to:
	//	void store(CPersistentDataRecord &pdr) const;
	//	void apply(CPersistentDataRecord &pdr);

	DECLARE_PERSISTENCE_METHODS

	CModifiersInDB();

	void clear();

	void serial(NLMISC::IStream &f) throw(NLMISC::EStream);

	// write disabled effects in DB, used only in initDatabase
	void writeInDatabase(CCDBSynchronised &database);

	void update(CCDBSynchronised &database);

	/// add an active effect
	sint8 addEffect(const NLMISC::CSheetId &sheetId, bool bonus, CCDBSynchronised &database);

	/// remove an effect
	void removeEffect(uint8 index, bool bonus, CCDBSynchronised &database);

	/// disable an effect
	void disableEffect(uint8 index, bool bonus, NLMISC::TGameCycle activationDate, CCDBSynchronised &database);
	
private:
	void _addBonus(const CModifierInDB& bonus);
	void _addMalus(const CModifierInDB& malus);
};


#endif //RY_MODIFIERS_DB_H


/* End of modifiers_in_db.h */
