/** \file vision_delta_manager.cpp
 *
 * $Id: vision_delta_manager.cpp,v 1.3 2007/03/09 09:56:54 boucher Exp $
 */

#include "nel/net/unified_network.h"
#include "vision_delta_manager.h"
#include "gpm_service.h"

const std::string FrontEndVisionMessageType = std::string("VISIONS_DELTA_2");


void CVisionDeltaManager::addVisionDelta(const CPlayerVisionDelta& visionDelta)
{
	// identify the correct front end for the player in question from the player id in the vision delta
	NLMISC::CEntityId eid= TheDataset.getEntityId(visionDelta.PlayerIndex);

	// serialise the result into the message
	NLNET::TServiceId dynamicId(eid.getDynamicId());
	if (_FrontEnds.find(dynamicId)==_FrontEnds.end())
	{
		// if the message didn't exist then intialise it
		_FrontEnds[dynamicId].setType(FrontEndVisionMessageType);
	}
	_FrontEnds[dynamicId].serial(const_cast<CPlayerVisionDelta&>(visionDelta));
}

void CVisionDeltaManager::update()
{
	TFrontEnds::iterator it;
	for (it=_FrontEnds.begin();it!=_FrontEnds.end();++it)
	{
		// extract the message and destination values from the map iterator
		const NLNET::TServiceId& destination	= it->first;
		NLNET::CMessage& msg	= it->second;

		// send the message
		sendMessageViaMirror( destination, msg );

		// clear out the message and prepare it for next time
		msg.clear();
		msg.setType(FrontEndVisionMessageType);
	}
}
