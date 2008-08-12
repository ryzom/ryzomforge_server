/** \file position_flag_manager.h
 *
 * $Id: position_flag_manager.h,v 1.4 2006/05/31 12:15:01 boucher Exp $
 */



#ifndef RY_POSITION_FLAG_MANAGER_H
#define RY_POSITION_FLAG_MANAGER_H

#include "nel/misc/types_nl.h"
#include "nel/misc/singleton.h"

class CFlagPosition
{
public:
	CFlagPosition() {}
	CFlagPosition(sint32 x, sint32 y, sint32 z) : X(x), Y(y), Z(z) {}

public:
	/// in meters
	sint32 X;
	sint32 Y;
	sint32 Z;
};

class CPositionFlagManager : public NLMISC::CSingleton<CPositionFlagManager>
{
public:
	/// set a flag with the given position
	void setFlag(const std::string & flagName, const CFlagPosition & flagPos);

	/// remove a flag
	void removeFlag(const std::string & flagName);

	/// get a flag position, return NULL if the flag does not exist
	const CFlagPosition * getFlagPosition(const std::string & flagName) const;

	/// return true if the flag exists
	bool flagExists(const std::string & flagName) const;

	/// serial flags and their positions
	void serial(NLMISC::IStream & f) throw(NLMISC::EStream);

	/// save flags to the given file
	void saveToFile(const std::string & fileName);

	/// load flags from the given file
	void loadFromFile(const std::string & fileName);

	/** send the list of flags in a given radius to a character
	 *  \param eid id of the character
	 *  \param shortFormat true if you only want to list flag names
	 *  \param radius in meters, zero means no distance limit
	 */
	void sendFlagsList(const NLMISC::CEntityId & eid, bool shortFormat = false, uint32 radius = 0) const;

private:
	typedef std::map<std::string, CFlagPosition> TFlagPositionMap;

private:

	/// flag positions
	TFlagPositionMap _FlagPositions;
};


#endif // RY_POSITION_FLAG_MANAGER_H

/* End of position_flag_manager.h */
