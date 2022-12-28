#include "../header/Flight.h"

Flight::Flight(string source_, string target_, string airline_) {
    source = source_;
    target = target_;
    airline = airline_;
}

string Flight::getSource() const {return source;}

string Flight::getTarget() const {return target;}

string Flight::getAirline() const {return airline;}