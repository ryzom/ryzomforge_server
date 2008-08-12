/** \file egs_static_xp_factor_table.h
 *
 * $Id: egs_static_xp_factor_table.h,v 1.3 2004/12/08 13:26:46 besson Exp $
 */



#ifndef RY_EGS_STATIC_XPFACTOR_TABLE_H
#define RY_EGS_STATIC_XPFACTOR_TABLE_H


// Nel georges
#include "nel/georges/u_form.h"
// game share
#include "game_share/constants.h"


/**
 * class for xp factor table
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CStaticXpFactorTable
{
public:	
	/// Serialisation
	virtual void serial(class NLMISC::IStream &f);
	
	/// read georges sheet
	void readGeorges (const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const NLMISC::CSheetId &sheetId);
	
	// return the version of this class, increments this value when the content of this class has changed
	inline static uint getVersion () { return 1; } 
	
	/// called when the sheet is removed
	void removed() {}

	/// get factor for a given number of actions (1..255)
	inline float getXpFactor(uint8 nbActions) const 
	{
#if !FINAL_VERSION
		nlassert(_XpFactorTable.size());
		nlassert(nbActions);
#endif
		--nbActions;
		if (nbActions < _XpFactorTable.size())
			return _XpFactorTable[nbActions];
		else
			return _XpFactorTable[_XpFactorTable.size()-1];
	}

public:
	/// table lines
	std::vector< float >	_XpFactorTable;
};

#endif // RY_EGS_STATIC_XPFACTOR_TABLE_H

/* End of egs_static_xp_factor_table.h */





















