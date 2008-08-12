/** \file pvp.h
 * 
 *
 * $Id: pvp.h,v 1.16 2006/01/10 17:38:58 boucher Exp $
 */



#ifndef RY_PVP_H
#define RY_PVP_H

#include "pvp_base.h"
#include "game_share/pvp_clan.h"

class CEntityBase;
class CCharacter;

/**
 * user-pvp interface 
 * \author Nicolas Brigand
 * \author Nevrax France
 * \date 2004
 */
class CPVPInterface
{
	friend class CPVPManager;

	NL_INSTANCE_COUNTER_DECL(CPVPInterface);
public:

	/// ctor
	CPVPInterface(CCharacter * owner);

	/// init with a PVP session
	void init(IPVP * pvpSession)
	{
		_PVPSession = pvpSession;
		setPVPModeInMirror();
	}

	/// reset PVP session
	void reset()
	{
		_PVPSession = NULL;
		setPVPModeInMirror();
	}

	/// returns true if PVP session is valid
	bool isValid() const
	{
		return _PVPSession != NULL;
	}

	/// call this when user leaves PVP
	bool leavePVP(IPVP::TEndType type);

	/// returns true if the PVP session respawns players itself
	bool doCancelRespawn();

	/// returns true if owner can hurt target
	bool canHurt(CEntityBase * target) const;

	/// returns true if owner can help target
	bool canHelp(CEntityBase * target) const;

	/// returns true if owner area effect can be applied on areaTarget
	bool canApplyAreaEffect(CEntityBase * areaTarget, bool offensive, bool ignoreMainTarget) const;

	/// call this when owner hurts another player
	void hurt(CCharacter * target);

	/// call this when player is killed. Returns true if the kill is eligible for PVP death penalty factor.
	bool killedBy(CEntityBase * killer);

	/**
	 *	Return clan concerned by pvp versus zone
	 * \param clan1 is the first clan concerned by pvp versus
	 * \param clan2 is the second clan concerned by pvp versus
	 * \return true if character are in pvp versus zone & clan1 & clan2 are setted, false if character are not in versus zone
	 */
	bool getPvpClan( PVP_CLAN::TPVPClan& clan1, PVP_CLAN::TPVPClan& clan2 ) const;

	/// returns the current PVP session
	const IPVP * getPVPSession() const { return &*_PVPSession; }

	/// returns the current PVP session
	IPVP * getPVPSession() { return &*_PVPSession; }

private:
	/// set PVP mode in mirror
	void setPVPModeInMirror() const;

private:
	CCharacter * const			_Owner;
	NLMISC::CSmartPtr<IPVP>		_PVPSession;
};

#endif // RY_PVP_H

