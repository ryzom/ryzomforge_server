/** \file manager_parent.h
 *	Common class for all manager container.
 *
 * $Id: manager_parent.h,v 1.9 2005/02/25 18:39:11 vuarand Exp $
 */



#ifndef MANAGER_PARENT_H
#define MANAGER_PARENT_H

class CAIInstance;
class CCellZone;
//class IBot;
class CGroup;
class CManager;

class IManagerParent : public NLMISC::CDbgRefCount<IManagerParent>
{
public:
	// define some virtual to be implemented by parent

	/// Return a reference to the ai instance that contains this manager (directly or indirectly)
	virtual CAIInstance * getAIInstance() const = 0;
	/** Return a pointeur to the cell zone that contain this mananger. 
	 *	Can be null if the manager is is a AIInstance object.
	 */
	virtual CCellZone	* getCellZone() = 0;

	/// return a display index string
	virtual std::string getIndexString() const =0;
	/// child manager ask parent to build is index string (the one for the manager, not for the parent)
	virtual std::string getManagerIndexString(const CManager *manager) const =0;

	virtual	void	addEnergy		(uint32	energy)	{}
	virtual	void	removeEnergy	(uint32	energy)	{}

	/// Signal that a group is now dead (no more bots spawned)
	virtual void	groupDead(CGroup *grp)	=	0;
};


#endif // MANAGER_PARENT_H
