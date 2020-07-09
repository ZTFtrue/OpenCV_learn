cmake_minimum_required (VERSION 2.6)

project (OpenCV_learn)

find_package( OpenCV REQUIRED )
FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
INCLUDE_DIRECTORIES(${GTK3_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTK3_LIBRARY_DIRS})

# Add other flags to the compiler
ADD_DEFINITIONS(${GTK3_CFLAGS_OTHER})

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
file(GLOB SOURCES "src/*.h" "src/*.cpp" )
add_executable(OpenCV_learn ${SOURCES} OpenCV_learn.cpp)
target_link_libraries( OpenCV_learn ${OpenCV_LIBS} ${GTK3_LIBRARIES})