/** \file delta_builder.h
 * <File description>
 *
 * $Id: delta_builder.h,v 1.3 2004/06/23 14:22:57 legros Exp $
 */

#ifndef NL_DELTA_BUILDER_H
#define NL_DELTA_BUILDER_H

#include "nel/misc/types_nl.h"

#include "timestamp.h"

#include <vector>


/**
 * <Class description>
 * \author Benjamin Legros
 * \author Nevrax France
 * \date 2003
 */
class CDeltaBuilder
{
public:

	/**
	 * Type of Delta to build
	 */
	enum TDelta
	{
		Second,
		Minute,
		Hour
	};

	/**
	 * Build delta
	 * Builds delta files from an stamp interval
	 */
	static bool		build(const std::string& outputPath,
						  const std::string& hoursUpdatePath,
						  const std::string& minutesUpdatePath,
						  const std::string& secondsUpdatePath,
						  const std::string& mintimestamp,
						  const std::string& maxtimestamp,
						  TDelta deltaType);

	/*
	 * Remove older files in update path
	 */
	static bool		removeOlderDeltaInPath(const std::string& keeptimestamp,
										   const std::string& path);

private:

	/// Constructor
	CDeltaBuilder();


	/**
	 * Build delta
	 * Builds delta files from an stamp interval
	 */
	static bool		internalBuild(	const std::string& outputPath,
									const std::string& hoursUpdatePath,
									const std::string& minutesUpdatePath,
									const std::string& secondsUpdatePath,
									const std::string& mintimestamp,
									const std::string& maxtimestamp,
									TDelta deltaType,
									std::vector<std::string>& generatedFiles);

	/// Generate Delta update file
	static bool		generateDeltaFile(const std::string& outputPath,
									  const std::vector<std::string>& updateFiles,
									  const CTimestamp& starttime,
									  const CTimestamp& endtime);

	/// Build update files list
	static bool		updateFilesList(std::vector<std::vector<std::string> >& fileLists,
									std::vector<std::string>& updateFiles,
									const CTimestamp& minstamp,
									const CTimestamp& maxstamp);

};


#endif // NL_DELTA_BUILDER_H

/* End of delta_builder.h */
