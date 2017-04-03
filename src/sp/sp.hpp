#ifndef SP_H
#define SP_H

#include <string>
#include <vector>

namespace Freeworld {

void start(std::string world, std::vector<std::string> vm_pkgs, std::vector<std::string> media_pkgs);
void stop();

} // end of namespace Freeworld

#endif //SP_H
