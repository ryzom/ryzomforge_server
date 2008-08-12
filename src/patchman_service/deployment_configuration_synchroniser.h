/** \file deployment_configuration_synchroniser.h
 *
 *
 */

#ifndef DEPLOYMENT_CONFIGURATION_SYNCHRONISER_H
#define DEPLOYMENT_CONFIGURATION_SYNCHRONISER_H


//-----------------------------------------------------------------------------
// includes
//-----------------------------------------------------------------------------

// game share
#include "game_share/deployment_configuration.h"

// local
#include "module_admin_itf.h"


//-----------------------------------------------------------------------------
// class CDeploymentConfigurationSynchroniser
//-----------------------------------------------------------------------------

class CDeploymentConfigurationSynchroniser: public PATCHMAN::CDeploymentConfigurationSynchroniserSkel
{
public:
	// specialisation of CDeploymentConfigurationSynchroniserSkel
	void requestSync(NLNET::IModuleProxy *sender);
	void sync(NLNET::IModuleProxy *sender, const NLNET::TBinBuffer &dataBlob);

	// our own virtual callback method for derived clases to implement (optionally)
	virtual void cbDeploymentConfigurationSynchronised(NLNET::IModuleProxy* sender) {}

protected:
	// ctor and initialisation...
	CDeploymentConfigurationSynchroniser();
	void init(NLNET::IModule* parent);

private:
	NLNET::IModule* _Parent;
};

#endif
