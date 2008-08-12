/** \file harvest_info.h
 * Information of harvest actions type (harvest and digging)
 *
 * $Id: harvest_info.h,v 1.4 2004/12/08 13:26:42 besson Exp $
 */



#ifndef RY_HARVEST_INFO_H
#define RY_HARVEST_INFO_H


namespace HARVEST_INFOS
{

struct CHarvestInfos
{
	NLMISC::TGameCycle EndCherchingTime;
	NLMISC::CSheetId Sheet;
	uint32	DepositIndex;
	uint32	DepositIndexContent;
	uint16	Quantity;
	uint16	MinQuality;
	uint16	MaxQuality;

	CHarvestInfos() : EndCherchingTime(0xffffffff), DepositIndex(0xffffffff), DepositIndexContent(0), Quantity(0),MinQuality(0),MaxQuality(0)
	{}

	void serial(NLMISC::IStream &f) throw(NLMISC::EStream)
	{
		f.serial( EndCherchingTime );
		f.serial( Sheet );
		f.serial( DepositIndex );
		f.serial( DepositIndexContent );
		f.serial( Quantity );
		f.serial( MinQuality );
		f.serial( MaxQuality );
	}
};

}
#endif // RY_HARVEST_INFO_H
/* End of harvest_info.h */
