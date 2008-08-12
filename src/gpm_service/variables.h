/** \file variables.h
 * <File description>
 *
 * $Id: variables.h,v 1.3 2006/01/10 17:38:59 boucher Exp $
 */



#ifndef NL_VARIABLES_H
#define NL_VARIABLES_H

#include "nel/misc/types_nl.h"
#include "nel/misc/variable.h"
#include <string>

/// \name Various service Info
//@{
/// Number of entities referenced on the GPMS
extern uint32		NumEntities;
/// Number of players referenced on the GPMS
extern uint32		NumPlayers;
/// Verbose mode
extern bool			Verbose;
//@}


/// \name Player control
//@{
/// Allow check player speed
extern bool			CheckPlayerSpeed;
//@}

#endif // NL_VARIABLES_H

/* End of variables.h */
