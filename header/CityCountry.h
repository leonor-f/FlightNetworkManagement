#ifndef CITYCOUNTRY_H
#define CITYCOUNTRY_H

#include<string>

using namespace std;

class CityCountry {
public:
    CityCountry();
    CityCountry(const string& city, const string& country);

    string getCity() const;
    string getCountry() const;

    void setCity(const string &city);
    void setCountry(const string &country);

    bool operator==(const CityCountry &t) const;
    bool operator<(const CityCountry &t) const;

private:
    string city_;
    string country_;
};


#endif
