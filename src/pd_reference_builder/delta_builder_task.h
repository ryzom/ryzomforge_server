/** \file delta_builder_task.h
 * <File description>
 *
 * $Id: delta_builder_task.h,v 1.2 2004/06/09 16:37:42 legros Exp $
 */

#ifndef NL_DELTA_BUILDER_TASK_H
#define NL_DELTA_BUILDER_TASK_H

#include "nel/misc/types_nl.h"
#include "reference_builder_service.h"

#include "pd_lib/delta_builder.h"


/**
 * This task builds a delta from other delta updates
 * \author Benjamin Legros
 * \author Nevrax France
 * \date 2003
 */
class CDeltaBuilderTask : public IRefTask
{
public:

	/// Constructor
	CDeltaBuilderTask();

	/// Destructor
	~CDeltaBuilderTask();

	/// Setup Task
	void		setup(const std::string& outputPath,
					  const std::string& hoursUpdatePath,
					  const std::string& minutesUpdatePath,
					  const std::string& secondsUpdatePath,
					  const std::string& mintimestamp,
					  const std::string& maxtimestamp,
					  CDeltaBuilder::TDelta type,
					  const std::string& keeptimestamp);



	/// Run task
	virtual bool	execute();


private:

	std::string		_OutputPath;
	std::string		_HoursUpdatePath;
	std::string		_MinutesUpdatePath;
	std::string		_SecondsUpdatePath;
	std::string		_Mintimestamp;
	std::string		_Maxtimestamp;
	CDeltaBuilder::TDelta	_Type;
	std::string		_KeepTimestamp;
};


#endif // NL_DELTA_BUILDER_TASK_H

/* End of delta_builder_task.h */
