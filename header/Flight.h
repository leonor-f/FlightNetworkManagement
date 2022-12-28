#ifndef PROJETO_AED_2_FLIGHT_H
#define PROJETO_AED_2_FLIGHT_H

#include<string>

using namespace std;

class Flight {
public:
    Flight(string source_, string target_, string airline_);

    string getSource() const;
    string getTarget() const;
    string getAirline() const;

private:
    string source;
    string target;
    string airline;
};


#endif //PROJETO_AED_2_FLIGHT_H
