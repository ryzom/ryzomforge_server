/** \file cdb_data_instance_container.cpp
 * <File description>
 *
 * $Id: cdb_data_instance_container.cpp,v 1.11 2006/09/14 17:04:21 cado Exp $
 */



#include "stdpch.h"
#include "cdb_data_instance_container.h"
#include "player_manager/db_string_updater.h"


/*
 * Initialization
 */
void			CCDBDataInstanceContainer::init( TCDBDataIndex size, bool usePermanentTracker )
{
	_DataArray.init( size, 0 );

	_ChangeTracker.init( size );
	_UsePermanentTracker = usePermanentTracker;
	if ( usePermanentTracker )
		_PermanentTracker.init( size );
}


/*
 * Return the number of changes
 */
/*uint			CCDBDataInstanceContainer::getChangedPropertyCount() const
{
	// TODO: can be optimized by storing the value in the class
	
	uint nb = 0;
	TCDBDataIndex dataIndex = getFirstChanged();
	while ( dataIndex != CDB_LAST_CHANGED )
	{
		++nb;
		dataIndex = getNextChanged( dataIndex );
	}
	return nb;
}*/


/*
 * Record a change (push)
 */
inline void		CCDBChangeTracker::recordChange( TCDBDataIndex index )
{
	// Note: could be shorter to link backwards but we need to link forward
	// to read the changes in order (for partial sending)

	// Test if the entity is already or not flagged as changed
	if ( _TrackVec[index] == CDB_INVALID_DATA_INDEX )
	{
		// Set the entityIndex as changed, and last one
		_TrackVec[index] = CDB_LAST_CHANGED;

		if ( _LastChanged != CDB_INVALID_DATA_INDEX )
		{
			// Link the previous last one to the new last one
			//nlassertex( _LastChanged != index, ( "Looping at %u", entityIndex ) );
			_TrackVec[_LastChanged] = index;
		}
		else
		{
			// Set the first one if not set
			_FirstChanged = index;
			//nldebug( "_ChangeTracker._TrackVec[%d] = %d", index, _ChangeTracker._TrackVec[index] );
		}

		// Set the new last one
		_LastChanged = index;

		// Increment the counter
		++_ChangedCount;
	}
}


/*
 * Record a change (push) in the backward-linnked-list which entry-point is subtrackerLast
 */
inline void		CCDBChangeTracker::recordChangeSublist( TCDBDataIndex& subtrackerLast, TCDBDataIndex index )
{
	// Test if the entity is already or not flagged as changed
	if ( _TrackVec[index] == CDB_INVALID_DATA_INDEX )
	{
		// Set the index as changed, and link it to the previous one (the first time, it's CDB_LAST_CHANGED)
		_TrackVec[index] = subtrackerLast;

		// Make the list entry point (last item) pointing to the new entry
		subtrackerLast = index;
	}
}

/*
 * Set the value of the property (no bound check, sets change flag if value different than previous).
 */
bool			CCDBDataInstanceContainer::setValue64( TCDBDataIndex index, sint64 value, bool forceSending )
{
	if ( (_DataArray[index] != value) || forceSending )
	{
		_DataArray[index] = value;
		_ChangeTracker.recordChange( index );
		if ( _UsePermanentTracker )
			_PermanentTracker.recordChange( index );
		return true;
	}
	else
		return false;
}


/*
 * Set the value of the property (no bound check, set the change flag in an atom group if value different than previous)
 */
bool			CCDBDataInstanceContainer::setValue64InAtom( TCDBDataIndex index, sint64 value, TCDBDataIndex atomGroupIndex, bool forceSending )
{
	// Set the value
	if ( (_DataArray[index] != value) || forceSending )
	{
		_DataArray[index] = value;

		// Record the change of the atom in the main tracker
		_ChangeTracker.recordChange( atomGroupIndex );	

		// Record the change of the particular value in the atom subtracker
		_ChangeTracker.recordChangeSublist( (TCDBDataIndex&)(_DataArray[atomGroupIndex]), index );

		if ( _UsePermanentTracker )
		{
			_PermanentTracker.recordChange( atomGroupIndex );	
			_PermanentTracker.recordChangeSublist( (TCDBDataIndex&)(_DataArray[atomGroupIndex]), index );
		}

		return true;
	}
	else
		return false;
}


/*
 * Debug
 */
void		CCDBDataInstanceContainer::displayAtomChanges( TCDBDataIndex atomGroupIndex )
{
	nlinfo( "List of changes for AtomGroupIndex %hd", atomGroupIndex );
	TCDBDataIndex index = (TCDBDataIndex)_DataArray[atomGroupIndex];
	if ( index == CDB_LAST_CHANGED )
	{
		nlinfo( "<None>" );
	}
	else do
	{
		nlinfo( "> %hd", index );
		index = _ChangeTracker._TrackVec[index];
	}
	while ( index != CDB_LAST_CHANGED );
}
