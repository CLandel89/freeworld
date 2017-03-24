#ifndef SP_H
#define SP_H

#include <string>
#include <vector>

namespace Freeworld { namespace Sp {

void start(std::string world, std::vector<std::string> vm_pkgs, std::vector<std::string> media_pkgs);
void stop();

} } //end of Freeworld::Sp

#endif //SP_H
