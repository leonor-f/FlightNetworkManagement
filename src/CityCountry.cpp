#include "../header/CityCountry.h"

CityCountry::CityCountry(string city_, string country_) {
    city = city_;
    country = country_;
}

string CityCountry::getCity() const {return city;}

string CityCountry::getCountry() const {return country;}

bool CityCountry::operator==(const CityCountry &t) const {
    if((city == t.getCity() && country != t.getCountry()) || city != t.getCity()){return false;}
    return true;
}

bool CityCountry::operator<(const CityCountry &t) const {
    if(city < t.getCity() || (city == t.getCity() && country < t.getCountry())){return true;}
    return false;
}