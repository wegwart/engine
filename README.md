# 3D Experimental Rendering Engine

This project is a 3D rendering engine that is used by me to learn
about 3D graphics and OpenGL.

## Cloning

Use the recursive clone to fetch the submodules!

`git clone --recursive https://github.com/ulmer-a/engine`

## Dependencies

* GLM for all the maths
* spdlog for logging
* GLEW as an OpenGL loader library
* GLFW for creating a window and OpenGL context
* Dear ImGui for the in-game GUI
* Assimp asset import library

Ubuntu/Debian packages:

`libglfw3-dev libglew-dev libspdlog-dev libimgui-dev libstb-dev`

I plan on including all these dependencies in the form of git
submodules. This should make it easier to do cross-platform builds.~~~~

## Compiling and Running

The project requires a compiler that supports C++20 to build.

```shell
mkdir build && cd build
cmake ..
cmake --build .
```
