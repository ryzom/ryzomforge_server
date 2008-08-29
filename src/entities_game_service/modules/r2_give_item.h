/** \file r2_give_item.h
 * Module manage give item egs part (services implied: AIS/DSS/EGS)
 * Manage give item in npc view and player view (= give and receive item for one view).
 *
 * $Id: r2_give_item.h,v 1.4 2007/05/25 09:47:42 verquerre Exp $
 */


#ifndef R2_GIVE_ITEM_H
#define R2_GIVE_ITEM_H

#include <vector>
#include <map>
#include <string>

#include "nel/misc/types_nl.h"
#include "nel/misc/singleton.h"
#include "nel/misc/entity_id.h"

#include "server_share/msg_ai_service.h"
#include "game_share/scenario.h"

class CCharacter;

class CR2GiveItem : public NLMISC::CSingleton<CR2GiveItem>
{
public:
	struct TItemRequest
	{
		TDataSetRow		CharacterRowId;
		TDataSetRow		CreatureRowId;
		TAIAlias		GroupAlias;
		uint32			InstanceId;
		uint32			ActionId;
		std::vector< R2::TItemAndQuantity > ItemsRequest;
		std::string		MissionText; //utf8 string
		bool			IsGiveItem;

		bool operator == (const CItemRequestMsgItf& msg) const
		{
			return ( CharacterRowId == msg.getCharacterRowId() &&
				CreatureRowId == msg.getCreatureRowId() &&
				GroupAlias == msg.getGroupAlias() &&
				InstanceId == msg.getInstanceId() );
		}

		const TItemRequest& operator = ( const CItemRequestMsgItf& msg )
		{
			CharacterRowId = msg.getCharacterRowId();
			CreatureRowId = msg.getCreatureRowId();
			GroupAlias = msg.getGroupAlias();
			InstanceId = msg.getInstanceId();
			for( uint32 j = 0; j < msg.getItems().size(); ++ j )
			{
				for( uint32 i = 0; i < ItemsRequest.size(); ++i )
				{
					if( ItemsRequest[ i ].SheetId == msg.getItems()[ j ] )
					{
						ItemsRequest[ i ].Quantity += msg.getQuantities()[ j ];
						break;
					}
				}
				ItemsRequest.push_back( R2::TItemAndQuantity( msg.getItems()[ j ], msg.getQuantities()[ j ] ) );
			}
			MissionText = msg.getMissionText();
			return *this;
		}
	};

	typedef TDataSetRow TCreatureRowId;
	typedef std::vector< TItemRequest > TCreatureItemRequest;
	typedef std::map< TCreatureRowId, TCreatureItemRequest > TPendingRequest;

	// constructor
	CR2GiveItem() {};
	// destructor
	~CR2GiveItem() {}

	// AIS send a give item request
	void giveItemRequest( const CGiveItemRequestMsg &msg );

	// AIS send a receive item request
	void receiveItemRequest( const CReceiveItemRequestMsg &msg );

	// player character choose give item
	void playerCharacterGiveItem( TDataSetRow characterId );

	// onUntarget, clear database
	void onUntarget( CCharacter *c, TDataSetRow oldTarget );

	// player character choose an R2 Mission item
	void giveItemGranted( TDataSetRow creatureRowId, uint32 actionId ); 

	// on unspawn: update _PendingRequest
	void onUnspawn( TDataSetRow creatureRowId );

private:
	bool _ValidateGiveItemRequest( const TItemRequest &req );
	void _SetClientDB( const TItemRequest & req, uint32 MissionIndex );
	void _SetClientDBAll( CCharacter *c, const TCreatureItemRequest & req );
	void _SendAckToAIS( bool ok, const TItemRequest &req );
	uint32 _regiserLiteralString( TDataSetRow userRowId, const ucstring &litStr );

	TPendingRequest		_PendingRequest;
	static uint32		_NextActionId;
};


class CGiveItemRequestMsgImp : public CGiveItemRequestMsg
{
	void callback (const std::string &name, NLNET::TServiceId id);
};

class CReceiveItemRequestMsgImp : public CReceiveItemRequestMsg
{
	void callback (const std::string &name, NLNET::TServiceId id);
};



#endif


