/** \file timed_action_phrase.h
 * 
 *
 * $Id: timed_action_phrase.h,v 1.6 2005/02/22 10:22:29 besson Exp $
 */



#ifndef RYZOM_TIMED_ACTION_PHRASE_H
#define RYZOM_TIMED_ACTION_PHRASE_H

#include "phrase_manager/s_phrase.h"
#include "timed_actions.h"
//
#include "game_share/client_action_type.h"


/**
 * This class represents a sabrina phrase used for special powers such as auras
 * \author David Fleury
 * \author Nevrax France
 * \date 2003
 */
class CTimedActionPhrase : public CSPhrase
{
public:

	/// ctor
	CTimedActionPhrase();

	/// dtor
	virtual ~CTimedActionPhrase();

	/// \name Override methods from CSPhrase
	//@{
	virtual bool build( const TDataSetRow & actorRowId, const std::vector< const CStaticBrick* >& bricks, bool buildToExecute = true );

	/**
	 * evaluate phrase
	 * \return true if eval has been made without errors
	 */
	virtual bool evaluate();
	
	/**
	 * validate phrase
	 * \return true if phrase is valid
	 */
	virtual bool validate();
	virtual bool update();
	virtual void execute();
	virtual bool launch();
	virtual void apply();
	
	/**
	 * called at the end of the latency time
	 */
	virtual void end();

	/**
	 * called when brutally stop the phrase
	 */
	virtual void stop();

	/**
	 * called for brutal stop of the phrase before it's execution
	 */
	virtual void stopBeforeExecution();
	//@}

	/// test if action is canceled when actor is being hit, return true if canceled
	bool testCancelOnHit( sint32 attackSkillValue, CEntityBase * entity, CEntityBase * defender);

	/**
	 * set the primary target
	 * \param entityId id of the primary target
	 */
	virtual void setPrimaryTarget( const TDataSetRow &entityRowId ) { _TargetRowId = entityRowId; }

	/// get target
	inline const TDataSetRow &getTarget() const { return _TargetRowId; }

private:
	/// acting entity
	TDataSetRow				_ActorRowId;

	/// target id
	TDataSetRow				_TargetRowId;

	/// a pointer to the action to execute
	CTimedAction *			_TimedAction;

	/// execution duration
	NLMISC::TGameCycle		_ExecutionDuration;

	/// client action type
	CLIENT_ACTION_TYPE::TClientActionType _ActionType;

	/// root sheet id
	NLMISC::CSheetId		_RootSheetId;
};

#endif // RYZOM_TIMED_ACTION_PHRASE_H

/* End of timed_action_phrase.h */
