/** \file ai_entity.h
 *
 * $Id: ai_entity.h,v 1.36 2005/11/08 18:38:20 vuarand Exp $
 */

#ifndef RYAI_ENTITY_H
#define RYAI_ENTITY_H

#include <string>
#include <vector>

//--------------------------------------------------------------------------
// The CAIEntiy class
//--------------------------------------------------------------------------
class CAIEntity;
class CAIInstance;

extern void removeFromWatch(CAIEntity* entity);

class CAIEntity
{
public:
	/// @name Destructor
	//@{
	virtual ~CAIEntity();
	//@}
	
	/// @name Virtual interface
	//@{
	virtual CAIInstance* getAIInstance() const = 0;
	// display verbose status information regarding the entity 
//	virtual void display(CStringWriter& stringWriter) const;
//	virtual std::string getIndexString() const = 0;
	virtual std::string	getOneLineInfoString() const;
	virtual std::vector<std::string> getMultiLineInfoString() const;
	//@}
	
public:
	/// @name Debug info display methods
	//@{
	// public interface for the 'buildDebugString' virtual
	// method set - it is safe, returning cleanly if called on a NULL pointer
//	std::string debugString(uint idx = 0) const;
	//@}
};

inline
CAIEntity::~CAIEntity()
{
	removeFromWatch(this);
}

inline
std::string	CAIEntity::getOneLineInfoString() const
{
	return std::string("<no debug info available for this entity>");
}

inline
std::vector<std::string> CAIEntity::getMultiLineInfoString() const
{
	std::vector<std::string> container;
	MULTI_LINE_FORMATER::pushTitle(container, "CAIEntity");
	MULTI_LINE_FORMATER::pushEntry(container, "<default multi line info>");
	MULTI_LINE_FORMATER::pushEntry(container, getOneLineInfoString());
	MULTI_LINE_FORMATER::pushFooter(container);
	return container;
}

#endif
