cmake_minimum_required(VERSION 3.24)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 20)

add_executable(PasswordManager main.cpp Endecryptor.cpp Endecryptor.h DateTime.cpp DateTime.h)
