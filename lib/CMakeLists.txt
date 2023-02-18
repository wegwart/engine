cmake_minimum_required(VERSION 3.14)

# ------------ GLFW --------------
#set(GLFW_LIB_NAME "glfw")
#set(GLFW_INC_PATH ${GLFW_LIB_NAME}/include)
#set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
#set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
#
#add_subdirectory(${GLFW_LIB_NAME})

## ----------- spdlog -------------
#set(SPDLOG_LIB_NAME "spdlog")
#set(SPDLOG_MASTER_PROJECT OFF CACHE BOOL "" FORCE)
#
#add_subdirectory(spdlog)
#

# ------------ glm ---------------
set(GLM_LIB_NAME "glm")
set(GLM_INC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/glm)

add_library(${GLM_LIB_NAME} INTERFACE)


# ----------- imgui --------------
#set(IMGUI_LIB_NAME "imgui")
#set(IMGUI_INC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
#file(GLOB IMGUI_HEADER_FILES "${IMGUI_INC_PATH}/*.h")
#file(GLOB IMGUI_SOURCE_FILES "${IMGUI_INC_PATH}/*.cpp")
#
#add_library(${IMGUI_LIB_NAME} ${IMGUI_HEADER_FILES} ${IMGUI_SOURCE_FILES})

## ----------- imguizmo --------------
#set(IMGUIZMO_LIB_NAME "imguizmo")
#set(IMGUIZMO_INC_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo)
#file(GLOB IMGUIZMO_HEADER_FILES "${IMGUIZMO_INC_PATH}/*.h")
#file(GLOB IMGUIZMO_SOURCE_FILES "${IMGUIZMO_INC_PATH}/*.cpp")
#
#add_library(${IMGUIZMO_LIB_NAME} ${IMGUIZMO_HEADER_FILES} ${IMGUIZMO_SOURCE_FILES})
#target_link_libraries(${IMGUIZMO_LIB_NAME} ${IMGUI_LIB_NAME})
#target_include_directories(${IMGUIZMO_LIB_NAME} PUBLIC ${IMGUI_INC_PATH})

# ----------- stb_image ----------
#set(STB_IMAGE_LIB_NAME "stb_image")
#set(STB_IMAGE_INC_PATH ${CMAKE_CURRENT_SOURCE_DIR})
#
#add_subdirectory(stb_impl)

# ----------- assimp -------------
set(ASSMIP_LIB_NAME "assimp")
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Build assimp tests" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Build assimp tools" FORCE)
set(ASSIMP_NO_EXPORT ON CACHE BOOL "Do not build assimp exporters" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build assimp as shared lib" FORCE)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "Build assimp with all importers" FORCE)
set(ASSIMP_BUILD_FBX_IMPORTER ON CACHE BOOL "Build assimp with FBX importer" FORCE)
add_subdirectory(${ASSMIP_LIB_NAME})

set(LIBS_INCLUDE
        #${IMGUI_INC_PATH}
        ${GLM_INC_PATH}
        PARENT_SCOPE)

set(LIBS_LINK
        #${IMGUI_LIB_NAME}
        #${GLFW_LIB_NAME}
        #${SPDLOG_LIB_NAME}
        #${STB_IMAGE_LIB_NAME}
        ${GLM_LIB_NAME}
        ${ASSMIP_LIB_NAME}
        PARENT_SCOPE)
