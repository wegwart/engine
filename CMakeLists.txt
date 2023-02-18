cmake_minimum_required(VERSION 3.18)

project(ulmer_engine VERSION 0.1)

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

add_compile_options(-Wall -Wextra -Werror)
add_subdirectory(engine)

add_executable(DemoSceneApp DemoScene.cpp)
target_link_libraries(DemoSceneApp PRIVATE engine)
