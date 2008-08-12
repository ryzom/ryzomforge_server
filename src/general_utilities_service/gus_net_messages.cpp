/** \file gus_net_messages.cpp
 *
 * $id$
 *
 */

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

#include "game_share/utils.h"
#include "gus_net_messages.h"


//-----------------------------------------------------------------------------
// GUSNET namespace
//-----------------------------------------------------------------------------

namespace GUSNET
{
	//-----------------------------------------------------------------------------
	// methods CMsgRegisterModule
	//-----------------------------------------------------------------------------

	CMsgRegisterModule::CMsgRegisterModule()
	{
		_ModuleId= InvalidRemoteModuleId;
	}

	void CMsgRegisterModule::serial(NLMISC::IStream& stream)
	{
		stream.serial(_ModuleId);
		stream.serial(_ModuleName);
		stream.serial(_Parameters);
	}

	void CMsgRegisterModule::setup(uint32 moduleId,const NLMISC::CSString& moduleName,const NLMISC::CSString& parameters)
	{
		_ModuleId= moduleId;
		_ModuleName= moduleName;
		_Parameters= parameters;
	}

	uint32 CMsgRegisterModule::getModuleId() const
	{
		return _ModuleId;
	}

	const NLMISC::CSString& CMsgRegisterModule::getModuleName() const
	{
		return _ModuleName;
	}

	const NLMISC::CSString& CMsgRegisterModule::getParameters() const
	{
		return _Parameters;
	}


	//-----------------------------------------------------------------------------
	// methods CMsgUnregisterModule
	//-----------------------------------------------------------------------------

	CMsgUnregisterModule::CMsgUnregisterModule()
	{
		_ModuleId= InvalidRemoteModuleId;
	}

	void CMsgUnregisterModule::serial(NLMISC::IStream& stream)
	{
		stream.serial(_ModuleId);
	}

	void CMsgUnregisterModule::setup(uint32 moduleId)
	{
		_ModuleId= moduleId;
	}

	uint32 CMsgUnregisterModule::getModuleId() const
	{
		return _ModuleId;
	}
}

//-----------------------------------------------------------------------------
