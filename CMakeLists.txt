cmake_minimum_required(VERSION 3.1)

project(testCSP)

ADD_DEFINITIONS(
    -std=c++11 # Or -std=c++0x
    # Other flags
)

SET(LIB_FOLDER "${CMAKE_CURRENT_SOURCE_DIR}/lib")

# include libraries
add_subdirectory("${LIB_FOLDER}/rhea")
# show headers
include_directories("${LIB_FOLDER}/rhea")
include_directories("${LIB_FOLDER}/kiwi")

# produce executables
file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/demos/*.cpp")

foreach( demoFile ${SRCS} )

    get_filename_component(demoName ${demoFile} NAME_WE)

    message(STATUS "will build : ${demoName}")

    add_executable( ${demoName} ${demoFile} )
    # Link
    target_link_libraries( ${demoName} rhea )
endforeach()
