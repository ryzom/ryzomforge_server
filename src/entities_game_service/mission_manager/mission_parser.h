/** \file mission_parser.h
 * <File description>
 *
 * $Id: mission_parser.h,v 1.22 2005/07/12 09:46:50 berenguier Exp $
 */



#ifndef RY_MISSION_PARSER_H
#define RY_MISSION_PARSER_H

#include "game_share/string_manager_sender.h"
#include "mission_manager/ai_alias_translator.h"
#include "game_share/string_manager_sender.h"
#include "mission_item.h"

class CMissionTemplate;

/// global parsing data
struct CMissionGlobalParsingData
{
	/// mission name map
	std::map<TAIAlias,std::string>				NameMap;
	/// copy missions encountered
	std::vector< std::pair<TAIAlias,TAIAlias> >	CopyMissions;
	/// container linking a mission to its parent
	std::vector< std::pair<TAIAlias,TAIAlias> >	ParentMissions;
};

/// specific mission parsing data
struct CMissionSpecificParsingData
{
	std::vector< std::pair< std::string, STRING_MANAGER::TParamType> > ChatParams;
	std::vector< std::pair<std::string,CMissionItem> >				   Items;
	std::vector< std::string >										   Jumps;
	CMissionTemplate*												   Template;
	std::map< std::string, uint >									   Integers;
	std::string														   Name;
};

/**
 * static class containing helper used  to parse missions
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2003
 */
class CMissionParser
{
public:
	
	/// solve chat parameter types. Useful to determine the nature of chat parameters that had an unknown type when we encoutered them
	/// Each entry in txtParams contains a STRING_MANAGER parameter where only the Identifier field is filled. This method looks up for this identifier in paramTypes.
	/// If the identifer is found, the entry in textParam is modified by clearring the identifier field, and filling the param type and approprita field
	///\return true if all param have been solved, otherwise, it returns false and warns
	static bool solveTextsParams(uint32 lineNum, TVectorParamCheck & txtParams, CMissionSpecificParsingData & missionData  );
	/// remove all starting and ending blanks in a string
	static void removeBlanks( std::string & str);
	/// remove all starting and ending blanks in a string
	static  std::string getNoBlankString( const std::string & str );
	/// parse a mission text script (  <phrase_id>*[;<param>]
	static bool parseParamText(uint32 line, const std::string & script,std::string & textId, TVectorParamCheck & textParams );
	/// parse a string list
	static bool parseStringList(uint32 line, const std::string & separator, const std::vector< std::string > & preparsedParams, std::vector< std::string > & ret );
	/// parse a bot name
	static bool parseBotName(const std::string & name,TAIAlias & aliasRet,CMissionSpecificParsingData & data);
		

	/// solve bot names ( convert alias in Eid in string manager parameters )
	inline static void solveBotNames( TVectorParamCheck & params,const NLMISC::CEntityId& giver )
	{
		for ( uint i = 0; i< params.size(); i++)
		{
			if ( params[i].Type == STRING_MANAGER::bot && params[i].getEId() == NLMISC::CEntityId::Unknown )
			{
				if ( params[i].Identifier == "giver" )
				{
					params[i].setEIdAIAlias(giver, CAIAliasTranslator::getInstance()->getAIAlias( giver ));
				}
				else
				{
					params[i].setEIdAIAlias(CAIAliasTranslator::getInstance()->getEntityId( params[i].Int ), params[i].Int);
				}
			}
		}
	}
	static void solvePlayerName( TVectorParamCheck & params , const TDataSetRow & playerRow );

	static void solveEntitiesNames( TVectorParamCheck & params , const TDataSetRow & playerRow,const NLMISC::CEntityId& giver );

	/// same as Nel splitString but each char in the separator string is considered as a separator ( in the strtok way )
	static void tokenizeString(const std::string &str, const std::string &separators, std::vector<std::string> &retList);

	/// add the price of an item to the amouut
	static bool addItemPrice( uint32 line, const std::vector<std::string> & args, uint & amount );

private:
	/// fill a string manager param from its description, used in solveTextsParams
	static bool fillTextParam( STRING_MANAGER::TParam & param ,const std::string & value, STRING_MANAGER::TParamType type );
	

};


#endif // RY_MISSION_PARSER_H

/* End of mission_parser.h */






















