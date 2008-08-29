/** \file light_ig_loader.h
 * <File description>
 *
 * $Id: light_ig_loader.h,v 1.2 2004/03/01 19:21:53 lecroart Exp $
 */



#ifndef NL_LIGHT_IG_LOADER_H
#define NL_LIGHT_IG_LOADER_H

// misc
#include "nel/misc/types_nl.h"
#include <nel/misc/path.h>
#include <nel/misc/file.h>
#include <nel/misc/stream.h>
#include <nel/misc/matrix.h>
#include <nel/misc/vector.h>
#include <nel/misc/quat.h>

// STL
#include <string>
#include <vector>


/**
 * <Class description>
 * \author Benjamin Legros
 * \author Nevrax France
 * \date 2003
 */
class CLightIGLoader
{
public:

	/// Constructor
	CLightIGLoader();


	/// Load IG
	void				loadIG(const std::string &filename);


	/// Num instances
	uint				getNumInstance()
	{
		return _ShapeNames.size();
	}

	/// get shape name
	const std::string	&getShapeName(uint i)
	{
		return _ShapeNames[i];
	}

	/// get shape name
	const std::string	&getInstanceName(uint i)
	{
		return _InstanceNames[i];
	}

	/// get instance matrix
	void				getInstanceMatrix(uint i, NLMISC::CMatrix &matrix)
	{
		matrix.identity();	
		matrix.translate(_ShapePos[i]);
		matrix.rotate(_ShapeRots[i]);
		matrix.scale(_ShapeScales[i]);	
	}


protected:

	/// File
	NLMISC::CIFile		_File;



	/// Shape names array
	std::vector<std::string>		_ShapeNames;

	/// Shape names array
	std::vector<std::string>		_InstanceNames;

	/// Shape pos array
	std::vector<NLMISC::CVector>	_ShapePos;

	/// Shape Rots array
	std::vector<NLMISC::CQuat>		_ShapeRots;

	/// Shape Scales array
	std::vector<NLMISC::CVector>	_ShapeScales;

};


#endif // NL_LIGHT_IG_LOADER_H

/* End of light_ig_loader.h */
