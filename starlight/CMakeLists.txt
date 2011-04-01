cmake_minimum_required(VERSION 2.4)

project(starlight)

option(BOX2D_INSTALL "Install Box2D libs, includes, and CMake scripts" OFF)
option(BOX2D_INSTALL_DOC "Install Box2D documentation" OFF)
option(BOX2D_BUILD_SHARED "Build Box2D shared libraries" OFF)
option(BOX2D_BUILD_STATIC "Build Box2D static libraries" ON)
option(BOX2D_BUILD_EXAMPLES "Build Box2D examples" OFF)

set(BOX2D_VERSION 2.1.0)

# The starlight project and dependencies.
find_package(OpenGL REQUIRED)
add_subdirectory(freeglut)
add_subdirectory(Box2D)
add_subdirectory(inet)
add_subdirectory(starlight)

