/** \file r2_variables.cpp
 *
 * $Id: r2_variables.cpp,v 1.1 2005/10/12 13:08:32 miller Exp $
 */

#include "stdpch.h"
#include "r2_variables.h"

NLMISC::CVariable<bool> IsRingShard("variables","IsRingShard", "if 1 then use ring shard systems instead of normal shard systems", false, 0, true);
