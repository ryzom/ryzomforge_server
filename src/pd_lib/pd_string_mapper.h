/** \file pd_string_mapper.h
 * <File description>
 *
 * $Id: pd_string_mapper.h,v 1.1 2004/06/23 14:22:57 legros Exp $
 */

#ifndef NL_PD_STRING_MAPPER_H
#define NL_PD_STRING_MAPPER_H

#include <nel/misc/types_nl.h>
#include <nel/misc/stream.h>
#include <map>
#include <string>
#include <vector>

/**
 * A Class that maps a string to an uint32
 * \author Benjamin Legros
 * \author Nevrax France
 * \date 2003
 */
class CPDStringMapper
{
public:

	/// Unknown String Id
	enum
	{
		UnknownString = 0xfffffff
	};

	/// Constructor
	CPDStringMapper();


	/// Get String from Id
	const std::string&	getString(uint32 id) const;

	/// Get Id from String
	uint32				getId(const std::string& str) const;

	/// Set Mapping
	void				setMapping(const std::string& str, uint32 id);


	/// Serial Mapper
	void				serial(NLMISC::IStream& f);

	/// Rebuild Id Mapping
	void				buildIdMap();


private:

	/// Mapping of string to id
	typedef std::map<std::string, uint32>			TStringMap;

	/// Mapping of id to string
	typedef std::map<uint32, TStringMap::iterator>	TIdMap;

	/// String Mapping
	TStringMap										_StringMap;

	/// Id Mapping
	TIdMap											_IdMap;

	/// Unknown String
	static std::string								_UnknownString;

};


/*
 * -- Inlines
 */


/*
 * Get String from Id
 */
inline const std::string&	CPDStringMapper::getString(uint32 id) const
{
	TIdMap::const_iterator	it = _IdMap.find(id);

	if (it == _IdMap.end())
	{
		return _UnknownString;
	}

	TStringMap::iterator	its = (*it).second;
	return (*its).first;
}

/*
 * Get Id from String
 */
inline uint32				CPDStringMapper::getId(const std::string& str) const
{
	std::string					lowMapStr = NLMISC::toLower(str);
	TStringMap::const_iterator	it = _StringMap.find(lowMapStr);

	return (it == _StringMap.end()) ? UnknownString : (*it).second;
}


#endif // NL_PD_STRING_MAPPER_H

/* End of pd_string_mapper.h */
