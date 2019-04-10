# dunno, guess nobody uses older ones anymore?
cmake_minimum_required(VERSION 3.0)

project(shiny-spork)
find_package(SFML 2.4 COMPONENTS network graphics audio window system REQUIRED)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Weffc++ -pedantic")
set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE INCLUDE include/*.h)
file(GLOB_RECURSE SOURCE src/*.cpp)

add_executable(start ${SOURCE} ${INCLUDE})

target_include_directories(start PRIVATE include)
target_include_directories(start PRIVATE assets)
target_link_libraries(start sfml-network sfml-graphics sfml-audio sfml-window sfml-system)
