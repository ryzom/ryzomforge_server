/** \file pds_type.cpp
 * <File description>
 *
 * $Id: pds_type.cpp,v 1.7 2004/09/27 17:45:34 legros Exp $
 */

#include "../pd_lib/pds_common.h"

#include "pds_type.h"
#include "pds_database.h"

#include "../pd_lib/db_description_parser.h"

#include <nel/misc/debug.h>

using namespace std;
using namespace NLMISC;

/*
 * Constructor
 */
CType::CType()
{
	clear();
}

/**
 * Destructor
 */
CType::~CType()
{
	//PDS_DEBUG("delete()");
	clear();
}

/*
 * Clear
 */
void	CType::clear()
{
	_Init = false;
	_Name.clear();
	_Id = 0;
	_DataType = PDS_UnknownDataType;
	_ByteSize = 0;
	_EnumValueTable.clear();
	_ValueEnumTable.clear();
	_IndexSize = 0;
}


/*
 * Init
 */
bool	CType::init(CDatabase *database, const CTypeNode& type)
{
	_Parent = database;

	_Name = type.Name;
	_Id = type.Id;
	_ByteSize = type.ByteSize;

	uint	i;

	switch (type.Type)
	{
	case CTypeNode::TypeSimple:
		_DataType = type.DataType;
		break;

	case CTypeNode::TypeDimension:
		_DataType = PDS_dimension;
		_IndexSize = type.Dimension;
		break;

	case CTypeNode::TypeEnum:
		{
			_DataType = PDS_enum;
			if (_ByteSize != sizeof(TEnumValue))
				return false;

			TEnumValue	valuemin = 0xffffffff;
			TEnumValue	valuemax = 0x00000000;

			for (i=0; i<type.EnumValues.size(); ++i)
			{
				if (!addEnum(type.EnumValues[i].first, type.EnumValues[i].second))
					return false;

				if (valuemin > type.EnumValues[i].second)
					valuemin = type.EnumValues[i].second;

				if (valuemax < type.EnumValues[i].second)
					valuemax = type.EnumValues[i].second;
			}

			_IndexSize = valuemax-valuemin+1;

		}
		break;

	default:
		break;
	}

	// set parent logger
	setParentLogger(database);

	_Init = true;
	
	return true;
}

/*
 * Add enum value
 */
bool	CType::addEnum(const string &enumName, TEnumValue value)
{
	// check...
	if (!isEnum())
	{
		PDS_WARNING("addEnum(): type is not an enum");
		return false;
	}

	// check name doesn't exist yet
	TEnumValueTable::iterator	it = _EnumValueTable.find(enumName);
	if (it != _EnumValueTable.end())
	{
		PDS_WARNING("addEnum(): can't add enum '%s', name already exists", enumName.c_str());
		return false;
	}

	// insert it in both tables
	_EnumValueTable.insert(TEnumValueTable::value_type(enumName, value));

	if (_ValueEnumTable.size() <= value)
		_ValueEnumTable.resize(value+1, INVALID_ENUM_NAME);

	_ValueEnumTable[value] = enumName;

	return true;
}

/*
 * Get enum value from its name
 */
TEnumValue	CType::getIndexValue(const string &name, bool verbose) const
{
	// check...
	if (!isIndex())
	{
		PDS_WARNING("getIndexValue(): type is not an index");
		return false;
	}

	if (isEnum())
	{
		// check name is in enum
		TEnumValueTable::const_iterator	it = _EnumValueTable.find(name);
		if (it == _EnumValueTable.end())
		{
			if (verbose)
				PDS_WARNING("getValue(): '%s' not found in enum, INVALID_ENUM_VALUE returned", name.c_str());
			return INVALID_ENUM_VALUE;
		}

		return (*it).second;
	}
	else
	{
		return atoi(name.c_str());
	}
}

/*
 * Get enum name from its value
 */
string	CType::getIndexName(TEnumValue value, bool verbose) const
{
	// check...
	if (!isIndex())
	{
		PDS_WARNING("getIndexName(): type is not an index");
		return false;
	}

	if (isEnum())
	{
		// check value belongs to enum
		if (value >= _ValueEnumTable.size())
		{
			if (verbose)
				PDS_WARNING("getEnumName(): value '%d' not in range of enum, INVALID_ENUM_NAME returned", value);
			return INVALID_ENUM_NAME;
		}

		return _ValueEnumTable[value];
	}
	else
	{
		return toString(value);
	}
}

/*
 * Get Enum size
 */
TEnumValue	CType::getIndexSize() const
{
	// check...
	if (!isIndex())
	{
		PDS_WARNING("getIndexSize(): type is not an index");
		return 0;
	}

	// should be that
	return _IndexSize;
}







/*
 * Display type
 */
void	CType::display(NLMISC::CLog* log) const
{
	if (!initialised())
	{
		log->displayNL("** Type not initialised");
	}

	log->displayNL("Type %-3d %-32s | %-2d %-12s | %-2d | %s", _Id, _Name.c_str(), _DataType, getNameFromDataType(_DataType).c_str(), _ByteSize, (isEnum() ? "enum" : (isDimension() ? "dimension" : "not index")));
}


