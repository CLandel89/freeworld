namespace Freeworld { namespace Integration {
class IntegrationMpsSp;
} }

#ifndef INTEGRATION_MPS_SP_HPP
#define INTEGRATION_MPS_SP_HPP

#include "src/integration-headers/mps-sp/chunks.hpp"
#include "src/mps-sp/instance.hpp"

#include <string>

namespace Freeworld { namespace Integration {

class IntegrationMpsSpPrivate;
class IntegrationMpsSp {
public:
	IntegrationMpsSpPrivate* priv;
	Freeworld::InstanceMpsSp* instance;
	Chunks* chunks;

	IntegrationMpsSp(Freeworld::InstanceMpsSp* instance);
	~IntegrationMpsSp();
	void init();
	void quit();
	void open_world(std::string world);
	void close_world();
};

} } // end of namespace Freeworld::Integration

#endif // INTEGRATION_MPS_SP_HPP
