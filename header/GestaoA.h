#ifndef PROJETO_AED_2_GESTAOA_H
#define PROJETO_AED_2_GESTAOA_H

#include<unordered_set>
#include<string>
#include "Airport.h"
#include "Airline.h"
#include "Flight.h"

using namespace std;

struct airportHash
{
    int operator() (const Airport& b) const {
        return 0;
    }

    bool operator() (const Airport& b1, const Airport& b2) const {
        if(b1.getCode() < b2.getCode()){ return true;}
        return false;
    }
};


typedef unordered_set<Airport, airportHash, airportHash> tabHairports;

struct cityHash
{
    int operator() (const string& b) const {
        return 0;
    }

    bool operator() (const string& b1, const string& b2) const {
        if(b1 < b2){ return true;}
        return false;
    }
};


typedef unordered_set<string, cityHash, cityHash> tabHcities;

struct airlineHash
{
    int operator() (const Airline& b) const {
        return 0;
    }

    bool operator() (const Airline& b1, const Airline& b2) const {
        if(b1.getCode() < b2.getCode()){return true;}
        return false;
    }
};


typedef unordered_set<Airline, airlineHash, airlineHash> tabHairlines;


class GestaoA {
public:
    GestaoA();

    void readAirlines();
    void readAirports();
    void readFlights();

private:
    tabHairports airports;
    tabHcities cities;
    tabHairlines airlines;
};


#endif //PROJETO_AED_2_GESTAOA_H
