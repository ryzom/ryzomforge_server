/** \file stats_character_scan_job.h
 *
 * Part of STAT Module for GUS (general utilities service)
 *
 * $Id: stat_character_scan_job.h,v 1.4 2007/05/09 15:33:10 boucher Exp $
 */

#ifndef STAT_CHARACTER_SCAN_JOB_H
#define STAT_CHARACTER_SCAN_JOB_H

//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

#include "stdio.h"

#include "game_share/file_description_container.h"

#include "stat_job_manager.h"
#include "stat_char_info_extractor_factory.h"
#include "stat_char_filter_factory.h"
#include "stat_file_list_builder_factory.h"


//-------------------------------------------------------------------------------------------------
// class CCharacterScanJob
//-------------------------------------------------------------------------------------------------

class CCharacterScanJob: public CJobManager::IJob
{
public:
	// inherited virtual interface
	virtual void start();
	virtual bool finished();
	virtual std::string getShortStatus();
	virtual std::string getStatus();
	virtual void display(NLMISC::CLog* log=NLMISC::InfoLog);
	virtual void update();

public:
	CCharacterScanJob();
	~CCharacterScanJob();

public:
	// interface for initialisation and configuration of the job
	bool charTblAddCol(const std::string& name);
	bool addInfoExtractor(ICharInfoExtractor* infoExtractor);
	bool addFilter(ICharFilter* filter);
	bool addFileListBuilder(IFileListBuilder* builder);
	bool setOutputPath(const std::string& path);
	bool setOutputName(const std::string& fileNameRoot);
	void listFilesOnly(CFileDescriptionContainer& result);

	// interface for the InfoExtractors to use
	void charTblSetEntry(const std::string& colName,const std::string& value);
	void charTblFlushRow(uint32 account,uint32 slot);
	void freqTblAddEntry(const std::string& tblName, const std::string& key);

	// accessors for general use
	const std::string& getOutputPath() const;
	bool getFileList(CFileDescriptionContainer& result) const;
	bool deleteFilesInOutputDirectory() const;
	bool runForFile(const std::string& fileName);

private:
	typedef std::vector<NLMISC::CSmartPtr<ICharInfoExtractor> > TInfoExtractors;
	TInfoExtractors _InfoExtractors;

	typedef std::vector<NLMISC::CSmartPtr<ICharFilter> > TFilters;
	TFilters _Filters;

	typedef std::vector<NLMISC::CSmartPtr<IFileListBuilder> > TFileListBuilders;
	TFileListBuilders _FileListBuilders;

	CFileDescriptionContainer _Files;

	typedef std::map<std::string,uint32> TCharStatsMapTbl;
	typedef std::map<std::string, TCharStatsMapTbl> TCharStatsMap;
	TCharStatsMap _CharStatsMap;

	typedef std::vector<std::string> TTblCols;
	TTblCols _TblCols;

	typedef std::map<std::string,std::string> TCurrentRowEntries;
	TCurrentRowEntries _CurrentRowEntries;

	typedef enum { INIT, WORK, CLOSED, ERROR } TState;
	TState _State;

	std::string _OutputPath;
	std::string _OutputName;

	FILE* _CharTblFile;
	uint32 _NextFile;

	CFileDescriptionContainer* _FileList;
	bool _ListFilesOnly;
};


//-------------------------------------------------------------------------------------------------
#endif
