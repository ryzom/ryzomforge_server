/** \file projectile_stats.cpp
 *
 * $Id: projectile_stats.cpp,v 1.3 2006/01/10 17:38:55 boucher Exp $
 */

#include "stdpch.h"
#include "projectile_stats.h"


static NLMISC::TTime lastTime = 0;
static bool firstSample = true;
static uint numProjFired = 0;

const uint PROJ_STATS_REPORT_TIME = 60 * 1000;

void projStatsTime(NLMISC::TTime time)
{
	if (firstSample)
	{
		firstSample = false;
	}
	else
	{
		if (time - lastTime > PROJ_STATS_REPORT_TIME)
		{			
// The following removed for now by Sadge because it causes spam!
//			nlinfo("PROJECTILE_STATS : %d projectile fired in %.2f second -> %.2f projectile per second",
//				   (int) numProjFired, 
//				   (time - lastTime) / 1000.f,
//				   (1000.f * numProjFired) / (time - lastTime));
			lastTime = time;
			numProjFired = 0;
		}
	}
}


void projStatsIncrement()
{
	++ numProjFired;
}
