/** \file static_vector.h
 *
 * $Id: static_vector.h,v 1.15 2004/03/01 19:19:21 lecroart Exp $
 */




#ifndef RYAI_STATIC_VECTOR_H
#define RYAI_STATIC_VECTOR_H


/*

  This class implements an array of entities of any derived class of a given base class
  The entities are allocated in a single memory block.

*/

//	not the way to use templates .. ( bad generalisation implementation ).

/*
template <class BaseClass> 
class StaticVector
{
public:
	// ctor & dtor --------------------------------------------------
	StaticVector(): _data(0), _count(0), _size(0) {}
	~StaticVector() { if (_data) delete[] _data; }

	// allocate memory and initialise objects -----------------------
	template <class DerivedClass>
	void init(uint count,DerivedClass *&dc)
	{
		nlassert(_data==NULL);
		_count=count;
		
		_data=(BaseClass*)malloc(count*sizeof(DerivedClass));
		_size=sizeof(DerivedClass);
		nlassert(_data!=NULL);
		
		for (uint i=0;i<count;++i)
		{
//			std::construct(&((DerivedClass*)_data)[i], DerivedClass());
#undef new
			new (&((DerivedClass*)_data)[i]) DerivedClass();
#define new NL_NEW
		}
	}

	// destroy array of objects and free memory ---------------------
	void release()
	{
		_count=0;
		_size=0;
		if (_data)
			delete[] _data;
	}

	// return number of objects in array or 0 if not initialised ----
	uint count() const
	{
		return _count;
	}

	// [] operator for accessing data -------------------------------
	BaseClass &operator[](uint index) const
	{
		nlassert( index < _count );
		return *(BaseClass *)((char *)_data+index*_size);
	}

	void setElm(BaseClass *obj, uint index)
	{
		nlassert( index < _count );
//		BaseClass *ptr = (BaseClass *) ((char *)_data+index*_size);
//		memcpy( ptr, obj, _size );
		( *(BaseClass *)((char *)_data+index*_size) ) = *obj; 
	}

private:
	BaseClass*  _data;
	uint _count;
	uint _size;
	
};
*/

#endif

