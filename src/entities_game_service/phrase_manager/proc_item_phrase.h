/** \file proc_item_phrase.h
 * <File description>
 *
 * $Id: proc_item_phrase.h,v 1.10 2005/02/22 10:22:29 besson Exp $
 */



#ifndef RY_PROC_ITEM_PHRASE_H
#define RY_PROC_ITEM_PHRASE_H

#include "phrase_manager/s_phrase.h"


/**
 * class implemented proc item sabtrina phrases
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2003
 */
class CProcItemPhrase : public CSPhrase
{
public:
	
	virtual bool build( const TDataSetRow & actorRowId, const std::vector< const CStaticBrick* >& bricks, bool execution = true )
	{
		// nothing to do there
		return true;
	}
	virtual void setPrimaryTarget( const TDataSetRow &entityRowId )
	{
		nlerror("Invalid overload");
		return;
	}
	virtual bool evaluate()
	{
		return true;
	}
	virtual bool validate()
	{
		return true;
	}
	virtual bool update()
	{
		nlerror("Invalid overload");
		return false;
	}
	virtual void execute()
	{
		nlerror("Invalid overload");
		return;
	}
	virtual bool launch()
	{
		nlerror("Invalid overload");
		return false;
	}
	virtual void apply()
	{
		nlerror("Invalid overload");
		return;
	}
	virtual void end()
	{
		nlerror("Invalid overload");
		return;
	}
};


#endif // RY_PROC_ITEM_PHRASE_H

/* End of proc_item_phrase.h */
