/** \file ai_service_ctrl.cpp
 *
 * $Id: ai_actions.cpp,v 1.16 2005/08/12 09:20:20 lancon Exp $
 */


#include "stdpch.h"

#include "nel/misc/types_nl.h"
#include "nel/misc/hierarchical_timer.h"
#include "nel/misc/debug.h"
#include "ai_actions.h"

// singleton data
bool CAIActions::_init;
CAIActions::IExecutor *CAIActions::_executor;

void CAIActions::openFile(const std::string &fileName)
{
	nlassert(_init==true);
	_executor->openFile(fileName);
}
void CAIActions::closeFile(const std::string &fileName)
{
	nlassert(_init==true);
	_executor->closeFile(fileName);
}

void CAIActions::begin(uint32 contextAlias)
{
	nlassert(_init==true);
	_executor->begin(contextAlias);
}

void CAIActions::end(uint32 contextAlias)
{
	nlassert(_init==true);
	_executor->end(contextAlias);
}

static uint64 stringToInt64(const char *str)
{
	uint64 id=0;
	uint i;
	for (i=0;i<8 && str[i]!=0;++i)
		((char *)&id)[i]=str[i];

	// the following assert ensures that we never try to cram >8 letters into an int64
	nlassert(str[i]==0);

	return id;
}

using std::string;

inline
static uint64 stringToInt64(const string &str)
{
	return stringToInt64(str.c_str());
}

void CAIActions::execute(const string &action,const std::vector<CAIActions::CArg> &args)
{
	H_AUTO(CAIActions_execute);
	nlassert(_init==true);

	_executor->execute(stringToInt64(action),args);
}

void CAIActions::execute(const string &action,const std::vector<std::string> &stringArgs)
{
	H_AUTO(CAIActions_execute);
	nlassert(_init==true);

	// build an argument vector from the string vector
	std::vector<CAIActions::CArg> args;
	for (uint j=0;j<stringArgs.size();++j)
		args.push_back(CAIActions::CArg(stringArgs[j]));

	_executor->execute(stringToInt64(action),args);
}

void CAIActions::execute(const string &action,const std::vector<int> &rawArgs)
{
	H_AUTO(CAIActions_execute);
	nlassert(_init==true);

	// build an argument vector from the string vector
	std::vector<CAIActions::CArg> args;
	for (uint j=0;j<rawArgs.size();++j)
		args.push_back(CAIActions::CArg(rawArgs[j]));

	_executor->execute(stringToInt64(action),args);
}

void CAIActions::execute(const string &action,const std::vector<double> &rawArgs)
{
	H_AUTO(CAIActions_execute);
	nlassert(_init==true);

	// build an argument vector from the string vector
	std::vector<CAIActions::CArg> args;
	for (uint j=0;j<rawArgs.size();++j)
		args.push_back(CAIActions::CArg(rawArgs[j]));

	_executor->execute(stringToInt64(action),args);
}

void CAIActions::execute(const string &action)
{
	H_AUTO(CAIActions_execute);
	std::vector<CAIActions::CArg> emptyVector;
	execute(action,emptyVector);
}
