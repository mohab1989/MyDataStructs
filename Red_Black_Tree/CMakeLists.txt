
# Set cmake minimum version required
cmake_minimum_required(VERSION 3.2)

# Name Project
project(Red_Black_Tree)

# Project version number
set(RED_BLACK_TREE_VERSION_MAJOR 1)
set(RED_BLACK_TREE_VERSION_MINOR 0)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(
"${PROJECT_SOURCE_DIR}/red_black_tree_version.h.in"
"${PROJECT_SOURCE_DIR}/include/red_black_tree_version.h"
)

include(FindOpenMP)
if(OPENMP_FOUND)
    message(-- Found OpenMP)
    message(-- OpenMP_CXX_FLAGS: )
    message(-- OpenMP_EXE_LINKER_FLAGS: )

    set(CMAKE_C_FLAGS  )
    set(CMAKE_CXX_FLAGS  )
    set(CMAKE_EXE_LINKER_FLAGS  )
else()
    message(WARNING -- Couldnt Find OpenMP)
endif()

# Set Variables
set(SOURCE_FILES src/red_black_tree.cpp)

# Add SOURCE_FILES to executable/library
add_executable(Red_Black_Tree ${SOURCE_FILES})

# Add include directories
target_include_directories(Red_Black_Tree PUBLIC ${PROJECT_SOURCE_DIR}/include)

# linking with threads library to enable multithreading 
target_link_libraries(Red_Black_Tree Threads::Threads)

# Set some properties (standard)
set_target_properties(Red_Black_Tree PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED OFF
    CXX_EXTENSIONS OFF
    )
# Export compile command json file for use with source trail and YCM
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Add find GMock.cmake module to cmake modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

# Find Gtest and GMock packages
find_package(GTest)
find_package(GMock)
if(NOT GTEST_FOUND)
    message(WARNING "GTest couldn't be found")
else()
    message("GTest Found")
endif()
if(NOT GMOCK_FOUND)
    message(WARNING "GMock couldn't be found")
else()
    message("GMock Found")
endif()

if(GTEST_FOUND AND GMOCK_FOUND)
# Set testing project sources 
set(TESTING_SOURCES ${PROJECT_SOURCE_DIR}/tests/red_black_tree_test.cpp)

# Make Testing executable
add_executable(Red_Black_Tree_testing ${TESTING_SOURCES})

# Include Project's Include dir plus Gtest and GMock include dirs
target_include_directories(Red_Black_Tree_testing PUBLIC ${PROJECT_SOURCE_DIR}/include ${GTEST_INCLUDE_DIRS} ${GMOCK_INCLUDE_DIRS})

# Link with Gtest and GMock libs
target_link_libraries(Red_Black_Tree_testing GTest::GTest GTest::Main ${GMOCK_BOTH_LIBRARIES} Threads::Threads)

set_target_properties(Red_Black_Tree_testing PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED OFF
    CXX_EXTENSIONS OFF
    )
# Enabling testing
enable_testing()
add_test(Red_Black_Tree_test testing_project_name)
endif()

