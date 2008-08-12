/** \file pd_string_mapper.cpp
 * <File description>
 *
 * $Id: pd_string_mapper.cpp,v 1.1 2004/06/23 14:22:57 legros Exp $
 */

#include "pd_string_mapper.h"

/*
 * Unknown String
 */
std::string		CPDStringMapper::_UnknownString = "Unknown";


/*
 * Constructor
 */
CPDStringMapper::CPDStringMapper()
{
}


/*
 * Set Mapping
 */
void	CPDStringMapper::setMapping(const std::string& str, uint32 id)
{
	std::string				lowMapStr = NLMISC::toLower(str);
	TStringMap::iterator	its;

	TIdMap::iterator		iti = _IdMap.find(id);
	if (iti != _IdMap.end())
	{
		its = (*iti).second;;
		if ((*its).first != lowMapStr || (*its).second != id)
		{
			nlwarning("CPDStringMapper::setMapping(): failed to map '%s' to '%d', id is already mapped to a different string", str.c_str(), id);
			return;
		}

		return;
	}

	its = _StringMap.find(lowMapStr);

	if (its != _StringMap.end())
	{
		if ((*its).second != id)
		{
			nlwarning("CPDStringMapper::setMapping(): failed to map '%s' to '%d', string is already mapped to a different id", str.c_str(), id);
			return;
		}

		return;
	}

	its = _StringMap.insert(std::make_pair<std::string, uint32>(lowMapStr, id)).first;
	_IdMap[id] = its;
}

/*
 * Serial Mapper
 */
void	CPDStringMapper::serial(NLMISC::IStream& f)
{
	f.serialCheck((uint32)'PDSM');

	uint	version = f.serialVersion(0);

	f.serialCont(_StringMap);

	if (f.isReading())
	{
		buildIdMap();
	}
}

/*
 * Rebuild Id Mapping
 */
void	CPDStringMapper::buildIdMap()
{
	_IdMap.clear();

	TStringMap::iterator	it;
	for (it=_StringMap.begin(); it!=_StringMap.end(); ++it)
	{
		const std::string&	str = (*it).first;
		uint32				id = (*it).second;

		_IdMap[id] = it;
	}
}
