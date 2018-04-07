namespace Freeworld {
class InstanceMpcSp;
}

#ifndef INSTANCE_MPC_SP_HPP
#define INSTANCE_MPC_SP_HPP

#include "src/integration-headers/mpc-sp/integration.hpp"
#include "src/mpc/instance.hpp"
#include "src/mpc-sp/media_manager.hpp"
#include "src/sp/instance.hpp"

#include <string>

namespace Freeworld {

class InstanceMpcSp {
public:
	InstanceMpc* mpc;
	InstanceSp* sp;
	MediaManager* media_manager;
	Integration::IntegrationMpcSp* integration;
	InstanceMpcSp(InstanceMpc* mpc, InstanceSp* sp);
	~InstanceMpcSp();
	void start(std::vector<std::string> pkgs);
	void stop();
	void finish();
};

} // namespace Freeworld

#endif // INSTANCE_MPC_SP_HPP
