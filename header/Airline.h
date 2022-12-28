#ifndef PROJETO_AED_2_AIRLINE_H
#define PROJETO_AED_2_AIRLINE_H

#include<string>

using namespace std;

class Airline {
public:
    Airline(string code_, string name_, string callSign_, string country_);

    string getCode() const;
    string getName() const;
    string getCallSign() const;
    string getCountry() const;

    bool operator==(const Airline &t) const;
    bool operator<(const Airline& t) const;

private:
    string code;
    string name;
    string callSign;
    string country;
};


#endif //PROJETO_AED_2_AIRLINE_H
