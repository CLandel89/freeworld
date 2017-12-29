// https://stackoverflow.com/questions/3485166/change-the-current-working-directory-in-c

#ifdef _WIN32
#include <direct.h>
// MSDN recommends against using getcwd & chdir names
#define cwd _getcwd
#define cd _chdir
#else
#include "unistd.h"
#define cwd getcwd
#define cd chdir
#endif

#ifdef DEBUG
#include <iostream>
#endif

/** @brief Extracts the directory of the executable file
 *  (argv[0] from main) and changes to it as the working dir.
 * @author Christian Landel */
inline void fixdir (const char* const* argv)
{
    size_t l = strlen(argv[0]);
    char* path = new char[l+1];
    path[l] = '\0';
    strcpy(path, argv[0]);
    size_t pos;
    for (pos=l-1; pos>0; pos--)
    {
        if (path[pos]=='/' || path[pos]=='\\')
            break;
    }
    path[pos] = '\0'; // cut off last / and file name
#ifdef DEBUG
    std::cout << "::fixdir: Changing working directory to: " << path << "\n";
#endif
    if (pos && cd(path)) {
#ifdef DEBUG
        throw "::fixdir failed.";
#else
	printf("::fixdir failed.\n");
#endif
    }
    delete path;
}
