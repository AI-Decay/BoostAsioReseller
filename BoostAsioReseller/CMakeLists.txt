# CMakeList.txt : CMake project for BoostAsioReseller, include source and define
# project specific logic here.
#

cmake_minimum_required (VERSION 3.19)
set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)

set(BOOST_ROOT "E:/boost_1_74_0/stage")
set(Boost_USE_STATIC_RUNTIME FALSE)
set(Boost_USE_STATIC_LIBS TRUE)
set(Boost_USE_MULTITHREADED TRUE)
set(THREAD_LIBRARY_DEBUG TRUE)
set(Boost_USE_DEBUG_RUNTIME FALSE)
set(Boost_COMPILER "-clang11")

find_package(Boost COMPONENTS system)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost Not found")
endif()

include_directories (${Boost_INCLUDE_DIR})

add_executable (main "src/main/main.cpp" "src/main/boost_asio_reseller.cpp" "src/main/boost_asio_reseller.h" "src/tcp_socket/tcp_listener.h" "src/tcp_socket/tcp_listener.cpp" "src/tcp_socket/detail/tcp_server.h" "src/tcp_socket/tcp_server_states.h")

target_include_directories(main PUBLIC ${Boost_INCLUDE_DIRS}) 

target_link_libraries(main ${Boost_LIBRARIES})
