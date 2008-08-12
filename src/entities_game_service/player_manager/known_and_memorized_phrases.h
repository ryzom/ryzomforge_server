 /* \file known_and_memorized_phrases.h
 * 
 *
 * $Id: known_and_memorized_phrases.h,v 1.13 2006/01/23 13:59:36 houlmann Exp $
 */



#ifndef RY_KNOWN_MEMORIZED_PHRASES_H
#define RY_KNOWN_MEMORIZED_PHRASES_H

// game share
#include "game_share/sphrase_com.h"
#include "game_share/memorization_set_types.h"

// the max number of sentence that can be memorized in one set (must match client interface)
const uint8 MaxNbSentencesPerSet			= 20;

class CCharacter;

/**
 * struct for Known Phrases
 */
struct CKnownPhrase
{
	// Start by declaring methods for persistent load/ save operations
	// The following macro is defined in persistent_data.h
	// At time of writing it evaluated to:
	//	void store(CPersistentDataRecord &pdr) const;
	//	void apply(CPersistentDataRecord &pdr);

	DECLARE_PERSISTENCE_METHODS

	CSPhraseCom			PhraseDesc;
	NLMISC::CSheetId	PhraseSheetId;

	bool empty() const;
	void clear();
	void serial(NLMISC::IStream &f) throw(NLMISC::EStream);
};


/**
 * struct for a memorized phrase
 */
struct CMemorizedPhrase
{
	NL_INSTANCE_COUNTER_DECL(CMemorizedPhrase);
public:

	// Start by declaring methods for persistent load/ save operations
	// The following macro is defined in persistent_data.h
	// At time of writing it evaluated to:
	//	void store(CPersistentDataRecord &pdr) const;
	//	void apply(CPersistentDataRecord &pdr);

	DECLARE_PERSISTENCE_METHODS

	CMemorizedPhrase();
	explicit CMemorizedPhrase(const std::vector<NLMISC::CSheetId> &bricks, uint16 id);

	void clear();
	void serial(NLMISC::IStream &f) throw(NLMISC::EStream);

	std::vector<NLMISC::CSheetId>	Bricks;
	uint16							PhraseId;
};

/**
 * struct for memorization sets
 */
struct CMemorizationSet
{
	NL_INSTANCE_COUNTER_DECL(CMemorizationSet);
public:

	// Start by declaring methods for persistent load/ save operations
	// The following macro is defined in persistent_data.h
	// At time of writing it evaluated to:
	//	void store(CPersistentDataRecord &pdr) const;
	//	void apply(CPersistentDataRecord &pdr);

	DECLARE_PERSISTENCE_METHODS

	CMemorizationSet();
	~CMemorizationSet();

	void clear();

	void memorize(uint8 i, const std::vector<NLMISC::CSheetId> &bricks, uint16 id, const TDataSetRow &rowId);

	void memorizeWithoutCheck(uint8 i, const std::vector<NLMISC::CSheetId> &bricks, uint16 id);

	/// memorize starter phrases in easy order for newcomers
	bool memorizeStarterPhrase(const std::vector<NLMISC::CSheetId> &bricks, uint16 id);

	/// memorize in first found empty slot, returns true if successful, make no check
	bool memorizeInFirstEmptySlot(const std::vector<NLMISC::CSheetId> &bricks, uint16 id);
	
	void executePhrase(uint8 i, CCharacter *actor, const TDataSetRow &target, bool cyclic, bool enchant);

	void forget(uint8 i);

	/// forget All phrases
	void forgetAll();

	/// Re-memorise phrases to reconstruct them in case bricks inside had changed.
	void fixPhrases(const std::vector<CKnownPhrase> &knownPhrases, const TDataSetRow &rowId);
	
	const std::vector<CMemorizedPhrase*>	&getMemorizedPhrases() const { return Phrases; }

	void serial(NLMISC::IStream &f) throw(NLMISC::EStream);

private:
	std::vector<CMemorizedPhrase*>	Phrases;

private:
	// prevent copy constructor
	CMemorizationSet(const CMemorizationSet &other) {};
	// prevent copy operator
	CMemorizationSet &operator =(const CMemorizationSet&other) { return *this;}
};


/**
 * struct for all memorized phrase for a player
 */
struct CPlayerPhraseMemory
{
	// Start by declaring methods for persistent load/ save operations
	// The following macro is defined in persistent_data.h
	// At time of writing it evaluated to:
	//	void store(CPersistentDataRecord &pdr) const;
	//	void apply(CPersistentDataRecord &pdr);

	DECLARE_PERSISTENCE_METHODS

	CPlayerPhraseMemory();

	~CPlayerPhraseMemory();

	void clear();

	void memorize(uint8 memorizationSet, uint8 index, const std::vector<NLMISC::CSheetId> &bricks, uint16 id, const TDataSetRow &entityRowId);

	/// memorize starter phrases in easy order for newcomers
	bool memorizeStarterPhrase(const std::vector<NLMISC::CSheetId> &bricks, uint16 id);
	
	/// memorize in first found empty slot, returns true if successful, make no check on phrase validity
	bool memorizeInFirstEmptySlot(const std::vector<NLMISC::CSheetId> &bricks, uint16 id);

	// memorize in given set without any check on phrase validity
	void memorizeWithoutCheck(uint8 memorizationSet, uint8 i, const std::vector<NLMISC::CSheetId> &bricks, uint16 id );
		
	void executePhrase(uint8 memorizationSet, uint8 i, CCharacter *actor, const TDataSetRow &target, bool cyclic, bool enchant);

	void forget(uint8 memorizationSet, uint8 i);

	/// forget all phrases
	void forgetAll();

	/// Re-memorise phrases to reconstruct them in case bricks inside had changed.
	void fixPhrases(const std::vector<CKnownPhrase> &knownPhrases, const TDataSetRow &rowId);

	const std::vector<CMemorizationSet*>	&getMemorizationSets() const { return _MemSets; }

	void serial(NLMISC::IStream &f) throw(NLMISC::EStream);

private:
	CMemorizationSet* getMemSet(uint32 idx);
	std::vector<CMemorizationSet*>	_MemSets;


private:
	// prevent copy constructor
	CPlayerPhraseMemory(const CMemorizationSet &other) {};
	// prevent copy operator
	CPlayerPhraseMemory &operator =(const CMemorizationSet&other) { return *this;}
};




#endif //RY_KNOWN_MEMORIZED_PHRASES_H


/* End of known_and_memorized_phrases.h */
