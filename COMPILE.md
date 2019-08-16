# Compiling and running

Please go through this guide step-by-step if you wish to run Freeworld.
Change paths and improvize, whenever needed; report unexpected problems as GitHub Issues :)
Not tested under Windows (only Linux, so far).

## mruby

Freeworld uses [mRuby](http://mruby.org) as the scripting engine.
Since I'd like to stick to a specific version of mRuby, it is included as a git submodule. To fetch it, execute the following GIT commands (in the project root dir):
```
cd /path/to/repo
git submodule init
git submodule update
```

mRuby has some dependencies:
 * ruby
 * bison
 * a C compiler (gcc or clang)

Compile mRuby:
```
cd /path/to/repo
cd ext/mruby
./minirake
```
If that fails, look at the documentation in `ext/mruby`.

## other libraries and tools

Before compiling Freeworld, you need the following:
 * cmake-gui (or cmake)
 * sdl2
 * sdl2\_image
 * sdl2\_gfx
 * boost
Please make sure to use sane sources. E.g., on Ubuntu, you would install `sdl2` with `sudo apt install libsdl2-dev`.

## compilation

Create a build directory and compile Freeworld (command line / Linux):
```
mkdir ~/fw-build
cd ~/fw-build
cmake-gui /path/to/repo
#(Choose your build environment and generate the build directory (~/fw-build).)
make #or other command for the specified build environment
```

## running Freeworld

The compilation result should be in `/path/to/repo/dist`.
Run the script `/path/to/repo/freeworld-sp`; inspect it if anything goes wrong.
