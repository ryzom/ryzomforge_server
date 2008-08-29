/** \file primitive_cfg.h
 * Utility to load and access primitives configuration
 *
 * $Id: primitive_cfg.h,v 1.6 2004/04/16 16:19:13 ledorze Exp $
 */



#ifndef PRIMITIVE_CFG_H
#define PRIMITIVE_CFG_H

#include "nel/misc/types_nl.h"

class CPrimitiveCfg
{
//	static std::vector<std::string>			_AllPrimitives;
	static std::vector<std::string>			_MapNames;
	static std::map<std::string, std::vector<std::string> >	_Maps;
	static std::map<std::string, std::vector<std::string> >	_ContinentFiles;
public:

	static	void readPrimitiveCfg(bool forceReload = false);

	static const std::vector<std::string> &getMapNames()
	{
		return _MapNames;
	}

	static const std::vector<std::string> &getMap(const std::string mapName)
	{
		static std::vector<std::string> emptyVector;
		std::map<std::string, std::vector<std::string> >::iterator it(_Maps.find(mapName));

		if (it == _Maps.end())
			return emptyVector;
		else
			return it->second;
	}

	static	std::string getContinentNameOf(const std::string &fileName);

	static	void addPrimitive(std::vector<std::string>	&list, const	std::string &str);

//	static const std::vector<std::string> &getAllPrimitives()
//	{
//		return _AllPrimitives;
//	}

};


#endif //PRIMITIVE_CFG_H
