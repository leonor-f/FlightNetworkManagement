#include <fstream>
#include <sstream>
#include <iostream>
#include "../header/Airline.h"
#include "../header/Airport.h"
#include "../header/Flight.h"
#include "../header/GestaoA.h"

using namespace std;

GestaoA::GestaoA() {
    airports.clear();
    cities.clear();
    airlines.clear();

    tabHairports ap;
    airports = ap;
    tabHcities c;
    cities = c;
    tabHairlines al;
    airlines = al;
}

void GestaoA::readAirlines() {
    ifstream file("../resources/airlines.csv");

    string line;
    getline(file, line);

    while (getline(file, line)) {
        string code, name, callSign, country;

        istringstream stream(line);
        getline(stream, code, ',');
        getline(stream, name, ',');
        getline(stream, callSign, ',');
        getline(stream, country, ',');

        Airline airline = Airline(code, name, callSign, country);
        airlines.insert(airline);
    }
    readAirports();
}

void GestaoA::readAirports() {
    ifstream file("../resources/airports.csv");

    string line;
    getline(file, line);

    while (getline(file, line)) {
        string code, name, city, country, latitude, longitude;
        float latitudeF, longitudeF;

        istringstream stream(line);
        getline(stream, code, ',');
        getline(stream, name, ',');
        getline(stream, city, ',');
        getline(stream, country, ',');
        getline(stream, latitude, ',');
        getline(stream, longitude, ',');

        latitudeF = stof(latitude);
        longitudeF = stof(longitude);

        if (!existsCity(city)) cities.insert(city);

        Airport airport = Airport(code, name, city, country, latitudeF, longitudeF);
        airports.insert(airport);
    }
    readFlights();
}

bool GestaoA::existsCity(const string &city) {
    return cities.find(city)->empty() || cities.empty();
}

void GestaoA::readFlights() {

}