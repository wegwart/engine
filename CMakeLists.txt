cmake_minimum_required(VERSION 3.18)

project(ulmer_engine VERSION 0.1)

add_subdirectory(lib)

# Default build type: Release
if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release")
endif ()
message(STATUS "${CMAKE_PROJECT_NAME} v${CMAKE_PROJECT_VERSION} [${CMAKE_BUILD_TYPE}]")


option(ENABLE_DEBUG_OVERLAY "Enable debug info overlay" ON)
option(ENABLE_IMGUI_DEMO "Enable ImGui Demo Window" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "C++ Standard: C++${CMAKE_CXX_STANDARD}")

# generate the configuration header
set(CONFIG_HEADER ${PROJECT_BINARY_DIR}/src/config.h)
string(TIMESTAMP BUILD_DATE "%Y-%m-%d")
execute_process(
        COMMAND git log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)
configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/engine/config.h.in
        ${CONFIG_HEADER}
)

add_executable(engine
        ${CONFIG_HEADER}
        DemoScene.cpp
        engine/include/engine/Engine.h
        engine/Engine.cpp
        engine/Window.cpp
        engine/include/engine/Window.h
        engine/OverlayWindow.cpp
        engine/include/engine/OverlayWindow.h
        engine/DemoWindow.cpp
        engine/include/engine/DemoWindow.h
        engine/Scene.cpp
        engine/include/engine/Scene.h
        engine/renderer/VertexBuffer.cpp
        engine/include/engine/VertexBuffer.h
        engine/renderer/Shader.cpp
        engine/include/engine/Shader.h
        engine/renderer/Renderer.cpp
        engine/include/engine/Renderer.h
        engine/renderer/ShaderProgram.cpp
        engine/include/engine/ShaderProgram.h
        engine/renderer/Camera.cpp
        engine/include/engine/Camera.h
        )
target_include_directories(engine PRIVATE
        /usr/include/imgui
        ${PROJECT_SOURCE_DIR}/engine/include
        ${PROJECT_BINARY_DIR}/src
        )
target_compile_options(engine PRIVATE -pedantic -Wall -Wextra -Werror)
target_link_libraries(engine -lglfw -lGL -lGLEW -lspdlog -lfmt -limgui -lstb ${LIBS_LINK})
