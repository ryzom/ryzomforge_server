/** \file mirror_equipment.cpp
 * 
 *
 * $Id: mirror_equipment.cpp,v 1.5 2004/03/01 19:21:53 lecroart Exp $
 */



#include "stdpch.h"
#include "mirror_equipment.h"

namespace NLMISC
{
	std::string toString( const SMirrorEquipment& equipment) 
	{ 
		return std::string("Sheet: ") + equipment.IdSheet.toString() + std::string(" Quality: ") + NLMISC::toString( equipment.Quality );
	}
};

/* End of mirror_equipment.cpp */


