namespace Freeworld { namespace Integration {
class Input;
} }

#ifndef FREEWORLD_INTEGRATION_INPUT_HPP
#define FREEWORLD_INTEGRATION_INPUT_HPP

#include "src/integration-headers/mpc-sp/integration.hpp"

#include <stdint.h>

namespace Freeworld { namespace Integration {

enum CiType {
#include "dist/enums/ci_type.enum"
};
enum CiButton {
#include "dist/enums/ci_button.enum"
};

typedef struct {
	int32_t type;
	int32_t value;
} InputEvent;

class InputPrivate;

class Input {
public:
	InputPrivate* priv;
	IntegrationMpcSp* integration;
	Input(IntegrationMpcSp* integration);
	~Input();
	/** Returns true if an event has been processed ('event' is filled),
	  * false if there are no input events pending. */
	bool poll(InputEvent* event);
};

} } //end of namespace Freeworld::Integration

#endif // FREEWORLD_INTEGRATION_INPUT_HPP
