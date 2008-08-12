/** \file list_link.h
 *
 * $Id: sabrina_list_link.h,v 1.2 2004/03/01 19:22:19 lecroart Exp $
 */



#ifndef RY_SABRINA_LIST_LINK_H
#define RY_SABRINA_LIST_LINK_H

//---------------------------------------------------------------------------------
// CListLink<>
//---------------------------------------------------------------------------------
// A link for linking objects into lists
// The only valid constructor requires a pointer to the parent class that the
// list link represents

#pragma warning (disable : 4355)

template <class T> class CListLink
{
public:
	inline explicit CListLink(T *parent) : _Next(this), _Prev(this), _Parent(parent)
	{
	}

	inline virtual ~CListLink()
	{
		unlink();
	}
	
	inline void linkAfter(CListLink<T> *other)
	{
		#ifdef NL_DEBUG
			nlassert(other);
			nlassert(_Next==this);
			nlassert(_Prev==this);
//			nlassert(other->_Next->_Prev==other->_Prev);
//			nlassert(other->_Prev->_Next==other->_Next);
		#endif
		_Next=other->_Next;
		_Prev=other;

		_Prev->_Next=this;
		_Next->_Prev=this;
	}

	inline void linkBefore(CListLink<T> *other)
	{
		#ifdef NL_DEBUG		
			nlassert(other);
		#endif
		linkAfter(other->prev);
	}

	inline void unlink()
	{
		#ifdef NL_DEBUG
//			if (_Next==this)
//				nlerror("unlink() called for object that is not linked");
//			nlassert (_Next->_Prev==_Prev);
//			nlassert (_Prev->_Next==_Next);
		#endif

		_Next->_Prev=_Prev;
		_Prev->_Next=_Next;

		#ifdef NL_DEBUG
			_Next=this;
			_Prev=this;
		#endif
	}

	inline CListLink<T> * const &next()
	{
		return _Next;
	}

	inline CListLink<T> * const &prev()
	{
		return _Prev;
	}

	inline T *parent()
	{
		return _Parent;
	}

private:
	CListLink<T>	*_Next;
	CListLink<T>	*_Prev;
	T				*_Parent;
};

//---------------------------------------------------------------------------------
#endif // RY_SABRINA_LIST_LINK_H
