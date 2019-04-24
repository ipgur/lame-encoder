cmake_minimum_required(VERSION 3.4.3)
project(lame_encoder)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_path(LAME_INCLUDE_DIR lame/lame.h)
message(STATUS ${LAME_INCLUDE_DIR} )

find_package (Threads REQUIRED)
message(STATUS ${CMAKE_THREAD_LIBS_INIT} )
find_library (LIBMP3 NAMES libmp3lame.a)
message(STATUS ${LIBMP3} )

if (NOT LIBMP3)
    message(FATAL_ERROR "No libmp3lame found")
endif ()

if(NOT LAME_INCLUDE_DIR)
    message(FATAL_ERROR "No lame.h header found")
endif()


add_executable(${PROJECT_NAME} src/main.cpp src/SimpleThreadPool.cpp src/LameEncoder.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${LAME_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} ${LIBMP3} ${CMAKE_THREAD_LIBS_INIT})