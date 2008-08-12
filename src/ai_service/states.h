/** \file states.h
 *
 * $Id: states.h,v 1.32 2007/06/01 11:30:52 dailyserver Exp $
 */



#ifndef RYAI_STATE_H
#define RYAI_STATE_H

#include "state_profil.h"
#include "state_chat.h"
#include "keyword_owner.h"
#include "event_reaction.h"
#include "profile_in_state.h"
#include "ai_share/ai_vector.h"
#include "ai_place_xyr.h"

class CStateMachine;

class CAIState : 
	public	NLMISC::CDbgRefCount<CAIState>,
	public	CKeyWordOwner, 
	public	CAliasChild<CStateMachine>, 
	public	NLMISC::CRefCount,
	public	CProfileInState
{
public:
	
	// ctor & dtor ------------------------------------------------------
	CAIState(const CStateMachine	*container,CAIAliasDescriptionNode *aliasTree)
		: CKeyWordOwner(), 
		CAliasChild<CStateMachine>(const_cast<CStateMachine*>(container),aliasTree)
	{}

	CAIState(CStateMachine const* container, uint32 alias, std::string const& name)
	: CKeyWordOwner()
	, CAliasChild<CStateMachine>(const_cast<CStateMachine*>(container), alias, name)
	{}
	
	virtual ~CAIState()
	{}

	std::string	getIndexString	()	const;

	virtual bool isPositional	()	const	=0;

	// Profile property accessors --------------------------------------

	const CAliasCont<CAIStateProfile>&	profiles() const
	{
		return	_Profiles;
	}

	const CAliasCont<CAIStateChat>&		chats() const
	{
		return	_Chats;
	}
	
	IAliasCont*			getAliasCont		(AITYPES::TAIType	type);
	CAliasTreeOwner*	createChild			(IAliasCont	*cont,	CAIAliasDescriptionNode	*aliasTree);
	void				updateDependencies	(const	CAIAliasDescriptionNode	&aliasTree, CAliasTreeOwner *aliasTreeOwner);

protected:
	CAliasCont<CAIStateProfile>	_Profiles;
	CAliasCont<CAIStateChat>	_Chats;
};

class CAIStatePunctual: public CAIState  
{
public:
	virtual	bool	isPositional	()	const
	{
		return false;
	}
	
	CAIStatePunctual(const CStateMachine	*container,CAIAliasDescriptionNode *aliasTree)
		: CAIState(container,aliasTree) 
	{}

private:
};

class CShape
:public CPlaceRandomPos
{
public:
	CShape(bool acceptInvalidPos=false)
		: _GeometryType(NONE)
		, _AcceptInvalidPos(acceptInvalidPos)
	{}
	virtual	~CShape()
	{}
	
	typedef	RYAI_MAP_CRUNCH::CWorldPosition	TPosition;
	
	// methods for managing geometry
	bool	setPath(AITYPES::TVerticalPos verticalPos, const std::vector <CAIVector> &points);
	
	bool	setPatat(AITYPES::TVerticalPos verticalPos, const std::vector <CAIVector> &points);
	
	// dumb little geometry type reporting accessors
	bool	hasPath		()	const	{ return _GeometryType==PATH && hasPoints(); } 
	bool	hasPatat	()	const	{ return _GeometryType==PATAT && hasPoints(); } 
	bool	hasPoints	()	const	{ return _Geometry.size()!=0; } 
	
	// accessors for path & patat geometry - whichever of the 2 exists
	uint32 numPoints()						{ return _Geometry.size(); }
	const TPosition *point(uint32 idx)		{ return idx<_Geometry.size()? &_Geometry[idx]: NULL; }
	
	const std::vector<TPosition>	&getGeometry()	const { return	_Geometry; }
	
	bool	contains	(const	CAIVector	&pos)	const;

	bool	calcRandomPos(CAIPos &pos)	const;	
	
protected:
private:
	enum { NONE, PATH, PATAT  }	_GeometryType;
	std::vector<TPosition>		_Geometry;
	
	/// bouding box info
	CAIVector	_VMin, _VMax;
	bool	_AcceptInvalidPos;
};

class CAIStatePositional
:public	NLMISC::CDbgRefCount<const CAIStatePositional>
,public	NLMISC::CDbgRefCount<CAIStatePositional>
,public CAIState
{
public:
	CAIStatePositional (const CStateMachine	*container,CAIAliasDescriptionNode *aliasTree) 
	: CAIState(container,aliasTree)
	{
	}
	CAIStatePositional(CStateMachine const* container, uint32 alias, std::string const& name) 
	: CAIState(container, alias, name)
	{
	}
	
	virtual	bool	isPositional	()	const
	{
		return true;
	}
	const std::vector<CShape::TPosition>	&getGeometry()	const
	{
		return	_Shape.getGeometry();
	}
	bool	contains	(const	CAIVector	&pos)	const
	{
		return	_Shape.contains(pos);
	}

	CShape	&shape()
	{
		return	_Shape;
	}

	const	CShape	&shape()	const
	{
		return	_Shape;
	}
	
private:
	CShape	_Shape;
};

#endif

