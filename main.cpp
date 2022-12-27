#include <iostream>
#include "header/gestaoa.h"
#include "header/airline.h"
#include "header/airport.h"
#include "header/flight.h"

int main() {
    GestaoA a;
    a.readAirlines();
    a.readAirports();
}
