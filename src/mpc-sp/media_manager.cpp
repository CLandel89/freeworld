#include "src/mpc-sp/media_manager.hpp"

#include <iostream>
#include <stdexcept>

#include <boost/filesystem.hpp>

#include "src/mpc-mps-sp/utils.hpp"

namespace Freeworld {

//recursively iterate dir while loading
void MediaManager::rec_load(boost::filesystem::path path) {
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

void MediaManager::load(std::string name) {
	boost::filesystem::path path("packages/" + name);
	rec_load(path);
}

std::string MediaManager::fn_for_hash(int32_t hash) {
	try {
		std::string result = fn.at(hash);
		return result;
	}
	catch (const std::out_of_range& e) {
		std::cout << "File hash " << hash << " not found.\n";
		std::string empty;
		return empty;
	}
}

} // end of namespace Freeworld
