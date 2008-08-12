/** \file stats_guild_scan_job.h
 *
 * Part of STAT Module for GUS (general utilities service)
 *
 * $Id: stats_guild_scan_job.h,v 1.1 2005/04/25 23:57:36 miller Exp $
 */

#ifndef STAT_GUILD_SCAN_JOB_H
#define STAT_GUILD_SCAN_JOB_H

//-------------------------------------------------------------------------------------------------
// includes
//-------------------------------------------------------------------------------------------------

#include "game_share/file_description_container.h"

#include "stat_guild_container.h"
#include "stat_job_manager.h"


//-------------------------------------------------------------------------------------------------
// class CGuildScanJob
//-------------------------------------------------------------------------------------------------

class CGuildScanJob: public CJobManager::IJob
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
	// ctor / dtor
	CGuildScanJob(CStatGuildContainer* guildContainer,const NLMISC::CSString& outputRoot="");
	~CGuildScanJob();

public:
	// interface for initialisation and configuration of the job
	void addFileSpec(const NLMISC::CSString& fileSpec,bool recursive=false);

private:
	// private data - internal to job
	typedef enum { INIT, WORK, CLOSED, ERROR } TState;
	TState _State;
	uint32 _NextFile;
	CFileDescriptionContainer _Files;

	// file specs container
	typedef std::vector<NLMISC::CSString> TFileSpecs;
	TFileSpecs _RecursiveFileSpecs;
	TFileSpecs _NonRecursiveFileSpecs;

	// pointer to container that the job is supposed to be filling - if NULL job will abort
	NLMISC::CRefPtr<CStatGuildContainer> _GuildContainer;

	// the location for the csv files to be written to
	// - if empty, no csv files are written
	// - for values like './abc/def/' the output files take the form: './abc/def/xxx.csv'
	// - for values like './abc/def' the output files take the form: './abc/def_xxx.csv'
	NLMISC::CSString _OutputRoot;
};


//-------------------------------------------------------------------------------------------------
#endif
