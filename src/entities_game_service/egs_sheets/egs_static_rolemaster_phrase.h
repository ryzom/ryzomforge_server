/** \file egs_static_rolemaster_phrase.h
 * <File description>
 *
 * $Id: egs_static_rolemaster_phrase.h,v 1.6 2004/12/08 13:26:46 besson Exp $
 */



#ifndef NL_EGS_STATIC_ROLEMASTER_PHRASE_H
#define NL_EGS_STATIC_ROLEMASTER_PHRASE_H

//Nel georges
#include "nel/georges/u_form.h"


/**
 * <Class description>
 * \author Olivier Cado
 * \author Nevrax France
 * \date 2003
 */
class CStaticRolemasterPhrase
{
public:

	/// Constructor
	CStaticRolemasterPhrase() {}

	/// Read georges sheet
	void readGeorges (const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const NLMISC::CSheetId &sheetId);

	/// Return the version of this class, increments this value when the content of this class has changed
	inline static uint getVersion () { return 4; }

	/// Serial
	void serial(class NLMISC::IStream &f)
	{
		f.serialCont( Bricks );
		std::vector<NLMISC::CSheetId>::const_iterator ib;
		for ( ib=Bricks.begin(); ib!=Bricks.end(); ++ib )
		{
			if ( *ib == NLMISC::CSheetId::Unknown )
				nlwarning( "Serialized brick (in phrase) with unknown sheet id" );
		}
		f.serial( IsRolemasterPhrase );
		f.serial( IsValidPhrase );
		computeMinFameValue();
	}

	/// Removed
	void removed() {}

	/// called to copy from an other sheet (operator= + care ptrs)
	void reloadSheet(const CStaticRolemasterPhrase &o);

public:
	/// Bricks in the phrase
	std::vector<NLMISC::CSheetId>	Bricks;

	/// True if it's a rolemaster phrase, false if it's a bot phrase
	bool							IsRolemasterPhrase;

	/// true if the phrase is a real phrase (and so learnable), false if it's only a brick upgrade
	bool							IsValidPhrase;

	sint32							MinFameValue;

private:
	/// compute the minimum fame value needed to get the phrase
	void computeMinFameValue();
};


#endif // NL_EGS_STATIC_ROLEMASTER_PHRASE_H

/* End of egs_static_rolemaster_phrase.h */
