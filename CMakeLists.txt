cmake_minimum_required(VERSION 3.24)
project(projeto_aed_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(projeto_aed_2 main.cpp header/gestaoa.h src/gestaoa.cpp header/airline.h src/airline.cpp header/airport.h src/airport.cpp header/flight.h src/flight.cpp)
