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

float Airport::getLatitude() const {return latitude;}

float Airport::getLongitude() const {return longitude;}

bool Airport::operator==(const Airport &t) const {
    return code == t.getCode();
}

bool Airport::operator<(const Airport &t) const {
    return code < t.getCode();
}