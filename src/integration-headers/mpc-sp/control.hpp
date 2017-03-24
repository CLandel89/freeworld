#ifndef INPUT_H
#define INPUT_H

namespace Freeworld { namespace Impl {

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

/** Returns true if an event has been processed ('event' is filled),
 *  false if there are no input events pending. */
bool poll_event(InputEvent* event);

} } //end of namespace Freeworld::Impl

#endif //INPUT_H
