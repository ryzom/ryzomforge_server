/** \file ags_test.h
 * <File description>
 *
 * $Id: ags_test.h,v 1.4 2004/03/01 19:18:37 lecroart Exp $
 */




#ifndef GD_AGS_TEST_H
#define GD_AGS_TEST_H

// Nel Misc
#include "nel/misc/types_nl.h"

// Nel Net
#include "nel/net/service.h"

// Game share
#include "game_share/tick_event_handler.h"


// Callback called at service connexion
void cbServiceUp( const std::string& serviceName, uint16 serviceId, void * );

// Callback called at service down
void cbServiceDown( const std::string& serviceName, uint16 serviceId, void * );

// "Callbacks" for Tick service
void cbSync();


/**
 * <Class description>
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2001
 */
class CAgsTest : public NLNET::IService
{
public:
	// Initialisation of service
	void init (void);

	// Update net processing 
	bool update (void);

	// Update service processing
	static void serviceUpdate(void);

	// Release the service
	void release (void);
};

#endif // GD_AGS_TEST_H
/* End of ags_test.h */
