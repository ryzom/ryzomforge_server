/*

  light-weight stl-based xml reader

*/


#include "nel/misc/types_nl.h"

#include <string>
#include <vector>
#include <map>


class CxmlNode
{
public:
	bool read(const std::string &filename);
	bool parseInput(char * &ptr);

	inline const std::string &txt() const		{ return _txt;  }
	inline const std::string &type() const		{ return _name; }
	inline const std::string &arg(const std::string &argName) const
	{
		static std::string emptyString;

		std::map<std::string,std::string>::const_iterator it;
		it=_args.find(argName);

		if (it!=_args.end())
			return (*it).second;
		else
			return emptyString;
	}

	inline uint childCount() const				{ return _children.size(); }
	inline CxmlNode *child(uint index) const	{ return _children[index]; }

private:
	std::string _txt;
	std::string _name;
	std::map<std::string,std::string> _args;
	std::vector<CxmlNode *> _children;
};

