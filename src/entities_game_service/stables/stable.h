/** \file stable.h
 * <Manage stable for pet animals>
 *
 * $Id: stable.h,v 1.9 2006/01/10 17:38:58 boucher Exp $
 */



#ifndef RYZOM_STABLE_H
#define RYZOM_STABLE_H

#include "game_share/continent.h"
#include "game_share/respawn_point_type.h"
#include "game_share/entity_state.h"

/**
 * CStable
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2003
 * \Manage Stables for pet animals
 */
class CStable
{
	NL_INSTANCE_COUNTER_DECL(CStable);
public:

	struct TStableData
	{
		std::string StableName;
		CONTINENT::TContinent Continent;
		sint32 StableExitX;
		sint32 StableExitY;
		sint32 StableExitZ;
		float Theta;
	};

	typedef std::map< uint16, TStableData > TStableContainer;
	
	// initialize 
	static CStable* getInstance() 
	{
		NL_ALLOC_CONTEXT(ST_GI);
		if(_Instance == NULL)
		{
			_Instance = new CStable();
		}
		return _Instance;
	}
	
	/// constructor
	CStable(); 

	/// destructor
	virtual ~CStable();

	/// add a stable
	void addStable( const std::string& stableName, uint16 placeId, const std::string& continent, float x, float y, float z, float theta );

	/// return stable entry point coordinate
	bool getStableData( uint16 placeId, TStableData& stableData ) const;

	/// return true if name corresponding to a stable
	inline bool isStable( uint16 placeId ) const { return _Stables.find( placeId ) != _Stables.end(); }

private:
	// singleton instance
	static CStable * _Instance;
	
	// re-spawn name and datas
	TStableContainer _Stables;
};
#endif // RYZOM_STABLE_H

/* End of file stable.h */





















