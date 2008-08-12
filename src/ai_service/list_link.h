/** \file list_link.h
 *
 * $Id: list_link.h,v 1.7 2004/03/01 19:19:20 lecroart Exp $
 */



#ifndef RYAI_LIST_LINK_H
#define RYAI_LIST_LINK_H

//---------------------------------------------------------------------------------
// CListLink<>
//---------------------------------------------------------------------------------
// A link for linking objects into lists
// The only valid constructor requires a pointer to the parent class that the
// list link represents

#pragma warning (disable : 4355)

template <class C>
class CListLink
{
public:
	inline CListLink(C *parent) : _next(this), _prev(this), _parent(parent)
	{
	}

	inline virtual ~CListLink()
	{
		unlink();
	}
	
	inline void linkAfter(CListLink<C> *other)
	{
		#ifdef NL_DEBUG
			nlassert(_next==this);
			nlassert(_prev==this);
//			nlassert(other->_next->_prev==other->_prev);
//			nlassert(other->_prev->_next==other->_next);
		#endif
		_next=other->_next;
		_prev=other;

		_prev->_next=this;
		_next->_prev=this;
	}

	inline void linkBefore(CListLink<C> *other)
	{
		linkAfter(other->prev);
	}

	inline void unlink()
	{
		#ifdef NL_DEBUG
//			if (_next==this)
//				nlerror("unlink() called for object that is not linked");
//			nlassert (_next->_prev==_prev);
//			nlassert (_prev->_next==_next);
		#endif

		_next->_prev=_prev;
		_prev->_next=_next;

		#ifdef NL_DEBUG
			_next=this;
			_prev=this;
		#endif
	}

	inline C *next()
	{
		return _next->_parent;
	}

	inline C *prev()
	{
		return _prev->_parent;
	}

private:
	CListLink<C> *_next;
	CListLink<C> *_prev;
	C *_parent;
};

//---------------------------------------------------------------------------------
#endif
