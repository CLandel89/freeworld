#include "src/integration/lib/mps-sp-sqlite/integration.hpp"
#include "src/integration/lib/mps-sp-sqlite/chunks.hpp"
#include "src/integration/lib/mps-sp-sqlite/util.hpp"
#include "src/integration-headers/mps-sp/chunks.hpp"
#include "src/mps-sp/instance.hpp"
//this source file implements the following header:
#include "src/integration-headers/mps-sp/integration.hpp"

#include <stdlib.h> //malloc

namespace Freeworld { namespace Integration {

IntegrationMpsSpPrivate::IntegrationMpsSpPrivate() {
}
IntegrationMpsSpPrivate::~IntegrationMpsSpPrivate() {
}

IntegrationMpsSp::IntegrationMpsSp(InstanceMpsSp* instance) {
	this->instance = instance;
	priv = new IntegrationMpsSpPrivate;
	chunks = new Chunks(this);
}

IntegrationMpsSp::~IntegrationMpsSp() {
	delete chunks;
	delete priv;
}

void IntegrationMpsSp::init() {
}
void IntegrationMpsSp::quit() {
}

void IntegrationMpsSp::open_world(std::string world) {
	auto rc = sqlite3_open(("worlds/" + world + ".sqlite3").c_str(), &(priv->sqlite3_db));
	if (rc) ok_or_throw("OPEN-world", rc, priv->sqlite3_db);
	chunks->priv->prepare_chunks();
}

void IntegrationMpsSp::close_world() {
	chunks->priv->finalize_chunks();
	sqlite3_close(priv->sqlite3_db);
}

} } //end of namespace Freeworld::Integration
