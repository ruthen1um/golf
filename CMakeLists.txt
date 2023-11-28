# Adding Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # don't build the supplied example games

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(raylib)

cmake_minimum_required(VERSION 3.27)
project(golf)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set source_dir to `src` directory of project
set(source_dir ${CMAKE_SOURCE_DIR}/src/)

# make `sources` a list of all the .cpp and .hpp files contained in source_dir
file(GLOB sources CONFIGURE_DEPENDS
    "${source_dir}/*.cpp" # add all source files
    "${source_dir}/*.hpp" # add all header files
    )

# make an executable from all files in `sources`
add_executable(${PROJECT_NAME} ${sources})

# link raylib to executable
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# target to copy assets from CMAKE_SOURCE_DIR/resources to CMAKE_BINARY_DIR/resources
add_custom_target(assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources
)

add_custom_target(config
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/cfg ${CMAKE_BINARY_DIR}/cfg
)

# add_dependencies(golf assets config)
