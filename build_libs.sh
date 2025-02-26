#!/bin/sh

set -xe

IMGUI_INCLUDE="-Ithirdparty/imgui -Ithirdparty/imgui/backends"
IMPLOT_INCLUDE="-I./thirdparty/implot"
SDL2_INCLUDE="`pkg-config --cflags sdl2`"

INCLUDE_FLAGS="$IMGUI_INCLUDE $SDL2_INCLUDE"
LINKER_FLAGS="-lSDL2"

IMGUI_SRC="thirdparty/imgui/*.cpp thirdparty/imgui/backends/imgui_impl_sdl2.cpp thirdparty/imgui/backends/imgui_impl_sdlrenderer2.cpp"
IMPLOT_SRC="thirdparty/implot/implot.cpp"

g++ -shared -fPIC -g $INCLUDE_FLAGS $IMGUI_SRC $IMPLOT_SRC -o build/libNumerics.so -lSDL2
