#include "../header/Airline.h"

Airline::Airline(string code_, string name_, string callSign_, string country_) {
    code = code_;
    name = name_;
    callSign = callSign_;
    country = country_;
}

string Airline::getCode() const {return code;}

string Airline::getName() const {return name;}

string Airline::getCallSign() const {return callSign;}

string Airline::getCountry() const {return country;}