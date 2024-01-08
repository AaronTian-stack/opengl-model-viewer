cmake_minimum_required(VERSION 3.3)
project(opengl-model-viewer)

set(CMAKE_CXX_STANDARD 17)

# set files to compile
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
        ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

file(GLOB IMGUI_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include/imgui/*.cpp)
file(GLOB IMGUI_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include/imgui/*.h)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/build)

#Include library files
include_directories(dependencies/include)

add_executable(opengl-model-viewer ${SOURCE_FILES} ${IMGUI_SOURCE_FILES} ${IMGUI_HEADERS} main.cpp)

if(APPLE)
    target_link_libraries(opengl-model-viewer ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/library/libglfw.3.3.dylib)
else ()
    target_link_libraries(opengl-model-viewer ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/glfw3.dll)
endif ()