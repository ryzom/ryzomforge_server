/** \file team_manager.h
 * manages the temporary team of a player
 *
 * $Id: team_manager.h,v 1.25 2005/11/25 14:34:22 saffray Exp $
 */



#ifndef TEAM_MANAGER_H
#define TEAM_MANAGER_H

// misc
#include "game_share/ryzom_entity_id.h"

// EGS
#include "team_manager/team.h"


class CCharacter;


///\todo: avoid team reallocation problems?
///\todo: check if we have to remove team from IOS if crash/shutdown
///\todo successor index sert à rien???

/**
 * CTeamManager
 *
 * \author Stephane Coutelas
 * \author Nevrax France
 * \date 2002
 */
class CTeamManager
{
public:
	enum TInviteRetCode
	{
		AlreadyInvited,
		AlreadyInTeam,
		CantInviteEnemy,
		CantInvite,
		Ok,
	};
	/// default constructor
	CTeamManager()
		:_FirstFreeTeamId(0),_TeamAllocStep(128){}

	/// add all created to chat groups
	void addAllTeamsToChatGroup();

	/// player leaderId invites plyer targetId to join his team. Only leaders can invite
	void joinProposal( CCharacter * leader, const NLMISC::CEntityId &targetId );

	/// player charId declines an invitation
	void joinDecline( const NLMISC::CEntityId &charId );

	/// player charId accepts an invitation
	void joinAccept( const NLMISC::CEntityId &charId );

	/// a character quits its team
	void quitTeam( const NLMISC::CEntityId &charId );

	/**
	 * remove the specified character from his team
	 * \param charId id of the character
	 */
	void removeCharacter( const NLMISC::CEntityId &charId );
	/**
	 * remove the specified character from his team, check the kicking char is the team leader
	 * \param leader the character kicking (should be the team leader)
	 * \param memberIndex index of the kicked character in the leader team list
	 */
	void kickCharacter( CCharacter * leader,uint8 memberIndex );


	/// remove a team from the manager
	void removeTeam( uint16 teamId );

	/// add a fake team to this player
	void addFakeTeam(CCharacter * player);

	/// remove a fake team to this player
	void removeFakeTeam(CCharacter * player);

	///\return a pointer on a team, NULL if invalid
	CTeam* getTeam(uint16 id);
	///\return a pointer on a team, NULL if invalid or fake
	CTeam* getRealTeam(uint16 id);

	/**
	 * \param invited: character being invited
	 * \param invitor: character inviting the other one
	 * \return true if the invited is invitable by the invitor
	 */
	TInviteRetCode isInvitableBy(CCharacter * invited, CCharacter * invitor );

	/**
	 * PvP attack occurs in a team
	 * \param actor is the attacker character
	 * \param target is the victime character
	 */
	void pvpAttackOccursInTeam( CCharacter * actor, CCharacter * target );

	/**
	 * PvP help occurs in a team
	 * \param actor is the helper
	 * \param target is character received the help
	 */
	void pvpHelpOccursInTeam( CCharacter * actor, CCharacter * target );

	/**
	 * update method, called each tick
	 */
	void update();
	
	
private:
	/// the managed teams
	std::vector< CTeam >	_Teams;

	/// lowest free team Id
	uint16					_FirstFreeTeamId;

	/// Allocation step for the team container
	const uint				_TeamAllocStep;

};




extern CTeamManager TeamManager;


#endif //TEAM_MANAGER



