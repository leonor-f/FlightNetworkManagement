#include "../header/airline.h"

Airline::Airline(string code_, string name_, string callsign_, string country_) {
    code = code_;
    name = name_;
    callsign = callsign_;
    country = country_;
}

string Airline::getCode() const {return code;}

string Airline::getName() const {return name;}

string Airline::getCallSign() const {return callsign;}

string Airline::getCountry() const {return country;}