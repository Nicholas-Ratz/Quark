cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD          98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(TO_CMAKE_PATH "$ENV{HOME}" _HOME_PATH)
file(TO_CMAKE_PATH "$ENV{USERPROFILE}" _USERPROFILE_PATH)
list(APPEND CMAKE_MODULE_PATH
    "${_HOME_PATH}/.atom/CMake"
    "${_USERPROFILE_PATH}/.atom/CMake"
)
include(AtomFunctions REQUIRED)
Atom_SetupCompileCommands(SYMLINK)

project(Quark LANGUAGES CXX VERSION 1.2.0)
add_library(Quark OBJECT
    Testing.cpp
)
Atom_DetectCompiler()
Atom_SetupProject(Quark HEADER_ONLY TYPE PLUGIN)
Atom_SetupInstall(Quark TYPE PLUGIN VERSION 1.0.1 HEADER_ONLY)
