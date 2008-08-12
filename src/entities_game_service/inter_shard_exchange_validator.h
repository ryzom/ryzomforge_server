/** \file inter_shard_exchange_validator.h
 *
 * $Id: inter_shard_exchange_validator.h,v 1.2 2006/10/31 16:09:05 blanchard Exp $
 */

#ifndef INTER_SHARD_EXCHANGE_VALIDATOR_H
#define INTER_SHARD_EXCHANGE_VALIDATOR_H


//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

// NeL MISC
#include "nel/misc/singleton.h"


//-------------------------------------------------------------------------------------------------
// forward declarations
//-------------------------------------------------------------------------------------------------

class CGameItemPtr;


//-------------------------------------------------------------------------------------------------
// singleton class IInterShardExchangeValidator
//-------------------------------------------------------------------------------------------------

class IInterShardExchangeValidator
{
public:
	// public types
	typedef uint32 TShardId;
	typedef uint32 TLevelCap;

	/// validate an item for exchange
	virtual bool isExchangeAllowed(const CGameItemPtr& theItem, TShardId shardId0, TShardId shardId1) const =0;

	/// validate money for exchange
	virtual bool isMoneyExchangeAllowed(TShardId shardId0, TShardId shardId1) const =0;

	/// Singleton accessor
	static IInterShardExchangeValidator* getInstance();
};


#endif // INTER_SHARD_EXCHANGE_VALIDATOR_H
