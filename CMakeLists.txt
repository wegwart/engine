cmake_minimum_required(VERSION 3.24)
project(engine)

set(CMAKE_CXX_STANDARD 23)

add_executable(engine main.cpp App.h App.cpp GuiWindow.cpp GuiWindow.h OverlayWindow.cpp OverlayWindow.h)
target_include_directories(engine PRIVATE /usr/include/imgui)
target_link_libraries(engine -lglfw -lGL -lGLEW -lspdlog -lfmt -limgui -lstb)
