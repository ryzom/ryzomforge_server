/** \file static_items.h
 * Craft and keep a model of each selling item
 *
 * $Id: static_items.h,v 1.3 2005/07/07 15:08:38 coutelas Exp $
 */

#ifndef RYZOM_STATIC_ITEM_H
#define RYZOM_STATIC_ITEM_H

#include "game_share/people.h"
#include "game_share/item_type.h"
#include "game_share/rm_family.h"


/**
 * CStaticItems
 * Mount list of items selling in game
 * \author Alain Saffray
 * \author Nevrax France
 * \date 2003
 */
class CStaticItems
{
public:
	struct CRMForOneItemPart
	{
		std::vector< NLMISC::CSheetId >	RawMaterial;
	};

	// build static item vector
	static void buildStaticItem();		

	// CStaticItems::buildOntItem use faber system for make an item
	static CGameItemPtr buildOnetItem( NLMISC::CSheetId sheet );

	// init raw material table used for build static item
	static void initRmTable();

	// select raw material for build static item
	static void selectRmForCraft( const NLMISC::CSheetId& craftPlan, std::vector< NLMISC::CSheetId >& Rm, std::vector< NLMISC::CSheetId >& RmFormula );

	// return StaticItem reference
	static inline const std::vector< CGameItemPtr > & getStaticItems() {return _StaticItems;}

private:
	static std::vector< CGameItemPtr >	_StaticItems;
	static std::vector< CRMForOneItemPart >	_RmForSystemCraft;
};

#endif // RYZOM_STATIC_ITEM_H

/* static_items.h */

