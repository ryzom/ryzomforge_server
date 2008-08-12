/** \file owners.h
 *
 * $Id: owners.h,v 1.14 2005/03/08 10:20:11 vuarand Exp $
 */



#ifndef _OWNERS_
#define _OWNERS_

#include "ai_entity_physical.h"
#include "ai_entity_physical_inline.h"
#include "ai_instance.h"
#include "ai_grp_pet.h"

//	used to allow entity to handle pets.
class	CPetOwner
{
public:
	explicit	CPetOwner	()	:	_petGroup(NULL)
	{
	}
	virtual ~CPetOwner	();

	virtual	CAIEntityPhysical	&getPhysical()=0;
	inline	CGrpPet	*getPetGroup()
	{
		return	_petGroup;
	}
	inline	void	setPetGroup(CGrpPet	*petGroup)
	{
		nlassert(!getPetGroup());
		_petGroup=petGroup;
	}

	inline	void	removePetGroup()
	{
		_petGroup=NULL;
	}

private:
	NLMISC::CSmartPtr<CGrpPet>	_petGroup;
};

#endif
