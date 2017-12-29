namespace Freeworld {
class InstanceMps;
}

#ifndef __INSTANCE_MPS_HPP
#define __INSTANCE_MPS_HPP

#include "src/integration-headers/mps-sp/integration.hpp"
#include "src/mps-sp/instance.hpp"

#include <string>
#include <vector>

namespace Freeworld {

class InstanceMpsPrivate;
/** @brief WIP: This class integrates all modules necessary
 *  for operation in multiplayer server mode (MPS), or a
 *  stand-alone MPS. */
class InstanceMps {
public:
	InstanceMpsPrivate* priv;
	InstanceMpsSp* mpsSp;
	Integration::IntegrationMpsSp* integration_mpsSp;
	InstanceMps();
	~InstanceMps();
	void start(std::string world, std::vector<std::string> vm_pkgs, std::vector<std::string> media_pkgs);
	void stop();
};

}

#endif // __INSTANCE_MPS_HPP
