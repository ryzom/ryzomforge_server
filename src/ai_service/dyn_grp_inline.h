/** \file dyn_grp_inline.h
 *
 * $Id: dyn_grp_inline.h,v 1.2 2005/01/25 20:12:01 vuarand Exp $
 */



#ifndef DYN_GRP_INLINE_H
#define DYN_GRP_INLINE_H

inline
CDynGrpBase::CDynGrpBase()
: _Discardable(true)
{
}

inline
CDynGrpBase::~CDynGrpBase()
{
	if	(	_GroupDesc
		&&	!_FamilyBehavior.isNULL())
		_FamilyBehavior->_TheoricalLevel-=_GroupDesc->groupEnergyValue();
}

inline
void CDynGrpBase::initDynGrp(IGroupDesc const* const gd, CFamilyBehavior const* const familyBehavior)
{
	if	(	_GroupDesc
		&&	!_FamilyBehavior.isNULL())
		_FamilyBehavior->_TheoricalLevel -= _GroupDesc->groupEnergyValue();
	
	_GroupDesc = gd;
	_FamilyBehavior = familyBehavior;
	
	if	(	_GroupDesc
		&&	!_FamilyBehavior.isNULL())
		_FamilyBehavior->_TheoricalLevel += _GroupDesc->groupEnergyValue();
}

inline
void CDynGrpBase::setDiscardable(bool discardable) const
{
	_Discardable = discardable;
}

inline
bool CDynGrpBase::getDiscardable() const
{
	return _Discardable;
}

inline
NLMISC::CSmartPtr<IGroupDesc const> const& CDynGrpBase::getGroupDesc() const
{
	return _GroupDesc;
}

inline
NLMISC::CDbgPtr<CFamilyBehavior> const& CDynGrpBase::getFamilyBehavior() const
{
	return	_FamilyBehavior;
}

inline
float CDynGrpBase::getEnergyCoef() const
{
	if (!getDiscardable())
		return	0.f;
	
	if (getGroupDesc()==NULL)
		return	1.f;
	
	return getGroupDesc()->groupEnergyCoef();
}

inline
bool CDynGrpBase::getCountMultiplierFlag() const
{
	if (!_GroupDesc.isNull())
		return _GroupDesc->getCountMultiplierFlag();
	else
		return false;
}

#endif
