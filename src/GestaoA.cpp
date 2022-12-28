#include <fstream>
#include <sstream>
#include <iostream>
#include<set>
#include "../header/Airline.h"
#include "../header/Airport.h"
#include "../header/Flight.h"
#include "../header/menu.h"
#include "../header/CityCountry.h"
#include "../header/GestaoA.h"

using namespace std;

GestaoA::GestaoA() {
    tabHairports ap;
    airports = ap;
    tabHcities c;
    cities = c;
    tabHairlines al;
    airlines = al;
}

void GestaoA::readAirlines() {
    string ficheiro = "../resources/airlines.csv";
    ifstream ifs1;
    ifs1.open(ficheiro, ios::in);
    string line;
    getline(ifs1, line);

    while (getline(ifs1, line)) {
        string code, name, callSign, country;

        istringstream stream(line);
        getline(stream, code, ',');
        getline(stream, name, ',');
        getline(stream, callSign, ',');
        getline(stream, country, '\r');

        if(name.length() > getMaxAirlineNameLength()){setMaxAirlineNameLength(name.length());}
        if(country.length() > getMaxAirlineCountryLength()){setMaxAirlineCountryLength(country.length());}

        Airline airline = Airline(code, name, callSign, country);
        airlines.insert(airline);
    }
    ifs1.close();
}

void GestaoA::readAirports() {
    string ficheiro = "../resources/airports.csv";
    ifstream ifs2;
    ifs2.open(ficheiro, ios::in);
    string line;
    getline(ifs2, line);
    set<CityCountry> cityset;

    while (getline(ifs2, line)) {
        string code, name, city, country, latitude, longitude;
        float latitudeF, longitudeF;

        istringstream stream(line);
        getline(stream, code, ',');
        getline(stream, name, ',');
        getline(stream, city, ',');
        getline(stream, country, ',');
        getline(stream, latitude, ',');
        getline(stream, longitude, '\r');

        latitudeF = stof(latitude);
        longitudeF = stof(longitude);

        CityCountry cc(city, country);
        cityset.insert(cc);
        if(city.length() > getMaxCityLength()){setMaxCityLength(city.length());}
        if(country.length() > getMaxCountryLength()){setMaxCountryLength(country.length());}
        if(name.length() > getMaxAirportNameLength()){setMaxAirportNameLength(name.length());}

        Airport airport = Airport(code, name, city, country, latitudeF, longitudeF);
        airports.insert(airport);
    }
    for(auto i: cityset){
        cities.insert(i);
    }
    ifs2.close();
}

void GestaoA::readFlights() {
    return;
}

/**
 * Função para ajudar a centralizar textos.
 * @param n
 * @param v
 * @return
 */
pair<int, int> GestaoA::auxCenterDraw(int n, bool v) {
    int pad1 = n;
    int pad2;
    if (v) {
        pad2 = pad1+1;
    }
    else {
        pad2 = pad1;
    }
    return pair<int, int> {pad1, pad2};
}

/**
 * Desenho do Menu principal
 * Complexidade Temporal O(1)
 */
void GestaoA::drawMenu() {
    cout << "\n+---------------------------------------------+\n"
            "|           GESTAO DE AEROPORTOS              |\n"
            "+---------------------------------------------+\n"
            "| [1] - Listar Cidades                        |\n"
            "| [2] - Listar Aeroportos                     |\n"
            "| [3] - Listar Airlines                       |\n"
            "| [Q] - Sair da aplicacao                     |\n"
            "+---------------------------------------------+\n";
    cout << "\nEscolha a opcao e pressione ENTER:";
}

