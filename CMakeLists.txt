cmake_minimum_required(VERSION 3.6)
project(Sword_MasterServer)

set(${CMAKE_PROJECT_NAME}_VERSION_MAJOR 1)
set(${CMAKE_PROJECT_NAME}_VERSION_MINOR 0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_compile_options(-std=gnu++14 -Wno-c++11-narrowing)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../OpenCLRenderer/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(Threads)
find_package(SFML 2 REQUIRED system)

set(SWORD_MASTER_SERVER_SOURCES
		${PROJECT_SOURCE_DIR}/main.cpp
		${PROJECT_SOURCE_DIR}/server.cpp)

set(SWORD_MASTER_SERVER_HEADERS
		${PROJECT_SOURCE_DIR}/server.cpp
		${PROJECT_SOURCE_DIR}/network_messages.hpp)

include_directories(
		${PROJECT_SOURCE_DIR}/
		${PROJECT_SOURCE_DIR}/../libraries
)

add_executable(${PROJECT_NAME} ${SWORD_MASTER_SERVER_SOURCES} ${SWORD_MASTER_SERVER_HEADERS})

target_link_libraries(
		${PROJECT_NAME}
		${SFML_LIBRARIES}
		${CMAKE_THREAD_LIBS_INIT})
