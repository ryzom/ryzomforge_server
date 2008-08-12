/** \file ai_vision.cpp
 *
 * $Id: ai_vision.cpp,v 1.17 2005/05/16 10:00:07 distrib Exp $
 */




#include "stdpch.h"

//----------------------------------------------------------------------
// ctor
//----------------------------------------------------------------------
/*
CAIVision::CAIVision()
{
};

CAIVision::~CAIVision()	
{
};
*/
//----------------------------------------------------------------------
// placing or moving vision entity in world or removing from world
//----------------------------------------------------------------------
/*
template <class VectorClass> 
void CAIVision::updateBots(const VectorClass &xy,uint32 botRadiusInMeters)
{
	CAIEntityMatrix::CCellTblIteratorLinear *tbl;
	CAIEntityMatrix::CEntityIteratorRandom it;

	_bots.clear();
	tbl==CAIS::bestMatrixIteratorLinearTbl(botRadiusInMeters);
	for (it=CAIS::botMatrix().beginEntities(tbl,x,y);!it.end();++it)
		_bots.push_back(&*it);
}

template <class VectorClass> 
void CAIVision::updatePlayers(const VectorClass &xy,uint32 playerRaadiusInMeters)
{
	CAIEntityMatrix::CCellTblIteratorLinear *tbl;
	CAIEntityMatrix::CEntityIteratorRandom it;

	_players.clear();
	tbl==CAIS::bestMatrixIteratorLinearTbl(playerRadiusInMeters);
	for (it=CAIS::botMatrix().beginEntities(tbl,xy.x(),xy.y());!it.end();++it)
		_players.push_back(&*it);
}
*/
//----------------------------------------------------------------------
// singleton entry point for dealing with vision deltas from the GPMS
//----------------------------------------------------------------------
/*
void CAIVision::applyVisionDelta(  NLMISC::CEntityId eid, const CPlayerVisionDelta &delta )
{
	uint idx=(uint)eid.getShortId();

	if (idx>=_visions.size() || eid.getRawId()!=NLMISC::CEntityId(RYZOMID::aiVision,idx))
	{
		nlwarning("Unable to treat vision delta for unrecognised entity id: %s",eid.toString().c_str());
		return;
	}

	if (_visions[idx]==NULL)
	{
		nlwarning("Ignoring vision delta for deleted entity id: %s",eid.toString().c_str());
		return;
	}

	_visions[idx]->applyVisionDelta( delta );
}
*/
//----------------------------------------------------------------------
// dealing with individual vision deltas from the GPMS
//----------------------------------------------------------------------
/*
void CAIVision::applyVisionDelta( const CPlayerVisionDelta &delta )
{
	uint i;
	//nlinfo("Applying vision delta: in: %d  out: %d  replace: %d",delta.EntitiesIn.size(),delta.EntitiesOut.size(),delta.EntitiesReplace.size());

	for (i=0;i<delta.EntitiesOut.size();++i)
	{
		// remove entities no longer in vision
		visionBuffer[delta.EntitiesOut[i].Slot]=CAIEntityId();
	}

	for (i=0;i<delta.EntitiesIn.size();++i)
	{
		// add new entities to vision
		visionBuffer[delta.EntitiesIn[i].Slot]=CAIEntityId(delta.EntitiesIn[i].Id);

		// make sure that the player structures exist in the player map
		// this code to be replaced when propper player appearance/ disappeara	nce treated
		if (visionBuffer[delta.EntitiesIn[i].Slot].isPlr())
			CAIS::getPlayer(delta.EntitiesIn[i].Id);
	}

	for (i=0;i<delta.EntitiesReplace.size();++i)
	{
		// add more new entities to vision
		visionBuffer[delta.EntitiesReplace[i].Slot]=CAIEntityId(delta.EntitiesReplace[i].Id);

		// make sure that the player structures exist in the player map
		// this code to be replaced when propper player appearance/ disappeara	nce treated
		if (visionBuffer[delta.EntitiesReplace[i].Slot].isPlr())
			CAIS::getPlayer(delta.EntitiesReplace[i].Id);
	}
}
*/
//----------------------------------------------------------------------
// Method used for off-line use of AIS
/*
void CAIVision::addEntityId(CAIEntityId entityId)
{
	iterator retval = &visionBuffer[0];
	uint ii = 0;
	while (*retval != CAIEntityId() && *retval !=CAIEntityId(0) && *retval !=entityId)
	{
		if (ii >= 256)
			return;
		ii++;
		retval = &visionBuffer[ii];
	}
	visionBuffer[ii] = entityId;
}

void CAIVision::removeEntityId(CAIEntityId entityId)
{
	iterator retval = &visionBuffer[0];
	uint ii = 0;
	while (*retval != entityId)
	{
		if (ii >= 256)
			return;
		ii++;
		retval = &visionBuffer[ii];
	}
	visionBuffer[ii] = CAIEntityId();
}
*/
