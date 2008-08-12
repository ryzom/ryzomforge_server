/** \file uid_impulsions.h
 * 
 *
 * $Id: uid_impulsions.h,v 1.2 2004/03/01 19:21:52 lecroart Exp $
 */



#ifndef UID_IMPULSIONS_H
#define UID_IMPULSIONS_H


// misc
#include "nel/misc/types_nl.h"

/*
 * Message received from not yet identified clients (uid, for User Id)
 */
typedef void	(*TImpulsionUidCb)(uint32 uid, NLMISC::CBitMemStream &bms, NLMISC::TGameCycle gameCycle);


void	initImpulsionUid();
void	routeImpulsionUidFromClient( NLMISC::CBitMemStream& bms, const uint32& userId, const NLMISC::TGameCycle& gamecycle );


#endif // UID_IMPULSIONS_H

/* End of uid_impulsions.h */
