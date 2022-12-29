cmake_minimum_required(VERSION 3.23)
project(projeto_aed_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(projeto_aed_2 main.cpp header/GestaoA.h src/GestaoA.cpp header/Airline.h src/Airline.cpp src/Graph.cpp header/Graph.h header/Menu.h src/Menu.cpp header/CityCountry.h src/CityCountry.cpp)
