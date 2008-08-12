/** \file ai_alias_translator.h
 * <File description>
 *
 * $Id: ai_alias_translator.h,v 1.26 2006/05/31 12:10:21 boucher Exp $
 */



#ifndef RY_AI_ALIAS_TRANSLATOR_H
#define RY_AI_ALIAS_TRANSLATOR_H

#include "nel/ligo/primitive.h"
#include "game_share/misc_const.h"
#include "game_share/ryzom_entity_id.h"

#include <hash_map>


/**
 * Singleton used to get a bot entity id from its AI id and vice-versa
 * Useful because AIIDs are guaranted to be the same between two server sessions
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2002
 */
class CAIAliasTranslator
{
public:
	static const TAIAlias Invalid;

	///\return the singleton's instance and create it if it does not exist
	static inline CAIAliasTranslator* getInstance();

	///\init the translator
	static void init();

	// release the singleton's data
	static void release();

	/**
	 * update the association between a bot AI id and its entity id
	 * \param AIId : the AI id of the entity
	 * \param entityId : the CEntityId of the entity
	 */
	inline void updateAssociation(TAIAlias aiid, const NLMISC::CEntityId& entityId);

	/// remove an association
	inline void removeAssociation(NLMISC::CEntityId& entityId);
	
	/**
	 * Get a bot entityId
	 * \param aiid : the AI id of the bot
	 * \return the entityId of the searched bot
	 */
	inline const NLMISC::CEntityId & getEntityId(TAIAlias aiid) const;

	/**
	 * Get a bot AIId
	 * \param entityId: the entityId of the searched bot
	 * \return he AI id of the bot	 
	 */
	TAIAlias getAIAlias(const NLMISC::CEntityId & entityId) const;


	/**
	 * Get a bot unique id from its name
	 * \param botName : name of the bot
	 * \param ret : vector of names
	 */
	inline void getNPCAliasesFromName(const std::string & botName, std::vector<TAIAlias> & ret) const;

	/**
	 * Get a bot unique id from its name
	 * \param botName : name of the bot
	 * \param ret : vector of names
	 */
	inline void getNPCAliasesFromNameInSet(const std::string & botName, std::set<TAIAlias> & ret) const;

	/**
	 * get the name of a bot from its alias
	 * \param alias alias of the bot
	 * \return true on success
	 * \param ret: ref on a string storing the bot name
	 */
	inline bool getNPCNameFromAlias(TAIAlias alias,std::string & ret) const;

	/**
	 * Get a mission unique id from its name
	 * \param botName : name of the bot
	 * \return the id of the bot (invalid if not found
	 */
	inline TAIAlias getMissionUniqueIdFromName(const std::string & missionName) const;

	/**
	 * Retreive the mission name given the alias
	 * WARNING : SLOW : use it only for commands / stats ( iteration through a hash_map )
	 */
	inline const std::string &getMissionNameFromUniqueId(TAIAlias alias) const;
	
	/**
	 * Get an AI groupalias from its name
	 * \param botName : name of the group
	 * \param aliases: vrctor receiving the aliases
	 */
	inline void getGroupAliasesFromName(const std::string & name, std::vector< TAIAlias >& aliases) const;


	/**
	 * Send alias, and eid to ios via mirror.	 
	 */

	void sendAliasToIOS() const	;


private:
	/**
	 * build the bot tree from a primitive ( set the association between bots and id );
	 * \param prim : the primitive to be parsed
	 */
	void buildBotTree(const NLLIGO::IPrimitive* prim);

	/**
	 * build the mission tree from a primitive ( set the association between mission names and id );
	 * \param prim : the primitive to be parsed
	 */
	void buildMissionTree(const NLLIGO::IPrimitive* prim);
	
	/// Constructor (private because it is a singleton)
	CAIAliasTranslator();

	/// destructor (private because this singleton must be deleted through the release method)
	~CAIAliasTranslator();

	/// singleton instance
	static CAIAliasTranslator* _Instance;

	/// hash table using AI id as keys
	std::hash_map< uint, NLMISC::CEntityId >						_HashTableAiId;
	std::hash_map< NLMISC::CEntityId, TAIAlias,NLMISC::CEidHash >	_HashTableEntityId;
	
	/// map linking bot names to ids
	std::hash_multimap< std::string, TAIAlias >		_BotNamesToIds;
	/// map linking bot ids to names
	std::hash_map< uint, std::string >			_BotIdsToNames;
	/// map linking mission names to ids
	std::hash_map< std::string, TAIAlias >		_MissionNamesToIds;
	/// map linking AI group names to IDS
	std::hash_multimap< std::string, TAIAlias > _AIGroupNamesToIds;

	/// bool set to true if the mission and bot names must be kept
	bool _KeepNames;
};

//-----------------------------------------------
// CAIAliasTranslator getNPCAliasesFromName
//-----------------------------------------------
inline void CAIAliasTranslator::getNPCAliasesFromName(const std::string & botName, std::vector<TAIAlias> & ret) const
{
	ret.clear();
	std::string lwr = NLMISC::strlwr(botName);
	std::pair< std::hash_multimap< std::string, TAIAlias>::const_iterator, std::hash_multimap< std::string, TAIAlias>::const_iterator > result = _BotNamesToIds.equal_range(lwr);
	for ( std::hash_multimap< std::string, TAIAlias>::const_iterator it = result.first; it != result.second; ++it )
	{
		ret.push_back( (*it).second );
	}
}

