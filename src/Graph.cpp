#include <algorithm>
#include <queue>
#include <xmath.h>
#include <set>
#include "../header/Graph.h"
#include "../header/GestaoA.h"

Graph::Graph() : n(0) {}

Graph::Graph(int nodes) : n(nodes), airports(nodes + 1) {}

void Graph::addFlight(int src, int dest, const string &airline) {
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
    for (const Airport &airport: airports) {
        if (!airport.code.empty()) airportsCode.push_back(airport);
    }
    return airportsCode;
}

string Graph::getAirportCode(const string &code) const {
    return airports.at(getAirportInfo(code)).code;
}

string Graph::getAirportName(const string &code) const {
    return airports.at(getAirportInfo(code)).name;
}

string Graph::getAirportCity(const string &code) const {
    return airports.at(getAirportInfo(code)).city;
}

string Graph::getAirportCountry(const string &code) const {
    return airports.at(getAirportInfo(code)).country;
}

long double Graph::getAirportLatitude(const string &code) const {
    return airports.at(getAirportInfo(code)).latitude;
}

long double Graph::getAirportLongitude(const string &code) const {
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
list<pair<int, string>> Graph::getAirportFlights(const string &code) const {
    list<pair<int, string>> flights;
    pair<int, string> tempPair;
    int index = getAirportInfo(code);
    if (index == 0) return {};
    for (const Flight &flight: airports.at(index).flights) {
        tempPair.first = flight.dest;
        tempPair.second = flight.airline;
        flights.push_back(tempPair);
    }
    return flights;
}

const map<string, int> &Graph::getAirportsInfo() const {
    return airportsInfo;
}

int Graph::getAirportInfo(const string &code) const {
    if (airportsInfo.find(code) != airportsInfo.end()) return airportsInfo.at(code);
    return 0;
}

void Graph::setNode(const string &code, const string &name, const string &city,
                    const string &country, long double latitude, long double longitude) {
    int airportIndex = (int) airportsInfo.size() + 1;
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

/*!
 * calcula a menor distância entre 2 pontos, através da latitude e longitude de cada ponto
 * complexidade temporal O(1)
 * @param lat1
 * @param lon1
 * @param lat2
 * @param lon2
 * @return a menor distância entre os 2 pontos
 */
static double haversine(double lat1, double lon1, double lat2, double lon2) {
    // distance between latitudes and longitudes
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return round(rad * c);
}

/**
 * calcula a distância mínima entre 2 aeroportos, bem como o caminho (voo) mais curto entre eles.
 * @param src
 * @param destination
 */
void Graph::shortestPath(const string &src, const string &destination) {
    if (airportsInfo.find(src) == airportsInfo.end()) {
        cout << "O aeroporto de origem não existe!" << endl;
        return;
    }
    if (airportsInfo.find(destination) == airportsInfo.end()) {
        cout << "O aeroporto de destino não existe!" << endl;
        return;
    }
    auto a = airportsInfo.find(src);
    Airport airportSrc = airports[a->second];

    //bfs
    for (auto &it: airportsInfo) airports[it.second].visited = false;
    vector<string> predecessor;
    queue<int> q;
    q.push(a->second);
    airportSrc.visited = true;
    GestaoA gestaoA;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (destination == airports[u].name) break;
        for (const auto &f: airports[u].flights) {
            int w = f.dest;
            if (!airports[w].visited) {
                if (gestaoA.getAirlines().empty()) {
                    q.push(w);
                    predecessor[w] = airports[u].name;
                    airports[w].visited = true;
                } /*else if (gestaoA.getAirlines().find(f.airline) != gestaoA.getAirlines().end()) {
                    q.push(w);
                    predecessor[w] = airports[u].name;
                    airports[w].visited = true;
                }*/
            }
        }
    }
    vector<string> path;
    string pre = destination;
    if (airports[getAirportInfo(destination)].visited) {
        while (pre != src) {
            path.push_back(pre);
            //pre = predecessor[pre];
        }
    } else {
        cout << "Não existe nenhum voo entre os aeroportos selecionados" << endl;
        return;
    }
    path.push_back(src);
    reverse(path.begin(), path.end());
    double distance = 0;
    cout << "Voo mais curto do aeroporto " + src + " para o aeroporto " + destination << endl;
    for (auto it = path.begin(); it != path.end(); it++) {
        if (it != path.begin()) distance += haversine((double) airports[getAirportInfo(*it)].latitude,
                                  (double) airports[getAirportInfo(*it)].longitude,
                                  (double) airports[getAirportInfo(*(it - 1))].latitude,
                                  (double) airports[getAirportInfo(*(it - 1))].longitude);
        if (it != path.end() - 1) cout << *it << " -> ";
        else cout << *it << endl;
    }
    cout << "Distância total do voo = " << distance << " km" << endl;
}