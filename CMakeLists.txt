cmake_minimum_required(VERSION 3.6)
project(KRY_projekt1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-lgmpxx -lgmp -lssl -lcrypto")

set(SOURCE_FILES main.cpp Communicator.cpp Communicator.h IO.cpp IO.h DiffieHellman.cpp DiffieHellman.h)
add_executable(KRY_projekt1 ${SOURCE_FILES})