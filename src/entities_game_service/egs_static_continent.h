/** \file egs_static_continent.h
 * <File description>
 *
 * $Id: egs_static_continent.h,v 1.2 2004/12/08 13:26:42 besson Exp $
 */

#ifndef RY_EGS_STATIC_CONTINENT_H
#define RY_EGS_STATIC_CONTINENT_H

//Nel georges
#include "nel/georges/u_form.h"
#include "nel/georges/u_form_elm.h"
#include "nel/georges/load_form.h"


class CStaticWorld
{
public:
	/// Serialisation
	void serial(class NLMISC::IStream &f);
	
	/// read georges sheet
	void readGeorges (const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const NLMISC::CSheetId &sheetId);
	
	// return the version of this class, increments this value when the content of this class has changed
	inline static uint getVersion () { return 1; }
	
	/// called when the sheet is removed
	void removed() {}


	std::vector<

};



#endif // RY_EGS_STATIC_CONTINENT_H

/* End of egs_static_continent.h */






















