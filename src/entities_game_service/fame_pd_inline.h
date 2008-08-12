/** \file fame_pd_inline.h
 * 
 * $Id: fame_pd_inline.h,v 1.10 2005/04/05 13:41:50 fleury Exp $
 */

namespace EGSPD
{
	
/* -----------------------------------------
* Inline implementation of CFameTrend
* ----------------------------------------- */
inline const std::string&		CFameTrend::toString(TFameTrend v)
{
	if (v < 0 || v >= ___TFameTrend_useSize)
	{
		nlwarning("TFameTrend::toString(): value '%u' is not matched, \"Unknown\" string returned", v);
		return _UnknownString;
	}
	if (!_Initialised)
	{
		init();
	}
	return _StrTable[v];
}
inline CFameTrend::TFameTrend	CFameTrend::fromString(const std::string& v)
{
	if (!_Initialised)
	{
		init();
	}
	if(v==_UnknownString)
	{
		return Unknown;
	}
	const std::map<std::string, TFameTrend>::const_iterator	it = _ValueMap.find(NLMISC::toLower(v));
	if (it == _ValueMap.end())
	{
		nlwarning("TFameTrend::toString(): string '%s' is not matched, 'Unknown' enum value returned", v.c_str());
		return Unknown;
	}
	return (*it).second;
}
// End of inline implementation of CFameTrend

/* -----------------------------------------
* Inline implementation of CFameContainerEntryPD
* ----------------------------------------- */
inline CFameContainerEntryPD::CFameContainerEntryPD()
{
	__BaseTable = 0;
}
inline CFameContainerEntryPD::~CFameContainerEntryPD()
{
}
// End of inline implementation of CFameContainerEntryPD

/* -----------------------------------------
* Inline implementation of CFameContainerPD
* ----------------------------------------- */
inline CFameContainerPD::CFameContainerPD()
{
	__BaseTable = 1;
}
inline CFameContainerPD::~CFameContainerPD()
{
}
// End of inline implementation of CFameContainerPD

/* -----------------------------------------
* Inline implementation of CGuildFameContainerPD
* ----------------------------------------- */
inline CGuildFameContainerPD::CGuildFameContainerPD()
{
	__BaseTable = 2;
}
inline CGuildFameContainerPD::~CGuildFameContainerPD()
{
}
// End of inline implementation of CGuildFameContainerPD

	
} // End of EGSPD
