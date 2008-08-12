/** \file sheets.h
 *
 * $Id: sheets.h,v 1.5 2006/09/21 10:22:12 coutelas Exp $
 */



#ifndef RY_CMS_SHEETS_H
#define RY_CMS_SHEETS_H

#include "nel/misc/types_nl.h"
#include "nel/misc/smart_ptr.h"
#include "nel/misc/sheet_id.h"

///Nel Georges
#include "nel/georges/u_form.h"
#include "nel/georges/u_form_elm.h"


/**
 * Singleton containing database on information for actors
 * \author Sadge
 * \author Nevrax France
 * \date 2002
 */
class CSheets
{
public:
	class CSheet
	{
	public:
		CSheet(): WalkSpeed(1.3f), RunSpeed(6.0f), Radius(0.5f), Height(2.0f), BoundingRadius(0.5), Scale(1.0f) {}

		float	WalkSpeed;
		float	RunSpeed;
		float	Radius;				// pacs primitive's radius
		float	Height;				// pacs primitive's height
		float	BoundingRadius;		// fighting radius
		float	Scale;				// entity scale

		void readGeorges (const NLMISC::CSmartPtr<NLGEORGES::UForm> &form, const NLMISC::CSheetId &sheetId)
		{
			// the form was found so read the true values from George
			form->getRootNode ().getValueByName (WalkSpeed, "Basics.MovementSpeeds.WalkSpeed");
			form->getRootNode ().getValueByName (RunSpeed, "Basics.MovementSpeeds.RunSpeed");
			form->getRootNode ().getValueByName (Radius, "Collision.CollisionRadius");
			form->getRootNode ().getValueByName (Height, "Collision.Height");
			form->getRootNode ().getValueByName (BoundingRadius, "Collision.BoundingRadius");
			form->getRootNode ().getValueByName (Scale, "3d data.Scale");
		}

		void serial (NLMISC::IStream &s)
		{
			s.serial (WalkSpeed, RunSpeed, Radius, Height, BoundingRadius, Scale);
		}

		static uint getVersion () { return 1; }
		
		void removed() {}
	};

	// load the creature data from the george files
	static void init();

	// display the creature data for all known creature types
	static void display();

	//
	static void release() {}
	

	// get a data record from the database
	static const CSheet *lookup( NLMISC::CSheetId id );

private:
	// prohibit cnstructor as this is a singleton
	CSheets();

	static std::map<NLMISC::CSheetId,CSheet> _sheets;
	static bool _initialised;
};


#endif // RY_CMS_SHEETS_H
