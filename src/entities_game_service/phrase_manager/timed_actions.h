/** \file timed_actions.h
 * <File description>
 *
 * $Id: timed_actions.h,v 1.10 2006/10/09 15:25:31 saffray Exp $
 */


#ifndef RY_TIMED_ACTIONS_H
#define RY_TIMED_ACTIONS_H


class CEntityBase;
class CGameItemPtr;
class CTimedActionPhrase;


class CStaticItem;

/**
 * Timed action base class
 * \author David Fleury
 * \author Nevrax France
 * \date 2004
 */
class CTimedAction
{
	NL_INSTANCE_COUNTER_DECL(CTimedAction);

	enum TFamily
	{
		Teleport,
		Disconnect,

		Unknown,
	};

public:
	/// \ctor
	CTimedAction() {}
	
	/// \dtor
	virtual ~CTimedAction() {}

	/// validate action
	virtual bool validate(CTimedActionPhrase *phrase, CEntityBase *actor) = 0;

	/// apply action
	virtual void applyAction(CTimedActionPhrase *phrase, CEntityBase *actor) = 0;

	/// stop action
	virtual void stopAction(CTimedActionPhrase *phrase, CEntityBase *actor) = 0;

	/// stop action before execution of the phrase
	virtual void stopBeforeExecution(CTimedActionPhrase *phrase, CEntityBase *actor) {}

	/// test if action is canceled when actor is being hit, return true if canceled
	virtual bool testCancelOnHit( sint32 attackSkillValue, CEntityBase * entity, CEntityBase * defender);

private:
	/// family
//	TFamily		_Family;
};


/**
 * Timed action specialized class for Teleport
 * \author David Fleury
 * \author Nevrax France
 * \date 2004
 */
class CTPTimedAction : public CTimedAction
{
public:
	/// \ctor
	CTPTimedAction() {}
	
	/// \dtor
	virtual ~CTPTimedAction() {}

	/// validate action
	virtual bool validate(CTimedActionPhrase *phrase, CEntityBase *actor);
	
	/// apply action
	virtual void applyAction(CTimedActionPhrase *phrase, CEntityBase *actor);

	/// stop action
	virtual void stopAction(CTimedActionPhrase *phrase, CEntityBase *actor);

	/// stop action before execution of the phrase
	virtual void stopBeforeExecution(CTimedActionPhrase *phrase, CEntityBase *actor) { stopAction(phrase,actor); }

private:
	/// get and unlock TP item
	CGameItemPtr getAndUnlockTP(CEntityBase *actor);
};


/**
 * Timed action specialized class for Disconnection
 * \author David Fleury
 * \author Nevrax France
 * \date 2004
 */
class CDisconnectTimedAction : public CTimedAction
{
public:
	/// \ctor
	CDisconnectTimedAction() {}
	
	/// \dtor
	virtual ~CDisconnectTimedAction() {}

	/// validate action
	virtual bool validate(CTimedActionPhrase *phrase, CEntityBase *actor);
	
	/// apply action
	virtual void applyAction(CTimedActionPhrase *phrase, CEntityBase *actor);

	/// stop action
	virtual void stopAction(CTimedActionPhrase *phrase, CEntityBase *actor);

	/// stop action before execution of the phrase
	virtual void stopBeforeExecution(CTimedActionPhrase *phrase, CEntityBase *actor);
};


/**
 * Timed action specialized class for mounting a Mektoub
 * \author David Fleury
 * \author Nevrax France
 * \date 2004
 */
class CMountTimedAction : public CTimedAction
{
public:
	/// \ctor
	CMountTimedAction() {}
	
	/// \dtor
	virtual ~CMountTimedAction() {}

	/// validate action
	virtual bool validate(CTimedActionPhrase *phrase, CEntityBase *actor);
	
	/// apply action
	virtual void applyAction(CTimedActionPhrase *phrase, CEntityBase *actor);

	/// stop action
	virtual void stopAction(CTimedActionPhrase *phrase, CEntityBase *actor);

	/// stop action before execution of the phrase
	virtual void stopBeforeExecution(CTimedActionPhrase *phrase, CEntityBase *actor);

private:
	// entity to mount
	TDataSetRow		_EntityToMount;
};

/**
 * Timed action specialized class for unmounting a Mektoub
 * \author David Fleury
 * \author Nevrax France
 * \date 2004
 */
class CUnmountTimedAction : public CTimedAction
{
public:
	/// \ctor
	CUnmountTimedAction() {}
	
	/// \dtor
	virtual ~CUnmountTimedAction() {}

	/// validate action
	virtual bool validate(CTimedActionPhrase *phrase, CEntityBase *actor);
	
	/// apply action
	virtual void applyAction(CTimedActionPhrase *phrase, CEntityBase *actor);

	/// stop action
	virtual void stopAction(CTimedActionPhrase *phrase, CEntityBase *actor);

	/// stop action before execution of the phrase
	virtual void stopBeforeExecution(CTimedActionPhrase *phrase, CEntityBase *actor);

	/// test if action is canceled when actor is being hit, return true if canceled
	virtual bool testCancelOnHit( sint32 attackSkillValue, CEntityBase * attacker, CEntityBase * defender) { return false; }
};


/**
 * Timed action specialized class for consumming an item
 * \author David Fleury
 * \author Nevrax France
 * \date 2004
 */
class CConsumeItemTimedAction : public CTimedAction
{
public:
	/// \ctor
	CConsumeItemTimedAction() { _Form = 0; }
	
	/// \dtor
	virtual ~CConsumeItemTimedAction() {}

	/// validate action
	virtual bool validate(CTimedActionPhrase *phrase, CEntityBase *actor);
	
	/// apply action
	virtual void applyAction(CTimedActionPhrase *phrase, CEntityBase *actor);

	/// stop action
	virtual void stopAction(CTimedActionPhrase *phrase, CEntityBase *actor);

	/// stop action before execution of the phrase
	virtual void stopBeforeExecution(CTimedActionPhrase *phrase, CEntityBase *actor);

	/// test if action is canceled when actor is being hit, return true if canceled
	virtual bool testCancelOnHit( sint32 attackSkillValue, CEntityBase * attacker, CEntityBase * defender);

private:
	const CStaticItem *_Form;
};


#endif // RY_TIMED_ACTIONS_H


/* End of timed_actions.h */
