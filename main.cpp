#include <iostream>
#include "header/GestaoA.h"
#include "header/Airline.h"
#include "header/Airport.h"
#include "header/Flight.h"

int main() {
    GestaoA a;
    a.readAirlines();
    a.readAirports();
}
