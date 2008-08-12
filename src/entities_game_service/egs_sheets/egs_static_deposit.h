/** \file egs_static_deposit.h
 * <File description>
 *
 * $Id: egs_static_deposit.h,v 1.4 2004/12/08 13:26:46 besson Exp $
 */



#ifndef RYZOM_STATIC_DEPOSIT_H
#define RYZOM_STATIC_DEPOSIT_H

//Nel georges
#include "nel/georges/u_form.h"
#include "nel/georges/u_form_elm.h"
#include "nel/georges/load_form.h"
// std
#include <vector>

// TEMP
typedef uint32 TTerrain;


/*
 * Struct deposit parameters
 */
class CStaticDepositRawMaterial
{
public:
	NLMISC::CSheetId	MaterialSheet;
	//uint16				MaxAmount;

	void serial(class NLMISC::IStream &f) throw(NLMISC::EStream)
	{
		f.serial( MaterialSheet );
		//f.serial( MaxAmount );
	}
};


/**
 * CStaticDeposit
 *
 * \author Alain Saffray, Olivier Cado
 * \author Nevrax France
 * \date 2002-2003
 */
/*class CStaticDeposit
{
public :
		
	/// read sheet
	virtual void readGeorges( const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const NLMISC::CSheetId &sheetId );
	
	// return the version of this class, increments this value when the content of this class changed
	static uint getVersion () { return 3; }
	
	/// destructor
	virtual ~CStaticDeposit() {}
	
	/// called when the sheet is removed
	void removed() {}
	
	/// Serialize deposit
	void serial(class NLMISC::IStream &f) throw(NLMISC::EStream)
	{}		
};*/

#endif // RYZOM_STATIC_DEPOSIT_H

/* End of static_deposit.h */
