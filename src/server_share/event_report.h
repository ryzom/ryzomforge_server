/** \file event_report.h
 * 
 *
 * $Id: event_report.h,v 1.10 2004/03/01 19:21:53 lecroart Exp $
 */



#ifndef RY_EVENT_REPORT_H
#define RY_EVENT_REPORT_H

#include "nel/misc/types_nl.h"
#include "nel/misc/stream.h"

#include "game_share/action_nature.h"


/*

	NOTE
	----

	SEventReport is the structure used by the brick service event report message
	format:
		"EVENT_REPORTS"
		std::list<SEventReport>

    Subscription for event reports via message:
		"REGISTER_EVENT_REPORTS"

    Unsubscription via message:
		"UNREGISTER_EVENT_REPORTS"

*/

/**
 * Structure for event reports sent by the Brick Service
 * \author David Fleury
 * \author Nevrax France
 * \date 2002
 */
struct SEventReport
{
	NLMISC::CEntityId			ActingEntity;
	NLMISC::CEntityId			TargetEntity;
	ACTNATURE::TActionNature	Nature;
	sint32						DeltaLevel;
	std::string					Skill;
	std::string					Specialization;
	bool						Success;
	bool						FullResist;
	
	/// to String
	std::string toString() const
	{
		char buffer[512];
		sprintf( buffer, "Actor %s, Target %s. Delta Level = %d, skill = %s, spe = %s. Success = %s, FullResist = %s", ActingEntity.toString().c_str(), TargetEntity.toString().c_str(), DeltaLevel, Skill.c_str(), Specialization.c_str(), (Success?"yes":"no"),(FullResist?"yes":"no") );
		return std::string(buffer);
	}

	/// Serialisation
	void serial(class NLMISC::IStream &f) throw(NLMISC::EStream)
	{
		f.serial( ActingEntity );
		f.serial( TargetEntity );
		f.serialEnum( Nature );
		f.serial( DeltaLevel );
		f.serial( Skill );
		f.serial( Specialization );
		f.serial( Success );
		f.serial( FullResist );		
	}
};

#endif // RY_EVENT_REPORT_H
/* End of event_report.h */


