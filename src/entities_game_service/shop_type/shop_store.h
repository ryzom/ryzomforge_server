/** \file shop_store.h
 * Manage shop store: shop where player can sell it's items to other players
 *
 * $Id: shop_store.h,v 1.1 2004/09/07 18:00:23 saffray Exp $
 */


/*
	- 2 origins for items in sell
		- default crafted items and MP/TOOLS/Pet, always exist in infinite quantity
		- player items list per continent

	- A shop store is a bot merchant
	- What a merchant sell stay driven by shop_category.cfg and CShopTypeManager, sub-list per continent stay driven by origin, but in this case it's origin of where it's selled by player and not item origin
	- Each merchant sell:
		- basic item (infinite quantity with basic statistics, maximum price)
		- players items (item selled by players) price setted per player

	- For prevent lost item in sell or sell an item 2 times 
		- players character keep a class contains items he have in shop store (CItemSelling) , this class are saved with character
		- shop store save item selled for sending money to seller when player character enter in game and update CItemSelling of character
		- shop store not save item in sell, this are be re-constructed at EGS launch by parsing all players characters's CItemShopStore
	  

	process:
	- Establish players items selled by a npc merchant use same rules than default item, but provide by another liste (one liste of player items per continent), default item list are provided by CSellItem like before.
	- At EGS start, init list of player item in store by parsing all CItemSelling in character saved, and mount CItemShopStore, use it for re-init eid_translation data for keep it accurate
                    init list of item selled, and remove it in list of item in store
	- At character login: check list of item selled, for each item of this character, send to it corresponding money / message and remove item from selled item list, when all list are checked, send a unique message to BS for save character and list of selled item
	- When character sell an item, remove item from it's inventory, put item to CItemSelling class, give to player corresponding minimum price, set item to shop store of continent where player are, , send a unique message to BS for save character and list of selled item.
	- When player buy an item selled by other character (same way than default items), update selled item of CShopStore with item buyed, send unique message to BS for saving buyer character and list of selled item.
	- When selled item of CShopStore are added, check if seller player character are online, if it is send money and message, remove item of selled item list, send a unique message to BS for save character and list of selled item.


	class needed:

	CShopStore:
		- CItemShopStored	//not saved, init at egs start with character saved
		- CSelledItem		//class contains selled item, saved/reloaded at egs start

	CCharacter				// actual class of player charater
		- CItemSelling		// contains item selled by character, saved / reloaded with character save


*/


#ifndef RY_SHOP_STORE_H
#define RY_SHOP_STORE_H
