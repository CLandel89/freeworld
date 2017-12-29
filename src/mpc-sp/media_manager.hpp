namespace Freeworld {
class MediaManager;
}

#ifndef MEDIA_MANAGER_HPP
#define MEDIA_MANAGER_HPP

#include <string>
#include <map>

#include <boost/filesystem.hpp>

namespace Freeworld {

class MediaManager {
	std::map<int32_t, std::string> fn;
	void rec_load(boost::filesystem::path path);
public:
	void load(std::string name);
	std::string fn_for_hash(int32_t hash);
};

} // end of namespace Freeworld

#endif // MEDIA_MANAGER_HPP
