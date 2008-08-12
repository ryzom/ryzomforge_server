/** \file ai_files.h
 *
 * $Id: ai_files.h,v 1.4 2004/03/01 19:19:03 lecroart Exp $
 */



#ifndef RYAI_AI_FILES_H
#define RYAI_AI_FILES_H

#include "nel/misc/types_nl.h"
#include "nel/misc/sheet_id.h"
#include "nel/misc/entity_id.h"

#include "nel/net/transport_class.h"

#include <map>
#include <string>

class CAIFiles
{
public:
	// clear out the data strustures and rescan the directories listed in the config
	// file for source and object files
	static void scan();

	// delete the object files (and temporary files if any) for a given manager
	static void clean(sint mgrId);

	// source file name, extension, etc
	static std::vector<std::string> srcPaths();		// the paths for source files
	static std::string srcExtension();				// the standard src extension
	static std::string srcName(sint mgrId);			// without path or extension
	static std::string srcFileName(sint mgrId);		// without path
	static std::string fullSrcName(sint mgrId);		// without extension
	static std::string fullSrcFileName(sint mgrId);	// with path and extension

	// object file name, extension, etc
	static std::string objPath();					// the path for obj files
	static std::string objExtension();				// the standard obj file extension
	static std::string objName(sint mgrId);			// without path or extension
	static std::string objFileName(sint mgrId);		// without extension
	static std::string fullObjFileName(sint mgrId);	// with path and extension

	// saved data file name, extension, etc
	static std::string savPath();					// the path for sav files
	static std::string savExtension();				// the standard sav file extension
	static std::string savName(sint mgrId);			// without path or extension
	static std::string savFileName(sint mgrId);		// without extension
	static std::string fullSavFileName(sint mgrId);	// with path and extension

	// Reading & writing object files
	static void CAIFiles::writeObjFile(sint mgrId);	

private:
	static void CAIFiles::_addSrcFile(std::string fileName,std::string fullFileName, uint timestamp);
	static void CAIFiles::_addObjFile(sint mgrId,std::string fullFileName, uint timestamp);
	static void CAIFiles::_addSavFile(sint mgrId,std::string fullFileName);

	static void CAIFiles::_scanSrcFiles(const std::string &path);
	static void CAIFiles::_scanObjAndSavFiles();
};

#endif