//-----------------------------------------------
// CAIAliasTranslator getNPCAliasesFromNameInSet
//-----------------------------------------------
inline void CAIAliasTranslator::getNPCAliasesFromNameInSet(const std::string & botName, std::set<TAIAlias> & ret) const
{
	ret.clear();
	std::string lwr = NLMISC::strlwr(botName);
	std::pair< std::hash_multimap< std::string, TAIAlias>::const_iterator, std::hash_multimap< std::string, TAIAlias>::const_iterator > result = _BotNamesToIds.equal_range(lwr);
	for ( std::hash_multimap< std::string, TAIAlias>::const_iterator it = result.first; it != result.second; ++it )
	{
		ret.insert( (*it).second );
	}
}

//-----------------------------------------------
// CAIAliasTranslator getNPCAliasFromName
//-----------------------------------------------
inline bool CAIAliasTranslator::getNPCNameFromAlias(TAIAlias alias,std::string & ret) const
{
	std::hash_map< uint,std::string >::const_iterator it = _BotIdsToNames.find(alias);
	if ( it == _BotIdsToNames.end() )
		return false;
	ret = (*it).second;
	return true;
}

//-----------------------------------------------
// CAIAliasTranslator getGroupAliasesFromName
//-----------------------------------------------
inline void CAIAliasTranslator::getGroupAliasesFromName(const std::string & name, std::vector< TAIAlias >& aliases) const
{
	std::string lwr = NLMISC::strlwr(name);
	std::hash_multimap< std::string, TAIAlias>::const_iterator it = _AIGroupNamesToIds.find(lwr);
	while ( it != _AIGroupNamesToIds.end() && (*it).first == lwr )
	{
		aliases.push_back( (*it).second );
		++it;
	}
}

//-----------------------------------------------
// CAIAliasTranslator getInstance
//-----------------------------------------------
inline TAIAlias CAIAliasTranslator::getMissionUniqueIdFromName(const std::string & missionName) const
{
	std::string lwr = NLMISC::strlwr(missionName);
	std::hash_map< std::string, TAIAlias>::const_iterator it = _MissionNamesToIds.find(lwr);
	if ( it == _MissionNamesToIds.end() )
		return Invalid;
	return (*it).second;
}

inline const std::string &CAIAliasTranslator::getMissionNameFromUniqueId(TAIAlias alias) const
{
	static const std::string emptyString;

	std::hash_map< std::string, TAIAlias>::const_iterator first(_MissionNamesToIds.begin()), last(_MissionNamesToIds.end());
	for (; first != last; ++first)
	{
		if (first->second == alias)
			return first->first;
	}
	return emptyString;
}


//-----------------------------------------------
// CAIAliasTranslator getInstance
//-----------------------------------------------
inline CAIAliasTranslator* CAIAliasTranslator::getInstance()
{
	return _Instance;
}// CAIAliasTranslator getInstance

//-----------------------------------------------
// CAIAliasTranslator updateAssociation
//-----------------------------------------------
inline void CAIAliasTranslator::updateAssociation(TAIAlias aiid, const NLMISC::CEntityId& entityId)
{
	if ( entityId == NLMISC::CEntityId::Unknown )
	{
		nlwarning("Invalid entity %s (alias = %u)",entityId.toString().c_str(),aiid);
		return;
	}
	if ( aiid == Invalid )
	{
		// Doub: No warning because Invalid aliases (0) are allowed (e.g. dynamic fauna)
		//nlwarning("Invalid alias %u for entity %s",aiid, entityId.toString().c_str());
		return;
	}

	_HashTableAiId.insert( std::make_pair( (uint)aiid,entityId ) );
	_HashTableEntityId.insert( std::make_pair( entityId,aiid ) );
	
}// CAIAliasTranslator updateAssociation

//-----------------------------------------------
// CAIAliasTranslator removeAssociation
//-----------------------------------------------
inline void CAIAliasTranslator::removeAssociation(NLMISC::CEntityId& entityId)
{
	if ( entityId.getType() != RYZOMID::npc )
		return;
	std::hash_map< NLMISC::CEntityId, TAIAlias, NLMISC::CEidHash >::iterator itEid = _HashTableEntityId.find(entityId);
	if ( itEid == _HashTableEntityId.end() )
	{
		// No warning because not always inserted, see updateAssociation() (+ other reason it's already commented out?)
		//nlwarning("<CAIAliasTranslator removeAssociation> alias not found for %s",entityId.toString().c_str());
		return;
	}
	uint alias = (*itEid).second;
	if( _HashTableAiId.erase( alias ) == 0 )
	{
		nlwarning("<CAIAliasTranslator removeAssociation> alias %u has no entityId. DUPLICATED ALIAS?",alias);
	}
	_HashTableEntityId.erase(itEid);
}// CAIAliasTranslator removeAssociation

//-----------------------------------------------
// CAIAliasTranslator getEntityId
//-----------------------------------------------
inline const NLMISC::CEntityId& CAIAliasTranslator::getEntityId(TAIAlias aiid) const
{
	std::hash_map< uint, NLMISC::CEntityId >::const_iterator it = _HashTableAiId.find(aiid);
	if(  it != _HashTableAiId.end() )
		return (*it).second;
#ifndef FINAL_VERSION
	nlerror( "Illegal call to getEntityId on entity with no alias" ); // see 
#endif
	return NLMISC::CEntityId::Unknown;
}// CAIAliasTranslator getEntityId




#endif // RY_AI_ALIAS_TRANSLATOR_H

/* End of ai_alias_translator.h */
