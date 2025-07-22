cmake_minimum_required(VERSION 3.27)
project(Homework3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Homework3 main.cpp
        EmployeeProject2DLL.h
        EmployeeProject2DLL.cpp
        UndoStack.cpp
        UndoStack.h
)
