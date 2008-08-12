/** \file bypass_check_flags.h
 * 
 *
 * $Id: bypass_check_flags.h,v 1.2 2004/12/08 13:26:46 besson Exp $
 */



#ifndef RY_BYPASS_CHECK_FLAGS_H
#define RY_BYPASS_CHECK_FLAGS_H



namespace CHECK_FLAG_TYPE
{
	enum TCheckFlagType
	{
		WhileSitting = 0,
		InWater,
		OnMount,
		Fear,
		Sleep,
		Invulnerability,
		Stun,

		Unknown,
	};

	const std::string &toString(TCheckFlagType type);
	
	TCheckFlagType fromString(const std::string &str);
}

/**
 * CBypassCheckFlags used to enable/disable check for canEntityUseAction() method of CEntityBase
 * \author Fleury David
 * \author Nevrax France
 * \date 2004
 */
struct CBypassCheckFlags
{
public:
	union
	{
		uint8 RawFlags;

		struct
		{
			uint8	WhileSitting : 1;
			uint8	InWater : 1;
			uint8	OnMount : 1;
			uint8	Fear : 1;
			uint8	Sleep : 1; // = Mezz
			uint8	Invulnerability : 1;
			uint8	Stun : 1;

			uint8	Unused : 1;
		} Flags;
	};

	inline CBypassCheckFlags()
	{
		RawFlags = 0;
	}

	// set/reset flag from enum
	void setFlag( CHECK_FLAG_TYPE::TCheckFlagType type, bool on );

	static CBypassCheckFlags NoFlags;
};

#endif // RY_BYPASS_CHECK_FLAGS_H
