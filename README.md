## Build

requires sdl2
the instructions and scripts are for linux only for now
the reason why we build libraries (imgui, implot) seperatly is to help with compile times, build.sh runs much faster than build_libs.sh

```bash
./build_libs.sh
./build.sh
cd build
./main
```
