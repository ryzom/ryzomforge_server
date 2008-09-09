/** \file client.h
 *
 * $Id: client.h,v 1.7 2005/03/09 17:09:59 brigand Exp $
 */



#ifndef RY_CMS_CLIENT_H
#define RY_CMS_CLIENT_H

#include "game_share/ryzom_mirror_properties.h"
#include "nel/misc/smart_ptr.h"

// A monitor service client
class CMonitorClient : public NLMISC::CRefCount
{
protected:

	// The socket id
	NLNET::TSockId _Sock;

	// The listening bounding box
	NLMISC::CVector _WindowTopLeft, _WindowBottomRight;

public:

	class CEntityEntry
	{
	public:
		CEntityEntry ()
		{
			Flags = 0;
		}
		enum
		{
			Present = 1,
			Pending = 2,
			PosDirty = 4,
			MiscPropDirty = 8,
			DirtyAll = PosDirty | MiscPropDirty
		};
		uint8 Flags;
	};

	/// Constructor
	CMonitorClient(NLNET::TSockId sock);

	/// Destructor
	~CMonitorClient();

	/// Update
	void update ();


	/// Add an entity
	void	add(const TDataSetRow &entity);

	/// Remove an entity
	void	remove(const TDataSetRow &entity);

	/// Reset vision
	void	resetVision();

	//
	void setWindow(float xmin, float ymin, float xmax, float ymax);

	const NLMISC::CVector &getTopLeft() const
	{
		return _WindowTopLeft;
	}

	const NLMISC::CVector &getBottomRight() const
	{
		return _WindowBottomRight;
	}

	// returns the TSockID
	NLNET::TSockId getSock() const {return _Sock;}

	// Entities
	std::vector<CEntityEntry>	Entites;

	// In vision
	std::vector<uint32>			InVision;

	// Start point for entity update
	uint						StartOffset;

	// Pending entities to be added
	std::vector<uint32>			PendingAdd;

	// Pending entities to be removed
	std::vector<uint32>			PendingRemove;

	// The data for the ADD message
	class CAddData
	{
	public:
		uint32 Id;
		TYPE_NAME_STRING_ID	StringId;
		NLMISC::CEntityId	EntityId;
		NLMISC::CSheetId	SheetId;
	};

	// ADD message queue
	std::vector<CAddData>		Add;

	// RMV message queue
	std::vector<uint32>			Rmv;

	// The data for the POS message
	class CPosData
	{
	public:
		uint32 Id;
		float X, Y, Tetha;
	};
	// POS message queue
	std::vector<CPosData>		Pos;

	// The data for the MISC_PROP message
	class CMiscPropData
	{
	public:
		uint32 Id;
		sint32 CurrentHP;
		sint32 MaxHP;
		uint8  Mode;
		uint8  Behaviour;
	};

	// MISC_PROP message queue
	std::vector<CMiscPropData> MiscProp;


	// STR message queue
	std::vector<TYPE_NAME_STRING_ID>	Str;

	// Allowed Upload for this client (in bytes per second)
	uint32						AllowedUploadBandwidth;

	float						AddWeight;
	float						RemoveWeight;
	float						PosWeight;
	float						StrWeight;
	float						MiscPropWeight;
	//
	bool						Authentificated;
	bool						BadLogin; // The client has given a bad login
	                                      // As long as this flag is set, no login should be accepted
	                                      // for that client. The flag will be cleared in the main loop
	                                      // when enough time has ellapsed
};


extern std::vector<NLMISC::CSmartPtr<CMonitorClient> > Clients;



#endif // RY_CMS_CLIENT_H
