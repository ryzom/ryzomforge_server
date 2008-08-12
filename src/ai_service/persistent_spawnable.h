/** \file Persistent_Spawnable.h
 *
 * $Id: persistent_spawnable.h,v 1.11 2004/09/07 19:17:28 boucher Exp $
 */



#ifndef _PERSISTENT_SPAWNABLE_
#define	_PERSISTENT_SPAWNABLE_

//	SpawnObject
template <class T>
class CSpawnable :
	public	NLMISC::CDbgRefCount< CSpawnable<T> >,
	public NLMISC::CRefCount
{
public:
	CSpawnable(T&	owner)	:	_Owner(owner)
	{
	}
	virtual	~CSpawnable()
	{
	}
	
	inline	T&	getPersistent	()	const
	{
		return	_Owner;
	}
	
private:
	T&	_Owner;
};

//	SpawnObject
template	<class T>
class	CPersistent
{
public:
	CPersistent	(	)
	{
		_Spawnable	=	NULL;
	}
	virtual ~CPersistent	(	)
	{
		_Spawnable	=	NULL;
	}
	
	bool	isSpawned	()	const
	{
		return	!_Spawnable.isNull();
	}
	void	setSpawn	(const	NLMISC::CSmartPtr<T>	&spawnable)
	{
		_Spawnable=spawnable;
#if !FINAL_VERSION
	nlassert((!spawnable) || (static_cast<CPersistent<T>*>(&spawnable->getPersistent())==static_cast<CPersistent<T>*>(this)));
#endif	
	}
	
	inline	T	*getSpawnObj()	const	//	you must overload this access to cast the objet with a custom more proper type. ( you know what i mean ? )
	{
		return	_Spawnable;
	}
	
protected:
	
//	virtual	bool	spawn	()	=	0;
//	virtual	void	despawn	()	=	0;
	
private:
	NLMISC::CSmartPtr<T>	_Spawnable;
};

#endif
