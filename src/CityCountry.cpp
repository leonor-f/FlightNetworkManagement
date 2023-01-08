#include "../header/CityCountry.h"

CityCountry::CityCountry() {
    city_ = "";
    country_ = "";
}

CityCountry::CityCountry(const string& city, const string& country) {
    city_ = city;
    country_ = country;
}

string CityCountry::getCity() const { return city_; }

string CityCountry::getCountry() const { return country_; }

bool CityCountry::operator==(const CityCountry &t) const {
    if ((city_ == t.getCity() && country_ != t.getCountry()) || city_ != t.getCity()) return false;
    return true;
}

bool CityCountry::operator<(const CityCountry &t) const {
    if (city_ < t.getCity() || (city_ == t.getCity() && country_ < t.getCountry())) return true;
    return false;
}
