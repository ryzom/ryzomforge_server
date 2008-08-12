/** \file simple_entity_manager.h
 * <File description>
 *
 * $Id: simple_entity_manager.h,v 1.6 2004/12/08 13:26:44 besson Exp $
 */



#ifndef NL_SIMPLE_ENTITY_MANAGER_H
#define NL_SIMPLE_ENTITY_MANAGER_H

#include "nel/misc/vector_2f.h"
#include "game_share/base_types.h"


/**
 *
 */
template <class T>
class CSimpleEntityManager
{
public:

	typedef std::vector<T*> CSimpleEntityVec;

	/// Initialization
	void		init( TDataSetIndex baseRowIndex, TDataSetIndex size );

	/// Add an entity object
	void		addEntity( T *object )
	{
		TDataSetIndex index = rowIdToVecIndex( object->rowId() );
		if (index < _SimpleEntities.size())
		{
			_SimpleEntities[index] = object;
			++_NbEntities;
		}
		else
		{
			nlwarning("<CSimpleEntityManager::addEntity> entity index %u is out of range, vector size is %u", index, _SimpleEntities.size());
		}
	}
	//{ _SimpleEntities.insert( std::make_pair( object->rowId(), object ) ); }

	/// Destroy an entity object
	void		destroyEntity( const TDataSetRow& entityRowId );

	/// Access an entity object
	T *			getEntity( const TDataSetRow& entityRowId )
	{
		if ( ! TheDataset.isAccessible2(entityRowId) ) // allow unpublished entities
		{
			nlwarning( "E%u is not anymore in mirror", entityRowId.getIndex() );
			return NULL;
		}

		TDataSetIndex index = rowIdToVecIndex( entityRowId );
		if ( index >= _SimpleEntities.size() )
		{
			nlwarning( "E%u is out of range, vector size is %u", index, _SimpleEntities.size() );
			return NULL;
		}
		
		return _SimpleEntities[index];
		/*CSimpleEntityVec::iterator ism = _SimpleEntities.find( entityRowId );
		if ( ism != _SimpleEntities.end() )
			return (*ism).second;
		else
			return NULL;*/
	}

	/// Return the number of valid entities
	uint		nbEntities() const { return _NbEntities; }

	/// Update (call it at every tick)
	void		tickUpdate();

protected:

	///
	TDataSetIndex		rowIdToVecIndex( const TDataSetRow& rowId )
	{
		return rowId.getIndex() - _BaseIndex;
	}

	/// Singleton instance (set by init())
	static CSimpleEntityManager<T> *_Instance;

private:
	
	/// Source container
	CSimpleEntityVec	_SimpleEntities;

	/// Beginning row index of the entities
	TDataSetIndex		_BaseIndex;

	/// Number of valid entities
	uint				_NbEntities;
};


/*
 *
 */
template <class T>
void CSimpleEntityManager<T>::init( TDataSetIndex baseRowIndex, TDataSetIndex size )
{
	nlassert( ! _Instance );
	_Instance = this;

	_SimpleEntities.resize( size, NULL );
	_BaseIndex = baseRowIndex;
	_NbEntities = 0;
}


/*
 *
 */
template <class T>
void CSimpleEntityManager<T>::destroyEntity( const TDataSetRow& entityRowId )
{
	TDataSetIndex index = rowIdToVecIndex( entityRowId );
	if (index >= _SimpleEntities.size())
	{
		nlwarning("<CSimpleEntityManager::destroyEntity> entity index %u is out of range, vector size is %u", index, _SimpleEntities.size());
		return;
	}

	if (_SimpleEntities[index] != NULL)
	{
		delete _SimpleEntities[index];
		_SimpleEntities[index] = NULL;
		--_NbEntities;
	}
	else
	{
		nlwarning("<CSimpleEntityManager::destroyEntity> trying to destroy a NULL entity at index %u", index);
	}

	/*CHarvestSourceMap::iterator ism = _RunningSources.find( sourceRowId );
	if ( ism != _RunningSources.end() )
	{
		delete (*ism).second;
		_RunningSources.erase( ism );
	}*/
}


/*
 * Update (call it at every tick)
 */
template <class T>
void CSimpleEntityManager<T>::tickUpdate()
{
	// Update sources
	for ( typename CSimpleEntityVec::iterator isv=_SimpleEntities.begin(); isv!=_SimpleEntities.end(); ++isv )
	{
		T *object = (*isv);
		if ( ! object )
			continue;

		if ( ! object->update() )
		{
			delete object;
			(*isv) = NULL;
			--_NbEntities;
		}
	}

	/*vector<TDataSetRow> toDestroy;

	// Update sources
	for ( CHarvestSourceMap::iterator ism=_RunningSources.begin(); ism!=_RunningSources.end(); ++ism )
	{
		CHarvestSource *hsource = (*ism).second;
		if ( ! hsource->update() )
		{
			toDestroy.push_back( hsource->rowId() );
		}
	}

	// Destroy "dead" sources
	for ( vector<TDataSetRow>::iterator it=toDestroy.begin(); it!=toDestroy.end(); ++it )
	{
		destroySource( *it );
	}*/
}


#endif // NL_SIMPLE_ENTITY_MANAGER_H

/* End of simple_entity_manager.h */
