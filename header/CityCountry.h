#ifndef PROJETO_AED_2_CITYCOUNTRY_H
#define PROJETO_AED_2_CITYCOUNTRY_H
#include<string>

using namespace std;

class CityCountry {
public:
    CityCountry(string city_, string country_);

    string getCity() const;
    string getCountry() const;

    bool operator==(const CityCountry &t) const;
    bool operator<(const CityCountry &t) const;

private:
    string city;
    string country;
};


#endif //PROJETO_AED_2_CITYCOUNTRY_H
