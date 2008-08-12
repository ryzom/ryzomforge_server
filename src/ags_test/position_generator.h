/** \file position_generator.h
 *
 * $Id: position_generator.h,v 1.6 2004/10/07 15:45:08 boucher Exp $
 */




#ifndef GD_POSITION_GENERATOR_H
#define GD_POSITION_GENERATOR_H


#include <string>
#include "nel/misc/types_nl.h"
#include "nel/ligo/primitive.h"


namespace AGS_TEST
{

class CPositionGenerator
{
public:
	static void setPositionInMM(int x, int y);			// x and y are in milimeters
	static void setPosition(int x, int y);				// x and y are in meters
	static void setPosition(std::string spawnName);		// name of a spawn point or spawn zone
	static void setPattern(const std::string &pattern);
	static void setSpacing(int spacing);

	static void addSpawnPoint(const NLLIGO::CPrimPoint &point)	{ _spawnPoints[point.getName()]=point; }
	static void addSpawnZone(const NLLIGO::CPrimZone &zone);

	static void init();
	static void next(int &x, int &y);

	static std::string getSpawnName();

private:
	class CSpawnZone
	{
	public:
		uint Next;
		std::vector<NLMISC::CVector> Points;

		CSpawnZone(): Next(0) {}
		const NLMISC::CVector& getNext()
		{
			if (Next>=Points.size()) Next=0;
			return Points[Next++];
		}
	};

private:
	static int _x, _y;
	static int _dx, _dy;
	static int _spacing;
	static std::string _pattern;
	static std::string _spawnZoneName;

	typedef std::map<std::string, CSpawnZone> TSpawnZoneMap;
	typedef std::map<std::string, NLLIGO::CPrimPoint> TSpawnPointMap;

	static TSpawnZoneMap	_spawnZones;
	static TSpawnPointMap	_spawnPoints;

	// for grid
	static int _linelen, _leftonline;
};


} // end of namespace AGS_TEST

#endif // GD_POSITION_GENERATOR_H
