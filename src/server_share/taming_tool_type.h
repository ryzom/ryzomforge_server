/** \file taming_tool_type.h
 *
 * $Id: taming_tool_type.h,v 1.3 2004/03/01 19:21:54 lecroart Exp $
 */




#ifndef RY_TAMING_TOOL_TYPE_H
#define RY_TAMING_TOOL_TYPE_H


namespace TAMING_TOOL_TYPE
{

	enum TTamingToolType
	{
		Cattleprod,
		Stick,
		Whip,

		Unknown,
		NUM_TAMING_TOOL_TYPE = Unknown,
	};

	/**
	  * get the right string from the given enum value
	  * \param jop the TTamingToolType value to convert
	  * \return the string associated to this enum number (Unknown if the enum number not exist)
	  */
	const std::string& toString( TTamingToolType type );

	/**
	  * get the right TTamingToolType from its string
	  * \param str the input string
	  * \return the TTamingToolType associated to this string (unknown if the string cannot be interpreted)
	  */
	TTamingToolType toToolType( const std::string& str );

} // TAMING_TOOL_TYPE

#endif // RY_TAMING_TOOL_TYPE_H //

