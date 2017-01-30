# Dependencies
To compile, you need the following libs:
    sdl2
    sdl2_image
    sdl2_gfx
    boost
Please make sure to use sane sources. E.g., on Debian, you would use `apt-get install libsdl2-dev`. On Windows, you would download the packages from their authors and - W.I.P. - integrate them into my project.

## mruby
Since I'd like to stick to a specific version of mruby, it is included as a git submodule. To fetch it, execute the following in the project root dir (Windows users might need to use 'open git bash shell here' or similar from the context menu in the file browser):
```
git submodule init
git submodule update
```
Then try to compile mruby:
```
cd ext/mruby
./minirake
```
If that fails, look at the documentation in `ext/mruby`.
