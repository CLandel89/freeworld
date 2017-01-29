# Dependencies
To compile, you need the following libs:
    sdl2
    sdl2_image
    sdl2_gfx
    boost
Please make sure to use sane sources. E.g., on Debian, you would use `apt-get install libsdl2-dev`. On Windows, you would download the packages from their authors and - W.I.P. - integrate them into my project.

## mruby
Since mruby is needed and not packaged (yet), it needs to be fetched from GitHub:
```
git submodule init
git submodule update
```
Try to compile mruby:
```
cd ext/mruby
./minirake
```
If that fails, look at the documentation in `ext/mruby`.
