cmake_minimum_required(VERSION 3.3.2)
project(MyApp C CXX)

# Include your custom cmake file
include(cmake/App.cmake)

# Set coverage flags
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(CMAKE_EXE_LINKER_FLAGS "--coverage")

set(SOURCES "src/MyApp.h"
            "src/MyApp.cpp"
            "src/main.cpp"
            "src/Stock.cpp"
            "src/Headline.cpp"
            "src/Calendar.cpp"
            "src/Purchase.cpp"
            "src/Portfolio.cpp"
            "src/PathUtil.cpp")

# Create the executable target
add_app("${SOURCES}")