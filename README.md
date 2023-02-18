# 3D Experimental Rendering Engine

This project is a 3D rendering engine that is used by me to learn
about 3D graphics and OpenGL.

## Dependencies

* GLM for all the maths
* spdlog for logging
* GLEW as an OpenGL loader library
* GLFW for creating a window and OpenGL context
* Dear ImGui for the in-game GUI
* Assimp asset import library

Ubuntu/Debian packages:

`libglfw3-dev libglew-dev libspdlog-dev libimgui-dev libstb-dev libglm-dev libassimp-dev`

I plan on including all these dependencies in the form of git
submodules. This should make it easier to do cross-platform builds.

## Compiling and Running

The project requires a compiler that supports C++20 to build.

```shell
mkdir build && cd build
cmake ..
cmake --build .
```

## Known issues

### Shader can not be read if not run from build folder

```
$ ./build/DemoSceneApp
[2023-02-18 17:13:17.790] [info] OpenGL version is 4.5
[2023-02-18 17:13:17.794] [error] OpenGL shader compilation failed: 0:1(1): error: syntax error, unexpected end of file

DemoSceneApp: /home/wegwart/work/engine/engine/renderer/ShaderProgram.cpp:63: void Engine::Renderer::ShaderProgram::compileAndLinkShaders(const string&, const string&): Assertion `success == true' failed.
Aborted
```

Required launch settings for Visual Studio Code

.vscode/launch.json
```
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "program": "DemoSceneApp",
            "cwd": "${workspaceFolder}/build"
        }
    ]
}
```

### Segmentation fault after terminating program

```
build$ ./DemoSceneApp
[2023-02-18 17:18:11.309] [info] OpenGL version is 4.5
Segmentation fault
```


