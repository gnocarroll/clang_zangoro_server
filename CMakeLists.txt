cmake_minimum_required(VERSION 3.28)

if(MSVC) # will use vcpkg to get dependencies
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/CMakePresets.json)
endif()

project(zangoro_server)

# Want to enforce C99, C++11

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_compile_definitions(BOOST_ALLOW_DEPRECATED_HEADERS)
add_compile_definitions(_WEBSOCKETPP_CPP11_STL_) # have C++11 stdlib

add_executable(zangoro_server)

target_include_directories(zangoro_server
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(src)

find_package(SDL3        REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
find_package(websocketpp REQUIRED)
find_package(Boost       REQUIRED)
find_package(Threads     REQUIRED)

target_link_libraries(zangoro_server
    PRIVATE SDL3::SDL3 websocketpp::websocketpp Boost::headers Threads::Threads
)
