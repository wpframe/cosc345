cmake_minimum_required(VERSION 3.3.2)
project(MyApp C CXX)

include(cmake/App.cmake)


set(SOURCES "src/MyApp.h"
            "src/MyApp.cpp"
            "src/main.cpp"
            "src/Stock.cpp"
            "src/Headline.cpp"
            "src/Calendar.cpp"
            "src/Purchase.cpp"
            "src/Portfolio.cpp"
            )

add_app("${SOURCES}")
