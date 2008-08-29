/** \file pet_interface_msg.h
 *
 * $Id: pet_interface_msg.h,v 1.21 2007/05/25 09:47:43 verquerre Exp $
 */



#ifndef RY_PET_INTERFACE_MESSAGES_H
#define RY_PET_INTERFACE_MESSAGES_H

#include "nel/misc/types_nl.h"
#include "nel/misc/sheet_id.h"

#include "game_share/synchronised_message.h"
#include "game_share/mirror.h"


// Pet interface message class for AIS / EGS communication

//----------------------------------------------------------------
// pet spawn
//----------------------------------------------------------------
class CPetSpawnMsg : public CMirrorTransportClass
{
public:
	enum TSpawnMode { NEAR_PLAYER = 0, NEAR_POINT };
	uint32				AIInstanceId;
	uint16				SpawnMode;
	TDataSetRow			CharacterMirrorRow;
	NLMISC::CSheetId	PetSheetId;
	uint16				PetIdx;	// must be returned to EGS with CPetSpawnConfirmationMsg class
	sint32				Coordinate_X, Coordinate_Y, Coordinate_H; //For NEAR_POINT mode
	float				Heading; //For NEAR_POINT mode

	virtual void description ()
	{
		className ("CPetSpawnMsg");
		property ("AIInstanceId", PropUInt32, (uint32)~0, AIInstanceId);
		property ("SpawnMode", PropUInt16, (uint16)NEAR_PLAYER, SpawnMode);
		property ("CharacterMirrorRow",	PropDataSetRow,	TDataSetRow(), CharacterMirrorRow);
		property ("PetSheetId", PropSheetId, NLMISC::CSheetId::Unknown, PetSheetId);
		property ("PetIndex", PropUInt16, (uint16)0, PetIdx);
		property ("Coordinate_X", PropSInt32, (sint32)0, Coordinate_X);
		property ("Coordinate_Y", PropSInt32, (sint32)0, Coordinate_Y);
		property ("Coordinate_H", PropSInt32, (sint32)0, Coordinate_H);
		property ("Heading", PropFloat, 0.0f, Heading);
	}

	virtual void callback (const std::string &name, NLNET::TServiceId id) {};
};

		
//----------------------------------------------------------------
// spawn confirmation
//----------------------------------------------------------------
class CPetSpawnConfirmationMsg : public CMirrorTransportClass
{
public:
	enum TSpawnError 
	{ 
		NO_ERROR_SPAWN = 0,
		CHARATER_UNKNOWN, 
		PET_SHEETID_UNKNOWN, 
		CHARACTER_LAND_MAP_UNKNOWN, 
		COORDINATE_NOT_IN_WORLD, 
		NOT_IMPLEMENTED, 
		INTERNAL_ERROR, 
		PET_ALREADY_SPAWNED 
	};
	uint16 SpawnError;
	TDataSetRow	CharacterMirrorRow;
	TDataSetRow	PetMirrorRow; //If spawned
	uint16 PetIdx;

	virtual void description ()
	{		
		className ("CPetSpawnConfirmationMsg");
		property ("SpawnError", PropUInt16, (uint16)NO_ERROR_SPAWN, SpawnError);
		property ("CharacterMirrorRow", PropDataSetRow,	TDataSetRow(), CharacterMirrorRow);
		property ("PetMirrorRow",		PropDataSetRow,	TDataSetRow(), PetMirrorRow);
		property ("PetIndex", PropUInt16, (uint16)0, PetIdx);
	}
	virtual void callback (const std::string &name, NLNET::TServiceId id) {};
};


//----------------------------------------------------------------
// pet command
//----------------------------------------------------------------
class CPetCommandMsg : public CMirrorTransportClass
{
public:
	enum TCommand { STAND = 0, FOLLOW, GOTO_POINT, GOTO_POINT_DESPAWN, LIBERATE, DESPAWN };
	enum TCommandError { COLLISION_NOT_VALIDNO_ERROR_SPAWN = 0, CHARATER_UNKNOWN, PET_SHEETID_UNKNOWN, CHARACTER_LAND_MAP_UNKNOWN, COORDINATE_NOT_IN_WORLD, NOT_IMPLEMENTED, INTERNAL_ERROR };
	uint16 Command;
	TDataSetRow	CharacterMirrorRow;
	TDataSetRow PetMirrorRow;
	sint32	Coordinate_X, Coordinate_Y, Coordinate_H; //For GOTO_POINT, GOTO_POINT_DESPAWN and SPAWN_POINT commands
	float Heading; // For GOTO_POINT_DESPAWN commands (via stable)
	
	virtual void description ()
	{
		className ("CPetCommandMsg");
		property ("Command", PropUInt16, (uint16)STAND, Command);
		property ("CharacterMirrorRow", PropDataSetRow,	TDataSetRow(), CharacterMirrorRow);
		property ("PetMirrorRow", PropDataSetRow, TDataSetRow(), PetMirrorRow);
		property ("Coordinate_X", PropSInt32, (sint32)0, Coordinate_X);
		property ("Coordinate_Y", PropSInt32, (sint32)0, Coordinate_Y);
		property ("Coordinate_H", PropSInt32, (sint32)0, Coordinate_H);
		property ("Heading", PropFloat, 0.0f, Heading);
	}

	virtual void callback (const std::string &name, NLNET::TServiceId id) {};
};

//----------------------------------------------------------------
// command confirmation
//----------------------------------------------------------------
class CPetCommandConfirmationMsg : public CMirrorTransportClass
{
public:
	enum TCommandError { NO_ERROR_COMMAND = 0, POSITION_COLLISION_NOT_VALID };
	uint16 CommandError;
	TDataSetRow	CharacterMirrorRow;
	TDataSetRow PetMirrorRow;

	CPetCommandConfirmationMsg()
	{}

	CPetCommandConfirmationMsg(uint16 commandError,	const	CPetCommandMsg	&msg)
	:CommandError(commandError)
	,CharacterMirrorRow(msg.CharacterMirrorRow)
	,PetMirrorRow(msg.PetMirrorRow)
	{}

	virtual void description ()
	{		
		className ("CPetCommandConfirmationMsg");
		property ("CommandError", PropUInt16, (uint16)NO_ERROR_COMMAND, CommandError);
	}
	virtual void callback (const std::string &name, NLNET::TServiceId id) {};
};

//----------------------------------------------------------------
// pet owner
//----------------------------------------------------------------
class CPetSetOwner : public CMirrorTransportClass
{
public:

	TDataSetRow	OwnerMirrorRow;
	TDataSetRow PetMirrorRow;

	virtual void description ()
	{
		className ("CPetSetOwner");
		property ("OwnerMirrorRow", PropDataSetRow, TDataSetRow(), OwnerMirrorRow);
		property ("PetMirrorRow", PropDataSetRow, TDataSetRow(), PetMirrorRow);
	}
	
	virtual void callback (const std::string &name, NLNET::TServiceId id) {};
};

#endif //RY_PET_INTERFACE_MESSAGES_H
