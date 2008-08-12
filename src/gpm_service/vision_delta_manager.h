/** \file vision_delta_manager.h
 *
 * $Id: vision_delta_manager.h,v 1.3 2007/03/09 09:56:54 boucher Exp $
 */

#ifndef VISION_DELTA_MANAGER_H
#define VISION_DELTA_MANAGER_H

#include "nel/net/message.h"
#include "r2_share/r2_vision.h"


class CVisionDeltaManager: public R2_VISION::IVisionDeltaManager
{
public:
	// inherited interface
	void addVisionDelta(const CPlayerVisionDelta& visionDelta);

	// regular update call - used to dispatch messages and clear out buffers
	void update();

private:
	typedef std::map<NLNET::TServiceId, NLNET::CMessage> TFrontEnds;
	TFrontEnds _FrontEnds;
};

#endif
