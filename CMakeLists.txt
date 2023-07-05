cmake_minimum_required(VERSION 3.12)
project(opengl-model-viewer)

set(CMAKE_CXX_STANDARD 11)

# set files
file(GLOB SOURCE_FILES CONFIGURE_DEPENDS "*.h" "*.cpp" "*.c")

set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/build)

#Include library files
include_directories(dependencies/include)
# link_directories(dependencies/library)

# copy the assets so the program can read them
# THIS DOESNT REPLACE THE FILE!!! SO IT DOESNT WORK
file(COPY resources DESTINATION ${dir}/build)
file(COPY shaders DESTINATION ${dir}/build)

add_executable(opengl-model-viewer ${SOURCE_FILES})

target_link_libraries(opengl-model-viewer ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/library/libglfw.3.3.dylib)
