/** \file fe_types.h
 * Front-end tyês
 * $Id: fe_types.h,v 1.14 2004/03/01 19:21:52 lecroart Exp $
 */



#ifndef NL_FE_TYPES_H
#define NL_FE_TYPES_H

#include "nel/misc/types_nl.h"
#include "nel/misc/bit_mem_stream.h"
#include "nel/net/inet_address.h"
#include "game_share/entity_types.h"
#include "game_share/mirror.h"
#include <vector>
#include <hash_map>


typedef NLMISC::CBitMemStream TOutBox;

#undef SIMUL_CLIENTS
//#define SIMUL_CLIENTS


typedef uint16 TClientId; // range about 1..1000
extern uint MaxNbClients; // config file controlled
const uint MAX_NB_CLIENTS = 1000; // constant for raw arrays
const uint MAX_SEEN_ENTITIES_PER_CLIENT = 255; // per client

const uint16 INVALID_CLIENT = 0xFFFF;



class CClientHost;

/// Type of client container indexed by TClientId
typedef std::vector<CClientHost*> TClientIdCont;
#define GETCLIENTI(it) (*it)


/// Retrieving client id by entity id (initialized once and for all)
typedef std::vector<TClientId> TEntityToClient;


// Type of indexed in property receiver (old)
//typedef uint32 TEntityIndex;
//const TEntityIndex INVALID_ENTITY_INDEX = 0xFFFFFFFF;

/// Entity index type
typedef TDataSetRow TEntityIndex;



/// User account identifier
typedef uint32 TUid;



/**
 * CInetAddress hash function
 */
struct TInetAddressHash : public std::hash<NLNET::CInetAddress>
{
public:

	/// Hash function
	size_t operator() ( const NLNET::CInetAddress& x ) const
	{
		//return x.port();
		return x.internalIPAddress();
	}

};

/// Type of client map by address
typedef std::hash_map<NLNET::CInetAddress,CClientHost*,TInetAddressHash> THostMap;
#define GETCLIENTA(it) (*it).second

/// TEMP! fe/client time/tick types
//typedef sint64		TGameTime;
//typedef uint32		TGameTicks;

#endif // NL_FE_TYPES_H

/* End of fe_types.h */
