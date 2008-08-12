/** \file deposit_raw_material.h
 * One raw material in deposit parameters
 *
 * $Id: deposit_raw_material.h,v 1.7 2004/12/08 13:26:42 besson Exp $
 */



#ifndef RY_DEPOSIT_RAW_MATERIAL_H
#define RY_DEPOSIT_RAW_MATERIAL_H

// Struct deposit parameters
struct CDepositRawMaterial
{
	NLMISC::CSheetId	MaterialSheet;
	//uint16				MaxAmount;

	// defined operator = to fill structure with CStaticDeposit::CStaticDepositRawMaterial
	const CDepositRawMaterial &operator = (const CStaticDeposit::CStaticDepositRawMaterial& form )
	{
		MaterialSheet = form.MaterialSheet;
		//MaxAmount = form.MaxAmount;
		return *this;
	}

	/// serialize
//	void serial(class NLMISC::IStream &f) throw(NLMISC::EStream) 
//	{
//	}
};

#endif // RY_DEPOSIT_RAW_MATERIAL_H

/* End of deposit_raw_material.h */
