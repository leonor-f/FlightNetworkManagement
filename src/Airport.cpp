#include "../header/Airport.h"

Airport::Airport(string code_, string name_, string city_, string country_, float latitude_, float longitude_) {
    code = code_;
    name = name_;
    city = city_;
    country = country_;
    latitude = latitude_;
    longitude = longitude_;
}

string Airport::getCode() const {return code;}

string Airport::getName() const {return name;}

string Airport::getCity() const {return city;}

string Airport::getCountry() const {return country;}