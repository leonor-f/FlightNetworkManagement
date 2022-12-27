#ifndef PROJETO_AED_2_AIRLINE_H
#define PROJETO_AED_2_AIRLINE_H

#include<string>

using namespace std;

class Airline {
public:
    Airline(string code_, string name_, string callsign_, string country_);

    string getCode() const;
    string getName() const;
    string getCallSign() const;
    string getCountry() const;

private:
    string code;
    string name;
    string callsign;
    string country;
};


#endif //PROJETO_AED_2_AIRLINE_H
