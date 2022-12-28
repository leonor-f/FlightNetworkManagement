#ifndef PROJETO_AED_2_GESTAOA_H
#define PROJETO_AED_2_GESTAOA_H

#include<unordered_set>
#include<string>
#include<vector>
#include "Airport.h"
#include "Airline.h"
#include "Flight.h"
#include "CityCountry.h"

using namespace std;

class GestaoA {
public:
    GestaoA();

    struct AirportHash{
        size_t operator()(const Airport& a) const{
            return hash<string>()(a.getCode());
        }

        bool operator()(const Airport& b1, const Airport& b2) const{
            return false;
        }
    };

    typedef unordered_set<Airport, AirportHash, AirportHash> tabHairports;

    struct AirlineHash{
        size_t operator()(const Airline& a) const{
            return hash<string>()(a.getCode());
        }

        bool operator()(const Airline& b1, const Airline& b2) const{
            return false;
        }
    };

    typedef unordered_set<Airline, AirlineHash, AirlineHash> tabHairlines;

    struct CityHash{
        size_t operator()(const CityCountry& city) const{
            return hash<string>()(city.getCity());
        }

        bool operator()(const CityCountry& b1, const CityCountry& b2) const{
            return false;
        }
    };

    typedef unordered_set<CityCountry, CityHash, CityHash> tabHcities;

    void readAirlines();
    void readAirports();
    void readFlights();

    pair<int, int> auxCenterDraw(int n, bool v);
    void drawMenu();
    void drawCity(CityCountry cc, bool header);
    void drawCities(vector<CityCountry> citiesaux);
    void drawAirport(Airport a, bool header);
    void drawAirports(vector<Airport> airportsaux);
    void drawAirline(Airline a, bool header);
    void drawAirlines(vector<Airline> airlinesaux);
    bool ordenar();

    void setMaxCityLength(int maxLength_);
    void setMaxCountryLength(int maxLength_);
    void setMaxAirportNameLength(int maxLength_);
    void setMaxAirlineNameLength(int maxLength_);
    void setMaxAirlineCountryLength(int maxLength_);

    tabHairports getAirports() const;
    tabHcities getCities() const;
    tabHairlines getAirlines() const;
    int getMaxCityLength() const;
    int getMaxCountryLength() const;
    int getMaxAirportNameLength() const;
    int getMaxAirlineNameLength() const;
    int getMaxAirlineCountryLength() const;

private:
    tabHairports airports;
    tabHcities cities;
    tabHairlines airlines;
    int maxCityLength = 0;
    int maxCountryLength = 0;
    int maxAirportNameLength = 0;
    int maxAirlineNameLength = 0;
    int maxAirlineCountryLength = 0;
};


#endif //PROJETO_AED_2_GESTAOA_H
