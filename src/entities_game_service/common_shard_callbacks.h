/** \file common_shard_callbacks.h
 * <File description>
 *
 * $Id: common_shard_callbacks.h,v 1.3 2004/12/08 13:26:42 besson Exp $
 */



#ifndef RY_COMMON_SHARD_CALLBACKS_H
#define RY_COMMON_SHARD_CALLBACKS_H



/**
 * class used to manage net callbacks that are not linked to a particular game manager
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CCommonShardCallbacks
{
public:

	static void init();
	static void release();
};


#endif // RY_COMMON_SHARD_CALLBACKS_H

/* End of common_shard_callbacks.h */
