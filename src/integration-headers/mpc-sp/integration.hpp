namespace Freeworld { namespace Integration {
class IntegrationMpcSp;
} }

#ifndef FREEWORLD_INTEGRATION_MPC_SP_HPP
#define FREEWORLD_INTEGRATION_MPC_SP_HPP

#include "src/mpc-sp/instance.hpp"
#include "src/integration-headers/mpc-sp/input.hpp"
#include "src/integration-headers/mpc-sp/video.hpp"

namespace Freeworld { namespace Integration {

class IntegrationMpcSpPrivate;

class IntegrationMpcSp {
public:
	IntegrationMpcSpPrivate* priv;
	InstanceMpcSp* instance;
	Input* input;
	Video* video;
	IntegrationMpcSp(InstanceMpcSp* instance);
	~IntegrationMpcSp();
	void init();
	void quit();
};

} } //end of namespace Freeworld::Integration

#endif //FREEWORLD_INTEGRATION_MPC_SP_HPP
