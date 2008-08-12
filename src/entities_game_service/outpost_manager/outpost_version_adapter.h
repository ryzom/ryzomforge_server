/* \file outpost_version_adapter.h
 * outpost version adapter
 *
 * $Id: outpost_version_adapter.h,v 1.1 2005/09/27 09:58:27 besson Exp $
 */


#ifndef OUTPOST_VERSION_ADAPTER_H
#define OUTPOST_VERSION_ADAPTER_H

class COutpost;

/**
 * Singleton class used to adapt different version of COutpost
 * \author Sébastien 'kxu' Guignot
 * \author Nevrax France
 * \date 2005
 */
class COutpostVersionAdapter
{	
	NL_INSTANCE_COUNTER_DECL(COutpostVersionAdapter);
public:

	/// get singleton instance
	static inline COutpostVersionAdapter * getInstance()
	{
		NL_ALLOC_CONTEXT(OVAGI);
		if (_Instance == NULL)
			_Instance = new COutpostVersionAdapter();

		return _Instance;
	}

	/// get current version number
	uint32 currentVersionNumber() const;

	/// adapt outpost from given version
	void adaptOutpostFromVersion(COutpost & outpost, uint32 version) const;

private:
	/// adapter methods
	//void adaptToVersion1(COutpost & outpost) const;

private:
	/// singleton instance
	static COutpostVersionAdapter * _Instance;
};

#endif // OUTPOST_VERSION_ADAPTER_H
