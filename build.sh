#!/bin/sh

set -xe

CFLAGS="-Wall -Wextra -pedantic"
LINKER_FLAGS="-Lbuild -lSDL2 -lNumerics -Wl,-rpath=."
INCLUDE_FLAGS="-I./thirdparty/imgui -I./thirdparty/imgui/backends -I./thirdparty/implot `pkg-config --cflags sdl2`"

g++ $CFLAGS $INCLUDE_FLAGS src/main.cpp -o main $LINKER_FLAGS
