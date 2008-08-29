/** \file msg_object_player_manager.h
 * Definition of all classes used in messages for communication with (at destination to) the OPMS
 *
 * $Id: msg_object_player_manager.h,v 1.19 2007/05/25 09:47:43 verquerre Exp $
 */



#ifndef RY_MSG_OBJECT_PLAYER_MANAGER_H
#define RY_MSG_OBJECT_PLAYER_MANAGER_H

#include "nel/misc/types_nl.h"
#include "nel/misc/time_nl.h"

#include "nel/net/transport_class.h"
#include "game_share/ryzom_entity_id.h"
#include "game_share/synchronised_message.h"


/**
 * Class COPSAddEffectModifier, message class used to add a new modifier effect on a player
 * \author David Fleury
 * \author Nevrax France
 * \date 2002
 */
class COPSAddEffectModifier : public CMirrorTransportClass
{
public:
	TDataSetRow			CreatorId;			// id of the entity which created this effect (if any)
	TDataSetRow			PlayerId;			// id of the entity on which this effect is to be applied
	uint16				EffectType;

	enum EMode { set = 0, modify, variation };

//	NLMISC::TGameCycle	Duration;			// Apply duration of modifier
//	NLMISC::TGameCycle	RepeatInterval;		// 0 = apply effect only once, no repeatition
	uint32				Duration;			// Apply duration of modifier
	uint32				RepeatInterval;		// 0 = apply effect only once, no repeatition

	uint16				NbRepeat;			// means nothing if RepeatInterval == 0, otherwise it's the max number of repeatition, 0 == NO LIMIT
	std::string			AffectedValue;		// Name of affected value
	sint32				Modifier;			// 
	uint8				Mode;				// mode (set, variation modify)
	uint16				LifePoints;			// nb of life points of the effect

	std::list<uint16>	KillerEffects;		// the effect types that cancel this effect
	std::list<uint16>	PreventedEffects;	// the effect types prevented by this effect

	/// name of the string to display in the chat of the player at each application of the effect (MUST have NO param)
	std::string			ApplyPrivateMsgName;

	/// name of the string to display in the general chat at each application of the effect (MUST have ONE param of type $e)
	std::string			ApplySpectatorsMsgName;

	/// name of the string to display in the chat of the effect creator player (MUST have ONE param of type $e)
	std::string			ApplyCreatorMsgName;

	/// name of the string to display in the chat of the player at the end of the effect (MUST have NO param)
	std::string			EndPrivateMsgName;

	/// name of the string to display in the general chat at the end of the effect (MUST have ONE param of type $e)
	std::string			EndSpectatorsMsgName;
	
	/// name of the string to display in the chat of the effect creator player (MUST have ONE param of type $e)
	std::string			EndCreatorMsgName;

	/// name of the impulsion that will be sent to the client at the end of the effect
	std::string			EndImpulsionName;

	COPSAddEffectModifier() 
	{}

	virtual void description ()
	{
		className ("COPSAddEffectModifier");

		property ("CreatorId", PropDataSetRow, TDataSetRow(), CreatorId);
		property ("PlayerId", PropDataSetRow, TDataSetRow(), PlayerId);

		property ("Duration", PropUInt32, uint32(0), Duration);
		property ("RepeatInterval", PropUInt32, uint32(0), RepeatInterval);

		property ("EffectType", PropUInt16, uint16(0), EffectType);
		property ("NbRepeat", PropUInt16, uint16(0), NbRepeat);
		property ("AffectedValue", PropString, std::string(""), AffectedValue);
		property ("Modifier", PropSInt32, sint32(0), Modifier);
		property ("Mode", PropUInt8, uint8(set), Mode);		
		property ("LifePoints", PropUInt16, uint16(0), LifePoints);

		propertyCont ("KillerEffects", PropUInt16, KillerEffects);
		propertyCont ("PreventedEffects", PropUInt16, PreventedEffects);

		property ("ApplyPrivateMsgName", PropString, std::string(""), ApplyPrivateMsgName);
		property ("ApplySpectatorsMsgName", PropString, std::string(""), ApplySpectatorsMsgName);
		property ("ApplyCreatorMsgName", PropString, std::string(""), ApplyCreatorMsgName);
		property ("EndPrivateMsgName", PropString, std::string(""), EndPrivateMsgName);
		property ("EndSpectatorsMsgName", PropString, std::string(""), EndSpectatorsMsgName);
		property ("EndCreatorMsgName", PropString, std::string(""), EndCreatorMsgName);
		property ("EndImpulsionName", PropString, std::string(""), EndImpulsionName);
	}

	virtual void callback (const std::string &name, NLNET::TServiceId id);
};





/**
 * COPSCreateItem 
 * message class used to create an item
 * \author Stephane Coutelas
 * \author Nevrax France
 * \date 2002
 */
class COPSCreateItem : public CMirrorTransportClass
{
public:
	
	TDataSetRow	Id;
	NLMISC::CSheetId SheetId;
	TDataSetRow	Owner;
	uint8 Slot;
	sint32 X;
	sint32 Y;
	sint32 Z;


	COPSCreateItem() 
	{
		Slot = 0;
		X = 0;
		Y = 0;
		Z = 0;
	}

	virtual void description ()
	{
		className ("COPSCreateItem");

		property ("Id", PropDataSetRow, TDataSetRow(), Id);
		property ("SheetId", PropSheetId, NLMISC::CSheetId(0), SheetId);
		property ("Owner", PropDataSetRow, TDataSetRow(), Owner);
		
		property ("Slot", PropUInt8, uint8(0), Slot);
		property ("X", PropSInt32, sint32(0), X);
		property ("Y", PropSInt32, sint32(0), Y);
		property ("Z", PropSInt32, sint32(0), Z);
	}

	virtual void callback (const std::string &name, NLNET::TServiceId id);
};


/**
 * COPSDestroyItem 
 * message class used to destroy an item
 * \author Stephane Coutelas
 * \author Nevrax France
 * \date 2002
 */
class COPSDestroyItem : public CMirrorTransportClass
{
public:
	
	TDataSetRow	Id;
	
	COPSDestroyItem() 
	{}

	virtual void description ()
	{
		className ("COPSDestroyItem");

		property ("Id", PropDataSetRow, TDataSetRow(), Id);
	}

	virtual void callback (const std::string &name, NLNET::TServiceId id);
};



/**
 * COPSMovetem 
 * message class used to move an item
 * \author Stephane Coutelas
 * \author Nevrax France
 * \date 2002
 */
class COPSMoveItem : public CMirrorTransportClass
{
public:
	
	TDataSetRow	Id;
	uint8 Slot;
	sint32 X;
	sint32 Y;
	sint32 Z;


	COPSMoveItem() 
	{
		Slot = 0;
		X = 0;
		Y = 0;
		Z = 0;
	}

	virtual void description ()
	{
		className ("COPSMoveItem");

		property ("Id", PropDataSetRow, TDataSetRow(), Id);
		
		property ("Slot", PropUInt8, uint8(0), Slot);
		property ("X", PropSInt32, sint32(0), X);
		property ("Y", PropSInt32, sint32(0), Y);
		property ("Z", PropSInt32, sint32(0), Z);
	}

	virtual void callback (const std::string &name, NLNET::TServiceId id);
};



#endif // RY_MSG_OBJECT_PLAYER_MANAGER_H

/* End of msg_object_player_manager.h */
