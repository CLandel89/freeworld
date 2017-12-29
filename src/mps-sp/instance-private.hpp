namespace Freeworld {
class InstanceMpsSpPrivate;
}

#if (!defined(MPS)) && (!defined(MPS_SP)) && (!defined(SP))
#error "Don't use this outside of the Freeworld: MPS, MPS-SP, SP."
#endif // !defined(MPS_SP)

#ifndef INSTANCE_MPS_SP_PRIVATE_HPP
#define INSTANCE_MPS_SP_PRIVATE_HPP

#include "src/mps-sp/instance.hpp"

#include <mruby.h>

#include <map>

namespace Freeworld {

/** @brief @internal This class should only
 *  be visible within the MPS-SP module, for
 *  better code organization. Outside of the
 *  module, only the forward declaration
 *  should be used. */
class InstanceMpsSpPrivate {
public:
	mrb_state* vm;
};

extern std::map<mrb_state*, InstanceMpsSp*> vm_instance_map;

}

#endif // INSTANCE_MPS_SP_PRIVATE_HPP
