/** \file egs_static_ai_action.h
 * <File description>
 *
 * $Id: egs_static_guild_option.h,v 1.3 2004/12/08 13:26:46 besson Exp $
 */

//Nel georges
#include "nel/georges/u_form.h"
#include "game_share/sp_type.h"


namespace GUILD_OPTIONS
{
	enum TType
	{
		MainBuilding,
		RmFight,
		RmMagic,
		RmHarvest,
		RmCraft,
		Unknown,
	};
}

/**
 * A guild option form
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2003
 */
class CStaticGuildOption
{
public:
	

	EGSPD::CSPType::TSPType getSpType()const
	{
		switch(Type)
		{
		case GUILD_OPTIONS::RmFight:
			return EGSPD::CSPType::Fight;
		case GUILD_OPTIONS::RmMagic:
			return EGSPD::CSPType::Magic;
		case GUILD_OPTIONS::RmHarvest:
			return EGSPD::CSPType::Harvest;
		case GUILD_OPTIONS::RmCraft:
			return EGSPD::CSPType::Craft;
		default:
			return EGSPD::CSPType::EndSPType;
		}
	}

	/// Read georges sheet
	void readGeorges (const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const NLMISC::CSheetId &sheetId);

	/// Serial
	void serial(class NLMISC::IStream &f);

	/// Return the version of this class, increments this value when the content of this class has changed
	inline static uint getVersion () { return 1; }

	/// Removed
	void removed() {}

	uint32 Price;
	GUILD_OPTIONS::TType Type;

};


