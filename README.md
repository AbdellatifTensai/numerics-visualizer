## Build

when cloning the repository, don't forget to clone with submodules flags
```
git clone --recurse-submodules https://github.com/AbdellatifTensai/numerics-visualizer
```

requires sdl2, replace apt with your package manager on linux
```
sudo apt install libsdl2-*
```

run build scripts:

```
./build_libs.sh
./build.sh
cd build
./main
```

we build imgui and implot seperatly as dynamic libraries to help with compile times, build.sh runs much faster than build_libs.sh
