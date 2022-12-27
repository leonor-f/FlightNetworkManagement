#ifndef PROJETO_AED_2_AIRPORT_H
#define PROJETO_AED_2_AIRPORT_H

#include<string>

using namespace std;

class Airport {
public:
    Airport(string code_, string name_, string city_, string country_, float latitude_, float longitude_);

    string getCode() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    float getLatitude() const;
    float getLongitude() const;

private:
    string code;
    string name;
    string city;
    string country;
    float latitude;
    float longitude;
};


#endif //PROJETO_AED_2_AIRPORT_H
