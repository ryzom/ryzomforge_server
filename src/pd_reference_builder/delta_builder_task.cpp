/** \file delta_builder_task.cpp
 * <File description>
 *
 * $Id: delta_builder_task.cpp,v 1.2 2004/06/09 16:37:42 legros Exp $
 */

#include "delta_builder_task.h"


/*
 * Constructor
 */
CDeltaBuilderTask::CDeltaBuilderTask()
{
}

/*
 * Destructor
 */
CDeltaBuilderTask::~CDeltaBuilderTask()
{
}


/*
 * Setup Task
 */
void	CDeltaBuilderTask::setup(const std::string& outputPath,
								 const std::string& hoursUpdatePath,
								 const std::string& minutesUpdatePath,
								 const std::string& secondsUpdatePath,
								 const std::string& mintimestamp,
								 const std::string& maxtimestamp,
								 CDeltaBuilder::TDelta type,
								 const std::string& keeptimestamp)
{
	_OutputPath = outputPath;
	_HoursUpdatePath = hoursUpdatePath;
	_MinutesUpdatePath = minutesUpdatePath;
	_SecondsUpdatePath = secondsUpdatePath;
	_Mintimestamp = mintimestamp;
	_Maxtimestamp = maxtimestamp;
	_Type = type;
	_KeepTimestamp = keeptimestamp;
}



/*
 * Run task
 */
bool	CDeltaBuilderTask::execute()
{
	// generate new reference
	if (!CDeltaBuilder::build(	_OutputPath,
								_HoursUpdatePath,
								_MinutesUpdatePath,
								_SecondsUpdatePath,
								_Mintimestamp,
								_Maxtimestamp,
								_Type))
	{
		nlwarning("CDeltaBuilder: failed to build delta");
		return false;
	}
	else
	{
		nlinfo("CDeltaBuilder: built delta between '%s' and '%s'", _Mintimestamp.c_str(), _Maxtimestamp.c_str());

		// remove older files
		if (_Type == CDeltaBuilder::Hour)
			CDeltaBuilder::removeOlderDeltaInPath(_KeepTimestamp, _MinutesUpdatePath);
		if (_Type == CDeltaBuilder::Hour || _Type == CDeltaBuilder::Minute)
			CDeltaBuilder::removeOlderDeltaInPath(_KeepTimestamp, _SecondsUpdatePath);
	}

	return true;
}
