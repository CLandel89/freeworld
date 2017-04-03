#include "src/mpc-sp/package_manager.hpp"

#include <iostream>
#include <stdexcept>

#include <boost/filesystem.hpp>

#include "src/mpc-mps-sp/utils.hpp"

namespace Freeworld {

void PackageManager::load(std::string name) {
	boost::filesystem::path path("packages/" + name);
	rec_load(path);
}

void PackageManager::rec_load(boost::filesystem::path path) {
	std::string path_name = path.filename().string();
	for (
			boost::filesystem::directory_iterator iter(path), end;
			iter != end;
			iter++ )
	{
		std::string filename = iter->path().string();
		if (boost::filesystem::is_directory(*iter))
			//recursively add files
			rec_load(*iter);
		else
		{
			auto hash = Freeworld::string_hash(filename);
			fn[hash] = filename;
		}
	}
}

std::string PackageManager::fn_for_hash(int32_t hash) {
	try {
		std::string result = fn.at(hash);
		return result;
	}
	catch (std::out_of_range oor) {
		std::cout << "File hash " << hash << " not found.\n";
		std::string empty;
		return empty;
	}
}

PackageManager packageManager;
PackageManager* get_package_manager() {
	return &packageManager;
}

} // end of namespace Freeworld
