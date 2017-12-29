#include "src/mpc-sp/instance.hpp"
#include "src/integration-headers/mpc-sp/integration.hpp"
#include "src/mpc-sp/media_manager.hpp"

namespace Freeworld {

InstanceMpcSp::InstanceMpcSp(InstanceMpc* mpc, InstanceSp* sp)
: mpc(mpc), sp(sp) {
	integration = new Integration::IntegrationMpcSp(this);
	media_manager = new MediaManager;
}
InstanceMpcSp::~InstanceMpcSp() {
	delete media_manager;
}

void InstanceMpcSp::start(std::vector<std::string> pkgs) {
	integration->init();
	for (auto iter = pkgs.begin(); iter!=pkgs.end(); iter++) {
		media_manager->load(*iter);
	}
}

void InstanceMpcSp::stop() {
	integration->quit();
}

} // namespace Freeworld
