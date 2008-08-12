/** \totem_effect.h
 * 
 *
 * $Id: 
 */

#ifndef TOTEM_EFFECT_H
#define TOTEM_EFFECT_H

#include "phrase_manager/s_effect.h"
#include "game_share/characteristics.h"

/**
 * Class representing an effect produced 
 * by a totem in faction PVP
 * \author Gregorie Diaconu
 * \author Nevrax France
 * \date 2005
 */
class CTotemEffect : public CSEffect
{
public :
	///\ctor
	CTotemEffect(	const TDataSetRow & creatorRowId,
					const TDataSetRow & targetRowId,
					EFFECT_FAMILIES::TEffectFamily family,
					sint32 effectValue
				) : CSEffect( creatorRowId, targetRowId, family, false, effectValue, 0)
	{}

	/**
	 * apply the effects of the... effect
	 * \return true if effects ends
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);
	
	/// callback called when the effect is actually removed
	virtual void removed();

	/// change the parameter value
	inline void setParamValue( sint32 value ) { _Value = value; } 
};


/**
 * Class representing an effect produced 
 * by a totem in faction PVP which affects physical 
 * characteristics
 * \author Gregorie Diaconu
 * \author Nevrax France
 * \date 2005
 */
class CTotemCharacEffect : public CTotemEffect
{
private :
	CHARACTERISTICS::TCharacteristics	_AffectedCharac;
	
public:
	///\ctor
	CTotemCharacEffect(	const TDataSetRow & creatorRowId,
						const TDataSetRow & targetRowId,
						EFFECT_FAMILIES::TEffectFamily family,
						sint32 effectValue );

	/**
	 * apply the effects of the... effect
	 * \return true if effects ends
	 */
	virtual bool update(CTimerEvent * event, bool applyEffect);
	
	/// callback called when the effect is actually removed
	virtual void removed();
};

#endif // TOTEM_EFFECT_H
