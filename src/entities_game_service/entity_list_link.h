/** \file entity_list_link.h
 *
 * $Id: entity_list_link.h,v 1.3 2004/08/02 10:20:01 distrib Exp $
 */




#ifndef RY_ENTITY_LIST_LINK_H
#define RY_ENTITY_LIST_LINK_H



/**
 * template representing a circular linked list node .
 * designed to be used for entities but work with any class
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2003
 */
template	<class	T>
class	CEntityListLink
{
public:
	
	/// ctor
	inline CEntityListLink()	:	_entity(NULL)
	{
		_next=this;
		_prev=this;		
	}
	
	/// copy ctor
	inline CEntityListLink(T *entity)	:	_entity(entity)
	{
		_next=this;
		_prev=this;		
	}

	/// dtor
	inline	~CEntityListLink()
	{
		unlink();
	}

	/// set the entity pointer
	inline	void	setEntity(T	*entityPtr)
	{
#ifdef NL_DEBUG		
		nlassert(entityPtr);
#endif
		_entity=entityPtr;
	}
	
	//------------------------------------------------
	// read accessors
	inline	CEntityListLink<T> *	const	&	next()	const
	{
		return _next;
	}

	inline	CEntityListLink<T> *	const	&	prev()	const
	{
		return _prev;
	}
	
	inline	T	*entity() const
	{
		return	_entity;
	}

	//------------------------------------------------
	// link & unlink
	inline	void link(CEntityListLink<T> &predecessor)
	{
		nlassert(_entity);

		//	unlink (do not refresh prev and next as its done below).
		_prev->_next=_next;
		_next->_prev=_prev;
		
		//	link
		_prev=&predecessor;
		_next=predecessor._next;
		_prev->_next=this;
		_next->_prev=this;
	}

	inline bool unlinked() const
	{
		return	_next==this;
	}
	
	inline	void	unlink()
	{
#ifdef NL_DEBUG
		_entity=NULL;
#endif
		if (unlinked())
			return;
			
		_prev->_next=_next;
		_next->_prev=_prev;
		_next=this;
		_prev=this;
	}

private:

	// prohibited copy
	CEntityListLink &operator=(const CEntityListLink&);
    CEntityListLink(const CEntityListLink &entity);

	CEntityListLink	*_next;
	CEntityListLink	*_prev;
	T	*_entity;
};

//--------------------------------------------------------------------------

#endif

