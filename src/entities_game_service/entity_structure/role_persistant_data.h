/** \role_persistant_data.h
 * 
 *
 * $Id: role_persistant_data.h,v 1.5 2004/12/08 13:26:48 besson Exp $
 */



#ifndef RY_ROLE_PERSISTANT_DATA_H
#define RY_ROLE_PERSISTANT_DATA_H
//
//stdpch //#include "nel/misc/types_nl.h"
//#include "nel/misc/stream.h"
//
////#include "game_share/jobs.h"
//#include "game_share/skills.h"
//
//
//class CRolePersistantData
//{
//public:
//	/// Constructor
//	CRolePersistantData();
//
//	struct SSkillsProgress
//	{
//		uint16 LevelReached;
//		uint16 SkillCap;
//		
//		SSkillsProgress() { LevelReached = SkillCap = 0; }
//		
//		void serial(NLMISC::IStream &f) throw(NLMISC::EStream)
//		{
//			f.serial( LevelReached );
//			f.serial( SkillCap );
//		}
//	};
//	
//	typedef std::map< std::string, SSkillsProgress > TSkillLevelReachedContainer;
//	
//	struct SRole
//	{
//		JOBS::TJob			Job;
//		JOBS::TJobStatus	JobStatus;
//		NLMISC::TGameCycle	BeginFreezeTime;
//		NLMISC::TGameCycle	UnfreezeTime;
//		uint16				JobLevel;
//		NLMISC::CSheetId	RoleSheet;
//		
//		void serial(NLMISC::IStream &f) throw(NLMISC::EStream)
//		{
//			f.serialEnum( Job );
//			f.serialEnum( JobStatus );
//			f.serial( BeginFreezeTime );
//			f.serial( UnfreezeTime );
//			f.serial( JobLevel );
//			std::string sheetName;
//			if( f.isReading() )
//			{
//				f.serial( sheetName );
//				RoleSheet = NLMISC::CSheetId( sheetName );
//			}
//			else
//			{
//				sheetName = RoleSheet.toString();
//				f.serial( sheetName );
//			}
//		}
//	};	
//	
//	// Serial
//	void serial(NLMISC::IStream &f) throw(NLMISC::EStream)
//	{
//		f.serialCont( _Roles );
//		f.serialCont( _LevelReached );
//	}
//
//	//public attributes
//	std::vector< SRole > _Roles;
//	TSkillLevelReachedContainer _LevelReached; 
//
//}; //CRolePersistantData

#endif // RY_ROLE_PERSISTANT_DATA_H
/* role_persistant_data.h */
