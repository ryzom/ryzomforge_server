/** \file egs_static_emot.h
 * <File description>
 *
 * $Id: egs_static_emot.h,v 1.1 2005/07/06 12:13:33 vuarand Exp $
 */



#ifndef EGS_STATIC_EMOT_H
#define EGS_STATIC_EMOT_H

//Nel georges
#include "nel/georges/u_form.h"


/**
 * class used to store emote animation list
 * \author Jerome Vuarand
 * \author Nevrax France
 * \date 2005
 */
class CStaticEmot
{
public:
	/// ctor
	CStaticEmot() { }

	/// Read georges sheet
	void readGeorges (const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const NLMISC::CSheetId &sheetId);
	/// Return the version of this class, increments this value when the content of this class has changed
	inline static uint getVersion () { return 1; }
	/// Serial
	void serial(class NLMISC::IStream &f)
	{
		f.serialCont( _Anims );
		if (f.isReading())
			buildAnimIdMap();
	}
	
	uint16 getAnimIndex(const std::string& animId) const
	{
		std::map<std::string, size_t>::const_iterator it = _AnimIdMap.find(animId);
		if (it!=_AnimIdMap.end())
			return it->second;
		return (uint16)~0;
	}
	
	/// Removed
	void removed() { }
	
private:
	void buildAnimIdMap();
	
private:		
	/// all emote animations, ordered by (behav) integer id
	std::vector< std::string > _Anims;
	/// mapping of string id to integer id (index in _Anims)
	std::map<std::string, size_t> _AnimIdMap;
};



#endif
