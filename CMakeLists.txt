cmake_minimum_required(VERSION 3.23)
project(PasswordManager)

set(CMAKE_CXX_STANDARD 20)

add_executable(PasswordManager main.cpp Endecryptor.cpp Endecryptor.h Tui.cpp Tui.h DatabaseConnector.cpp DatabaseConnector.h entry.cpp entry.h)
