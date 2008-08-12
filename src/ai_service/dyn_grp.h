/** \file dyn_grp.h
 *
 * $Id: dyn_grp.h,v 1.27 2005/01/25 20:12:01 vuarand Exp $
 */



#ifndef DYN_GRP_H
#define DYN_GRP_H

#include "continent.h"

//////////////////////////////////////////////////////////////////////////////
// CDynGrpBase                                                              //
//////////////////////////////////////////////////////////////////////////////

class CDynGrpBase
{
public:
	CDynGrpBase();
	virtual ~CDynGrpBase();
	
	void initDynGrp(IGroupDesc const* const gd, CFamilyBehavior const* const familyBehavior);
	
	void setDiscardable(bool discardable) const;
	bool getDiscardable() const;
	
	NLMISC::CSmartPtr<IGroupDesc const> const& getGroupDesc() const;
	
	NLMISC::CDbgPtr<CFamilyBehavior> const& getFamilyBehavior() const;
	
	float getEnergyCoef() const;
	
	bool getCountMultiplierFlag() const;
		
protected:	
	/** Flag for group discardability.
	 *	If this flag is set, then the group can be despawn when
	 *	the family spawned energy is to high.
	 *	When cleared, the group cannot be despawned automaticaly
	 *	either for enegy reason nor for unadequate energy level.
	*/
	mutable	bool							_Discardable;
	/// The dynamic group model
	NLMISC::CSmartPtr<IGroupDesc const>		_GroupDesc;

	/// The family this group belong to
	NLMISC::CDbgPtr<CFamilyBehavior>		_FamilyBehavior;
};

//////////////////////////////////////////////////////////////////////////////
// CDynBot                                                                  //
//////////////////////////////////////////////////////////////////////////////

class CDynBot
{
public:
	CDynBot()	: _BotEnergyValue(0)
	{}
	virtual	~CDynBot()
	{}
	/// The energy value of this bot.

	const	uint32	&botEnergyValue	()	const
	{
		return	_BotEnergyValue;
	}

	void	setBotEnergyValue	(const	uint32	&energyValue)
	{
		_BotEnergyValue=energyValue;
	}

	virtual	void	addEnergy()		const	=	0;
	virtual	void	removeEnergy()	const	=	0;

private:
	uint32	_BotEnergyValue;
};

class CDynSpawnBot
{
public:
	CDynSpawnBot(const	CDynBot	&dynBot)	:	_DynBot(dynBot)
	{
		_DynBot.addEnergy();
	}

	virtual	~CDynSpawnBot()
	{
		_DynBot.removeEnergy();
	}

private:
	const	CDynBot	&_DynBot;
};


#endif
