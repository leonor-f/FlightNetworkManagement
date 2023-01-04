#include <algorithm>
#include "../header/Graph.h"

Graph::Graph() : n(0) {}

Graph::Graph(int nodes) : n(nodes), airports(nodes+1) {}

void Graph::addFlight(int src, int dest, const string& airline) {
    if (src >= 1 && src <= n && dest >= 1 && dest <= n) {
        airports.at(src).flights.push_back({dest, airline, 0});
    }
}

/**
 * Junta todos os códigos não vazios.
 * Complexidade Temporal O(n) onde n é o número de aeroportos.
 * @return um vetor com todos os códigos dos aeroportos.
 */
vector<Graph::Airport> Graph::getAirports() const {
    vector<Graph::Airport> airportsCode;
    for (const Airport& airport : airports) {
        if (!airport.code.empty()) airportsCode.push_back(airport);
    }
    return airportsCode;
}

string Graph::getAirportCode(const string& code) const {
    return airports.at(getAirportInfo(code)).code;
}

string Graph::getAirportName(const string& code) const {
    return airports.at(getAirportInfo(code)).name;
}

string Graph::getAirportCity(const string& code) const {
    return airports.at(getAirportInfo(code)).city;
}

string Graph::getAirportCountry(const string& code) const {
    return airports.at(getAirportInfo(code)).country;
}

long double Graph::getAirportLatitude(const string& code) const {
    return airports.at(getAirportInfo(code)).latitude;
}

long double Graph::getAirportLongitude(const string& code) const {
    return airports.at(getAirportInfo(code)).longitude;
}

string Graph::getAirportCode(const int &dest) const {
    return airports.at(dest).code;
}

string Graph::getAirportName(const int &dest) const {
    return airports.at(dest).name;
}

string Graph::getAirportCity(const int &dest) const {
    return airports.at(dest).city;
}

string Graph::getAirportCountry(const int &dest) const {
    return airports.at(dest).country;
}

long double Graph::getAirportLatitude(const int &dest) const {
    return airports.at(dest).latitude;
}

long double Graph::getAirportLongitude(const int &dest) const {
    return airports.at(dest).longitude;
}

bool Graph::getAirportVisited(int airport) const {
    return airports.at(airport).visited;
}

/**
 * Vai buscar os voos a partir de um aeroporto inicial (parâmetro code).
 * Complexidade Temporal O(n) onde n é o número de voos num aeroporto.
 * @param code
 * @return uma lista de pares com o destino e companhia aérea de um voo.
 */
list<pair<int, string>> Graph::getAirportFlights(const string& code) const {
    list<pair<int, string>> flights;
    pair<int, string> tempPair;
    int index = getAirportInfo(code);
    if (index == 0) return {};
    for (const Flight& flight : airports.at(index).flights) {
        tempPair.first = flight.dest;
        tempPair.second = flight.airline;
        flights.push_back(tempPair);
    }
    return flights;
}

const map<string, int>& Graph::getAirportsInfo() const {
    return airportsInfo;
}

int Graph::getAirportInfo(const string& code) const {
    if (airportsInfo.find(code) != airportsInfo.end()) return airportsInfo.at(code);
    return 0;
}

void Graph::setNode(const string &code, const string &name, const string &city,
                    const string &country, long double latitude, long double longitude) {
    int airportIndex = (int)airportsInfo.size() + 1;
    airportsInfo.insert({code, airportIndex});
    airports.at(airportIndex).code = code;
    airports.at(airportIndex).name = name;
    airports.at(airportIndex).city = city;
    airports.at(airportIndex).country = country;
    airports.at(airportIndex).latitude = latitude;
    airports.at(airportIndex).longitude = longitude;
    airports.at(airportIndex).visited = false;
    airports.at(airportIndex).dist = -1;
}
