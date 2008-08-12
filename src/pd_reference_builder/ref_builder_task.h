/** \file ref_builder_task.h
 * <File description>
 *
 * $Id: ref_builder_task.h,v 1.3 2004/09/28 12:25:34 legros Exp $
 */

#ifndef NL_REF_BUILDER_TASK_H
#define NL_REF_BUILDER_TASK_H

#include <nel/misc/types_nl.h>
#include <nel/misc/thread.h>

#include "reference_builder_service.h"

/**
 * This task builds a new reference from a previous reference and various delta updates
 * \author Benjamin Legros
 * \author Nevrax France
 * \date 2003
 */
class CRefBuilderTask : public IRefTask
{
public:

	/// Constructor
	CRefBuilderTask();

	/// Destructor
	~CRefBuilderTask();


	/// Setup Task
	void		setup(const std::string& rootRefPath,
					  const std::string& previousReferencePath,
					  const std::string& nextReferencePath,
					  const std::string& hoursUpdatePath,
					  const std::string& minutesUpdatePath,
					  const std::string& secondsUpdatePath,
					  const std::string& logUpdatePath,
					  const std::string& mintimestamp,
					  const std::string& maxtimestamp,
					  const std::string& keeptimestamp);



	/// Run task
	virtual bool	execute();


private:

	std::string		_RootRefPath;
	std::string		_PreviousReferencePath;
	std::string		_NextReferencePath;
	std::string		_HoursUpdatePath;
	std::string		_MinutesUpdatePath;
	std::string		_SecondsUpdatePath;
	std::string		_LogUpdatePath;
	std::string		_Mintimestamp;
	std::string		_Maxtimestamp;
	std::string		_KeepTimestamp;

public:

	/// Compute next timestamp
	static std::string	getNextTimestamp(const std::string& timestamp);
};


#endif // NL_REF_BUILDER_TASK_H

/* End of ref_builder_task.h */
