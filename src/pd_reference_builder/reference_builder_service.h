/** \file reference_builder_service.h
 * <File description>
 *
 * $Id: reference_builder_service.h,v 1.2 2007/03/09 09:56:56 boucher Exp $
 */

#ifndef NL_REFERENCE_BUILDER_SERVICE_H
#define NL_REFERENCE_BUILDER_SERVICE_H

#include <nel/misc/types_nl.h>
#include <nel/net/service.h>

#include <nel/misc/thread.h>


class IRefTask : public NLMISC::IRunnable
{
public:

	/**
	 * Method to task implement behaviour
	 * Return ture if task successfully executed
	 */
	virtual bool	execute() = 0;


public:

	/**
	 * Start the task
	 */
	void			start();

	/**
	 * Ask the task to stop
	 */
	virtual void	askStop()	{ AskedToStop = true; }

	/**
	 * The service that requested this task
	 */
	NLNET::TServiceId		RequesterService;
	/**
	 * The id of the task (id sent by requester)
	 */
	uint32			TaskId;

	enum TTaskState
	{
		NotRunning,
		Running,
		Completed
	};

	volatile TTaskState	State;
	volatile bool		AskedToStop;
	volatile bool		ExecutionSuccess;

public:

	virtual void	run();

	IRefTask() : State(NotRunning), _Thread(NULL), ExecutionSuccess(true), AskedToStop(false)	{ }
	virtual ~IRefTask()														{ if (_Thread != NULL)	delete _Thread; }

private:

	NLMISC::IThread	*_Thread;

};


/**
 * Persistant Data Service Class
 * \author Benjamin Legros
 * \author Nevrax France
 * \date 2004
 */
class CReferenceBuilderService : public NLNET::IService
{
public:

	/// Constructor
	CReferenceBuilderService();



	/// Initialization
	virtual void	init();

	/// Release
	virtual void	release();

	/// Update
	virtual bool	update();



	/// Queue of tasks to run
	std::deque<IRefTask*>	Tasks;

	/// Currently ran task
	IRefTask*				CurrentTask;


	/**
	 * Kill All Submitted Task By A Service
	 */
	void			killTasks(NLNET::TServiceId serviceId);

};


#endif // NL_REFERENCE_BUILDER_SERVICE_H

/* End of reference_builder_service.h */
