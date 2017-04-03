#ifndef PACKAGE_MANAGER_H
#define PACKAGE_MANAGER_H

#include <string>
#include <map>

#include <boost/filesystem.hpp>

namespace Freeworld {

class PackageManager {
	std::map<int32_t, std::string> fn;
	//recursively iterate dir while loading
	void rec_load(boost::filesystem::path path);
public:
	void load (std::string name);
	std::string fn_for_hash(int32_t hash);
};

PackageManager* get_package_manager();

} // end of namespace Freeworld

#endif /* PACKAGE_MANAGER_H */
