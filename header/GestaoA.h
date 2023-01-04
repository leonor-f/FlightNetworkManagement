#ifndef GESTAOA_H
#define GESTAOA_H

#include <unordered_set>
#include <string>
#include <vector>
#include <set>
#include "Graph.h"
#include "Airline.h"
#include "CityCountry.h"

using namespace std;

class GestaoA {
    public:
        GestaoA();

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

        static pair<int, int> auxCenterDraw(int n, bool v);
        static void drawMenu();
        static void drawNumberMenu();
        static void drawYMenu();
        void drawCity(const CityCountry& cc, bool header) const;
        void drawCities(const vector<CityCountry>& citiesaux) const;
        void drawAirport(const string& code, bool header);
        void drawAirports(const vector<string>& airports);
        void drawAirline(const Airline& a, bool header) const;
        void drawAirlines(const vector<Airline>& airlinesaux) const;
        void drawFlight(const string& name, const string& airline, bool header);
        void drawFlights(const string& code);
        void drawNumberOfAirlines(const string& code);
        void drawNumberOfTargets(const string& code);
        void drawNumberOfCountries(const string& code);
        void drawYairports(string code, int y);
        void drawYcities(string code, int y);
        void drawYcountries(string code, int y);

        set<int> Yairports(string code, int y);
        set<CityCountry> Ycities(string code, int y);
        set<string> Ycountries(string code, int y);
        static bool ordenar();

        void setMaxCityLength(int maxLength_);
        void setMaxCountryLength(int maxLength_);
        void setMaxAirportNameLength(int maxLength_);
        void setMaxAirlineNameLength(int maxLength_);
        void setMaxAirlineCountryLength(int maxLength_);

        vector<Graph::Airport> getAirports() const;
        tabHcities getCities() const;
        tabHairlines getAirlines() const;
        Graph getFlightNetwork() const;
        int getMaxCityLength() const;
        int getMaxCountryLength() const;
        int getMaxAirportNameLength() const;
        int getMaxAirlineNameLength() const;
        int getMaxAirlineCountryLength() const;

    private:
        tabHcities cities;
        tabHairlines airlines;
        Graph flightNetwork_;
        int maxCityLength = 0;
        int maxCountryLength = 0;
        int maxAirportNameLength = 0;
        int maxAirlineNameLength = 0;
        int maxAirlineCountryLength = 0;
};


#endif
