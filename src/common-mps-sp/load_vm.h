#ifndef LOAD_VM_H
#define LOAD_VM_H

#include <string>
#include <vector>

#include <mruby.h>
#include <mruby/compile.h>

namespace Freeworld { namespace Common {

void load_vm(mrb_state* vm, std::vector<std::string> pkgs);

} } //end of namespace Freeworld::Common

#endif //LOAD_VM_H
