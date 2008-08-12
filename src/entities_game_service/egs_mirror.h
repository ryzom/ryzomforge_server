/** \file egs_mirror.h
 * <File description>
 *
 * $Id: egs_mirror.h,v 1.18 2007/03/09 09:56:47 boucher Exp $
 */



#ifndef NL_EGS_MIRROR_H
#define NL_EGS_MIRROR_H

#include "game_share/mirror.h"
#include "game_share/ryzom_mirror_properties.h"


extern CMirror				Mirror;
extern CMirroredDataSet		*FeTempDataset;
extern CMirroredDataSet		*FameDataset;
extern TPropertyIndex		DSFirstPropertyAvailableImpulseBitSize;

extern uint32				MaxNbPlayers, MaxNbObjects, MaxNbNpcSpawnedByEGS, MaxNbForageSources, MaxNbToxicClouds;
extern uint32				MaxNbGuilds;


/*
 * Initialisation of the mirror
 */
void	initMirror( void (*cbUpdate)(), void (*cbSync)() );

/*
 * Initialisation of the properties in the mirror when the mirror service is up
 */
void	cbMirrorIsReadyForInit( CMirror *mirror );

/*
 * Callback called when mirror is ready for manage entity
 */
void	cbMirrorReadyForAddEntity( CMirror *mirror );

/*
 * Clear any target lists from previous uncleared sessions
 */
void	cleanOrphanTargetLists( NLNET::TServiceId serviceId );


#define TheDataset (*FeTempDataset)
#define TheFameDataset (*FameDataset)


void processMirrorUpdates();

/// get an entityId from a mirro data set row
inline NLMISC::CEntityId getEntityIdFromRow( const TDataSetRow & rowId )
{
	if ( TheDataset.isAccessible(rowId) )
		return TheDataset.getEntityId( rowId );
	return NLMISC::CEntityId::Unknown;
}

#endif // NL_EGS_MIRROR_H

/* End of egs_mirror.h */
