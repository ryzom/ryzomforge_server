/** \file deployment_configuration_synchroniser.cpp
 *
 *
 */

//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

// nel
#include "nel/misc/mem_stream.h"

// game share
#include "game_share/utils.h"

// local
#include "deployment_configuration_synchroniser.h"


//-------------------------------------------------------------------------------------------------
// namespaces
//-------------------------------------------------------------------------------------------------

using namespace std;
using namespace NLMISC;
using namespace NLNET;
using namespace PATCHMAN;
using namespace DEPCFG;


//-----------------------------------------------------------------------------
// methods CDeploymentConfigurationSynchroniser
//-----------------------------------------------------------------------------

void CDeploymentConfigurationSynchroniser::requestSync(NLNET::IModuleProxy *sender)
{
	// make sure we're initialised
	nlassert(_Parent!=NULL);

	// bundle the CDeploymentConfiguration singleton into a data blob
	CMemStream blob;
	blob.serial(CDeploymentConfiguration::getInstance());

	// get a proxy for the other guy and send them the message
	CDeploymentConfigurationSynchroniserProxy other(sender);
	other.sync(_Parent,NLNET::TBinBuffer(blob.buffer(),blob.size()));
}

void CDeploymentConfigurationSynchroniser::sync(NLNET::IModuleProxy *sender, const NLNET::TBinBuffer &dataBlob)
{
	// make sure we're initialised
	nlassert(_Parent!=NULL);

	// rebuild our CDeploymentConfiguration singleton from the data blob
	NLMISC::CMemStream blob;
	blob.fill(dataBlob.getBuffer(),dataBlob.getBufferSize());
	blob.invert();
	blob.serial(CDeploymentConfiguration::getInstance());

	// call the derived class' callback method (if there is one)
	cbDeploymentConfigurationSynchronised(sender);
}

CDeploymentConfigurationSynchroniser::CDeploymentConfigurationSynchroniser()
	:	_Parent(NULL)
{
}

void CDeploymentConfigurationSynchroniser::init(NLNET::IModule* parent)
{
	// make sure we're NOT initialising more than once
	nlassert(_Parent==NULL);

	CDeploymentConfigurationSynchroniserSkel::init(parent);

	_Parent= parent;
}
