cmake_minimum_required(VERSION 3.23)
project(projeto_aed_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(projeto_aed_2 main.cpp header/GestaoA.h src/GestaoA.cpp header/Airline.h src/Airline.cpp header/Airport.h src/Airport.cpp header/Flight.h src/Flight.cpp header/menu.h src/menu.cpp header/CityCountry.h src/CityCountry.cpp)
