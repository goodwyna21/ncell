cmake_minimum_required(VERSION 3.29)
project(ncell)
set(appname ncell)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

add_subdirectory(src)
#add_subdirectory(test)

#enable_testing
