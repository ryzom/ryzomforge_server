/** \file special_power_phrase.h
 * <Harvest phrase>
 *
 * $Id: special_power_phrase.h,v 1.16 2006/10/10 08:22:30 saffray Exp $
 */



#ifndef RYZOM_SPECIAL_POWER_PHRASE_H
#define RYZOM_SPECIAL_POWER_PHRASE_H

//
#include "special_power.h"
#include "phrase_manager/s_phrase.h"
#include "entity_manager/bypass_check_flags.h"
#include "egs_sheets/egs_static_brick.h"


class CGameItem;

/**
 * This class represents a sabrina phrase used for special powers such as auras
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CSpecialPowerPhrase : public CSPhrase
{
public:

	/// ctor
	CSpecialPowerPhrase();

	/// dtor
	virtual ~CSpecialPowerPhrase();

	/// \name Override methods from CSPhrase
	//@{
	virtual bool build( const TDataSetRow & actorRowId, const std::vector< const CStaticBrick* >& bricks, bool buildToExecute = true );

	/**
	 * evaluate phrase
	 * \return true if eval has been made without errors
	 */
	virtual bool evaluate();
	
	/**
	 * validate phrase
	 * \return true if phrase is valid
	 */
	virtual bool validate();
	virtual bool update();
	virtual void execute();
	virtual bool launch();
	virtual void apply();
	
	/**
	 * called at the end of the latency time
	 */
	virtual void end();

	/**
	 * called when brutally stop the phrase
	 */
	virtual void stop();
	//@}

	/// init phrase from a consumbale item
	bool buildFromConsumable(const TDataSetRow & actorRowId, const CStaticItem *itemForm, uint16 quality);

	/// get actor
	inline const TDataSetRow &getActor() const { return _ActorRowId;}
	/// get targets
	const std::vector<TDataSetRow> &getTargets() const { return _Targets; }
	/// get additional recast time
	inline NLMISC::TGameCycle getAdditionalRecastTime() const { return _AddRecastTime; }
	/// get consumable family id
	inline uint16 getConsumableFamilyId() const { return _ConsumableFamilyId; }

private:
	/// process prams (bricks or consumable items)
	virtual void processParams(const std::vector<TBrickParam::IIdPtr> &params, bool isConsumable, uint16 quality);

	/// apply all powers
	void applyPowers();

	/// acting entity
	TDataSetRow					_ActorRowId;	

	/// special power object
	std::vector<CSpecialPower*>	_Powers;

	/// affected entities
	std::vector<TDataSetRow>	_Targets;

	/// additional recast time
	NLMISC::TGameCycle			_AddRecastTime;

	/// flags to bypass some checks
	CBypassCheckFlags			_BypassCheckFlags;

	// consumable family Id
	uint16						_ConsumableFamilyId;
};

#endif // RYZOM_SPECIAL_POWER_PHRASE_H

/* End of special_power_phrase.h */
