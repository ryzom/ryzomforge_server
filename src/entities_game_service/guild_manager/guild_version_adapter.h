/** \file guild_version_adapter.h
 * <File description>
 *
 * $Id: guild_version_adapter.h,v 1.6 2006/05/31 12:13:20 boucher Exp $
 */

#ifndef RY_GUILD_VERSION_ADAPTER_H
#define RY_GUILD_VERSION_ADAPTER_H

class CGuild;
/**
 * class used to adapt previous guild versions to new ones
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CGuildVersionAdapter
{	

public:
	/// getInstance
	static inline CGuildVersionAdapter *getInstance()
	{
		if (_Instance == NULL)
			_Instance = new CGuildVersionAdapter();
		
		return _Instance;
	}
	/// get current version number
	uint32 currentVersionNumber() const;

	/// adapt character from given version
	void adaptGuildFromVersion( CGuild &guild ) const;
	
private:
	/// adapter methods
	void adaptToVersion1(CGuild &guild) const;
	void adaptToVersion2(CGuild &guild) const;
	void adaptToVersion3(CGuild &guild) const;
	void adaptToVersion4(CGuild &guild) const;

private:
	CGuildVersionAdapter(){};
	/// unique instance
	static CGuildVersionAdapter*			_Instance;
};

#endif // RY_GUILD_VERSION_ADAPTER_H

/* End of guild_version_adapter.h */
