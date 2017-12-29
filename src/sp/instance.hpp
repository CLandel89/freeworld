namespace Freeworld {
class InstanceSp;
}

#ifndef INSTANCE_SP_HPP
#define INSTANCE_SP_HPP

#include "src/integration-headers/mpc-sp/integration.hpp"
#include "src/integration-headers/mps-sp/integration.hpp"
#include "src/mpc-sp/instance.hpp"
#include "src/mps-sp/instance.hpp"

#include <string>
#include <vector>

namespace Freeworld {

class InstanceSpPrivate;
/** @brief This class integrates all single
 *  player(SP)-related modules. */
class InstanceSp {
public:
	InstanceSpPrivate* priv;
	InstanceMpcSp* mpcSp;
	InstanceMpsSp* mpsSp;
	// these are often accessed, so we might just reference them from here:
	Integration::IntegrationMpcSp* integration_mpcSp;
	Integration::IntegrationMpsSp* integration_mpsSp;
	InstanceSp();
	~InstanceSp();
	void start(std::string world, std::vector<std::string> vm_pkgs, std::vector<std::string> media_pkgs);
	void stop();
};

} // end of namespace Freeworld

#endif // INSTANCE_SP_HPP
