#ifndef INPUT_H
#define INPUT_H

namespace Jumpfree { namespace Impl {

enum CiType {
#include "../../dist/enums/ci_type.enum"
};
enum CiButton {
#include "../../dist/enums/ci_button.enum"
};

typedef struct {
	int32_t type;
	int32_t value;
} InputEvent;

//poll functions

/** Returns true if an event has been processed ('event' is filled),
 *  false if there are no input events pending. */
bool poll_event(InputEvent* event);

} } //end of namespace Jumpfree::Impl

#endif //INPUT_H
