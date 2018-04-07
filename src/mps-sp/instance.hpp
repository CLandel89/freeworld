namespace Freeworld {
class InstanceMpsSp;
}

#ifndef INSTANCE_MPS_SP_HPP
#define INSTANCE_MPS_SP_HPP

#include "src/integration-headers/mps-sp/integration.hpp"
#include "src/mps/instance.hpp"
#include "src/mps-sp/core_utils.hpp"
#include "src/mps-sp/database.hpp"
#include "src/sp/instance.hpp"

namespace Freeworld {

class InstanceMpsSpPrivate;
/** @brief Holds a world/runtime of a game.
 * The MPC doesn't need this because this is run in the MPS. */
class InstanceMpsSp {
public:
	InstanceMpsSpPrivate* priv;
	InstanceMps* mps;
	InstanceSp* sp;
	CoreUtils* core_utils;
	Database* database;
	Integration::IntegrationMpsSp* integration;
	bool finished = false;
	InstanceMpsSp(InstanceMps* mps, InstanceSp* sp);
	~InstanceMpsSp();
	void start(std::vector<std::string> pkgs);
	void stop();
	void finish();
};

} // end of namespace Freeworld

#endif // INSTANCE_MPS_SP_HPP