void GestaoA::drawCity(CityCountry cc, bool header) {
    if (header) {
        cout << "\n+-----------------------------------------------------------------+\n"
                "|             CITY              |             COUNTRY             |\n"
                "+-----------------------------------------------------------------+\n";
        }
    cout << "|";
    pair<int, int> pad = auxCenterDraw(getMaxCityLength() - (int)cc.getCity().length(), (int)cc.getCity().length()%2 == 0);
    for (int f = 0; f < pad.first; f++) {
        cout << " ";
        ++f;
    }
    cout << cc.getCity();
    for (int e = 0; e < pad.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|";
    pair<int, int> padCountry = auxCenterDraw(getMaxCountryLength() - (int)cc.getCountry().length(), (int)cc.getCountry().length()%2 == 0);
    for (int f = 0; f < padCountry.first; f++) {
        cout << " ";
        ++f;
    }
    cout << cc.getCountry();
    for (int e = 0; e < padCountry.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|" << "\n";
}

void GestaoA::drawCities(vector<CityCountry> citiesaux) {
    bool v = true;
    for (const CityCountry& s : citiesaux) {
        drawCity(s, v);
        v = false;
    }
    cout << "+-----------------------------------------------------------------+\n";
}

void GestaoA::drawAirport(Airport a, bool header) {
    if (header) {
        cout << "\n+------------------------------------------------------------------------------------------------+\n"
                "| COD |                          NAME                          |             COUNTRY             |\n"
                "+------------------------------------------------------------------------------------------------+\n";
    }
    cout << "| " << a.getCode() << " |";
    pair<int, int> pad = auxCenterDraw(getMaxAirportNameLength() - (int)a.getName().length(), (int)a.getName().length()%2 == 1);
    for (int f = 0; f < pad.first; f++) {
        cout << " ";
        ++f;
    }
    cout << a.getName();
    for (int e = 0; e < pad.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|";
    pair<int, int> padCountry = auxCenterDraw(getMaxCountryLength() - (int)a.getCountry().length(), (int)a.getCountry().length()%2 == 0);
    for (int f = 0; f < padCountry.first; f++) {
        cout << " ";
        ++f;
    }
    cout << a.getCountry();
    for (int e = 0; e < padCountry.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|" << "\n";
}

void GestaoA::drawAirports(vector<Airport> airportsaux) {
    bool v = true;
    for (const Airport& s: airportsaux) {
        drawAirport(s, v);
        v = false;
    }
    cout << "+------------------------------------------------------------------------------------------------+\n";
}

void GestaoA::drawAirline(Airline a, bool header) {
    if (header) {
        cout << "\n+---------------------------------------------------------------------------------------+\n"
                "| COD |                  NAME                    |                COUNTRY               |\n"
                "+---------------------------------------------------------------------------------------+\n";
    }
    cout << "| " << a.getCode() << " |";
    pair<int, int> pad = auxCenterDraw(getMaxAirlineNameLength() - (int)a.getName().length(), (int)a.getName().length()%2 == 1);
    for (int f = 0; f < pad.first; f++) {
        cout << " ";
        ++f;
    }
    cout << a.getName();
    for (int e = 0; e < pad.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|";
    pair<int, int> padCountry = auxCenterDraw(getMaxAirlineCountryLength() - (int)a.getCountry().length(), (int)a.getCountry().length()%2 == 1);
    for (int f = 0; f < padCountry.first; f++) {
        cout << " ";
        ++f;
    }
    cout << a.getCountry();
    for (int e = 0; e < padCountry.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|" << "\n";
}

void GestaoA::drawAirlines(vector<Airline> airlinesaux) {
    bool v = true;
    for (const Airline& s: airlinesaux) {
        drawAirline(s, v);
        v = false;
    }
    cout << "+---------------------------------------------------------------------------------------+\n";
}

bool GestaoA::ordenar() {
    string op;
    while (true) {
        cout << "\nDeseja ordenacao ascendente ou descendente? [A/D]:";
        cin >> op;
        if (op == "A" || op == "a") return true;
        else if (op == "D" || op == "d") return false;
        else Menu::teclaErro();
    }
}

void GestaoA::setMaxCityLength(int maxLength_) {
    maxCityLength = maxLength_;
}

void GestaoA::setMaxCountryLength(int maxLength_) {
    maxCountryLength = maxLength_;
}

void GestaoA::setMaxAirportNameLength(int maxLength_) {
    maxAirportNameLength = maxLength_;
}

void GestaoA::setMaxAirlineNameLength(int maxLength_) {
    maxAirlineNameLength = maxLength_;
}

void GestaoA::setMaxAirlineCountryLength(int maxLength_) {
    maxAirlineCountryLength = maxLength_;
}

GestaoA::tabHairports GestaoA::getAirports() const {return airports;}

GestaoA::tabHairlines GestaoA::getAirlines() const {return airlines;}

GestaoA::tabHcities GestaoA::getCities() const {return cities;}

int GestaoA::getMaxCityLength() const {return maxCityLength;}

int GestaoA::getMaxCountryLength() const {return maxCountryLength;}

int GestaoA::getMaxAirportNameLength() const {return maxAirportNameLength;}

int GestaoA::getMaxAirlineNameLength() const {return maxAirlineNameLength;}

int GestaoA::getMaxAirlineCountryLength() const {return maxAirlineCountryLength;}