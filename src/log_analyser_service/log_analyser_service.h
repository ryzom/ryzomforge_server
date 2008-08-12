/** \file log_analyser_service.h
 * <File description>
 *
 * $Id: log_analyser_service.h,v 1.4 2005/04/19 13:25:08 legros Exp $
 */

#ifndef NL_LOG_ANALYSER_SERVICE_H
#define NL_LOG_ANALYSER_SERVICE_H

#include <nel/misc/types_nl.h>
#include <nel/misc/thread.h>
#include <nel/misc/mutex.h>
#include <nel/misc/time_nl.h>
#include <nel/net/service.h>


/**
 * <Class description>
 * \author Benjamin Legros
 * \author Nevrax France
 * \date 2003
 */
class CLogAnalyserService : public NLNET::IService
{
public:

	/// Constructor
	CLogAnalyserService();


	/// Initialization
	virtual void	init();

	/// Release
	virtual void	release();

	/// Update
	virtual bool	update();


public:

	enum TQueryState
	{
		QueryAwaiting,
		QueryBeingTreated,
		QueryTreated
	};

	class CQuery
	{
	public:

		CQuery(uint32 id, const std::string& query) : Id(id), Progress(0.0f), Query(query), State(QueryAwaiting), Finished(false)	{}

		uint32						Id;
		volatile float				Progress;
		TQueryState					State;
		std::string					Query;
		std::vector<std::string>	Result;
		NLMISC::TTime				Timeout;

		volatile bool				Finished;

	};

	/// Get Service Instance
	static CLogAnalyserService*	getInstance()
	{
		return (CLogAnalyserService*)IService::getInstance();
	}

	/// Get Next Query Id
	uint32			getNextQueryId()
	{
		return _NextQueryId++;
	}

	/// Execute query
	void			executeQuery(uint32 queryId, const std::string& query);

	/// Get query result
	bool			getQueryResult(uint32 queryId, std::string& result, sint page, uint& numpage, const std::string& filter, bool fmode, uint linePerPage);

	/// Get Query list
	void			getQueryList(std::vector<CQuery*>& queries);

	/// Cancel awaiting query
	void			cancelQuery(uint32 queryId);

	/// Get current query
	CQuery*			getCurrentQuery()				{ return _Current; }

private:

	NLMISC::CMutex			_Mutex;

	NLMISC::IThread*		_Thread;

	CQuery*					_Current;

	std::deque<CQuery*>		_Requests;
	std::deque<CQuery*>		_Finished;

	uint32					_NextQueryId;

	/// Update Web connection
	void	updateWebConnection();
};


#endif // NL_LOG_ANALYSER_SERVICE_H

/* End of log_analyser_service.h */
