#include <algorithm>
#include <queue>
#include <xmath.h>
#include <set>
#include "../header/Graph.h"
#include "../header/Menu.h"
#include "../header/GestaoA.h"

Graph::Graph() : n(0) {}

Graph::Graph(int nodes) : n(nodes), airports(nodes + 1) {}

void Graph::addFlight(int src, int dest, const string &airline) {
    if (src >= 1 && src <= n && dest >= 1 && dest <= n) {
        airports.at(src).flights.push_back({dest, airline});
    }
}

vector<Graph::Airport> Graph::getAirports() const { return airports; }

string Graph::getAirportName(const string &code) const { return airports.at(getAirportInfo(code)).name; }

string Graph::getAirportCountry(const string &code) const { return airports.at(getAirportInfo(code)).country; }

string Graph::getAirportCode(const int &dest) const { return airports.at(dest).code; }

string Graph::getAirportName(const int &dest) const { return airports.at(dest).name; }

string Graph::getAirportCountry(const int &dest) const { return airports.at(dest).country; }

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

int Graph::getAirportInfo(const string &code) const {
    if (airportsInfo.find(code) != airportsInfo.end()) return airportsInfo.at(code);
    return 0;
}

void Graph::setNode(const string &code, const string &name, const string &city, const string &country, long double latitude, long double longitude) {
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

/**
 * Verifica se uma airline é válida.
 * Complexidade Temporal O(n).
 * @param airline
 * @param airlines
 * @return true caso exista, falso caso contrário.
 */
bool Graph::isAirlineValid(const string &airline, const vector<string> &airlines) {
    if (airlines.empty()) return true;
    for (const string& code : airlines) if (code == airline) return true;
    return false;
}

/**
 * Depth-First Search.
 * Complexidade Temporal O(|V| + |E|).
 * @param v
 * @param u
 * @param valuesPath
 * @param airlines
 */
void Graph::dfsAirlines(int v, int u, vector<infoFlight> &valuesPath, const vector<string> &airlines) {
    airports[v].visited = true;
    infoFlight temp;
    for (const auto& e : airports[v].flights) {
        int w = e.dest;
        if (isAirlineValid(e.airline, airlines)) {
            temp.src = airports.at(v).code;
            temp.dest = airports.at(w).code;
            temp.airline = e.airline;
            valuesPath.push_back(temp);
        }
        else continue;
        if (airports[w].dist > airports[v].dist) {
            if (!airports[w].visited) {
                dfsAirlines(w, u, valuesPath, airlines);
            }
        }
    }
}

/**
 * Breadth-First Search.
 * Complexidade Temporal O(|V| + |E|).
 * @param v
 * @param airlines
 */
void Graph::bfsAirlines(int v, const vector<string> &airlines) {
    for (Airport airport : airports) {
        airport.visited = false;
        airport.dist = 0;
    }
    queue<int> q;
    q.push(v);
    airports[v].visited = true;
    airports[v].dist = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (const auto& e: airports[u].flights) {
            int w = e.dest;
            if (!airports[w].visited && isAirlineValid(e.airline, airlines)) {
                q.push(w);
                airports[w].visited = true;
                airports[w].dist = airports[u].dist + 1;
            }
        }
    }
}

/**
 * calcula a menor distância entre 2 pontos, através da latitude e longitude de cada ponto
 * complexidade temporal O(1)
 * @param lat1
 * @param lon1
 * @param lat2
 * @param lon2
 * @return a menor distância entre os 2 pontos
 */
static double haversine(double lat1, double long1, double lat2, double long2) {
    // distance between latitudes and longitudes
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (long2 - long1) * M_PI / 180.0;

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
 * Verifica se uma airline é válida.
 * Complexidade Temporal O(n).
 * @param code
 * @param airlines
 * @return true caso exista, falso caso contrário.
 */
bool Graph::auxAirlineExist(const string &code, const vector<string>& airlines) {
    for (const auto& airline : airlines) if (airline == code) return true;
    return false;
}

/**
 * A Complexidade Temporal depende do tempo que o utilizador demora a dar um input.
 * @param airlines
 * @return
 */
vector<string> Graph::airlineHelper(const vector<string>& airlines) {
    vector<string> codes;
    while (true) {
        GestaoA::drawAirlineMenu();
        string op;
        cin >> op;
        if (op.length() != 1) {
            Menu::teclaErro();
            continue;
        }
        else if (op == "1") break;
        else if (op == "2") {
            string airline;
            while (true) {
                cout << "\nInsira o codigo da companhia: ";
                cin >> airline;
                if (airline.length() != 3) {
                    Menu::teclaErro();
                    continue;
                }
                transform(airline.begin(), airline.end(), airline.begin(), ::toupper);
                if (!auxAirlineExist(airline, airlines)) Menu::companhiaNaoExiste();
                else break;
            }
            codes.push_back(airline);
            break;
        }
        else if (op == "3") {
            string airline;
            while (true) {
                cout << "\nPressione [T] para terminar\n";
                cout << "Insira o codigo da companhia: ";
                cin >> airline;
                if (airline == "t" || airline == "T") break;
                else if (airline.length() != 3) {
                    Menu::teclaErro();
                    continue;
                }
                transform(airline.begin(), airline.end(), airline.begin(), ::toupper);
                if (!auxAirlineExist(airline, airlines)) {
                    Menu::companhiaNaoExiste();
                    continue;
                }
                else codes.push_back(airline);
            }
            break;
        }
        else Menu::teclaErro();
    }
    return codes;
}

/**
 * Procura os aeroportos mais próximos das coordenadas dadas.
 * Complexidade Temporal O(|V|).
 * @param lat1
 * @param long1
 * @param lat2
 * @param long2
 */
void Graph::auxLocal(long double lat1, long double long1, long double lat2, long double long2, const vector<string>& airlines) {
    pair<int, double> parSrc, parDest; // index e distance
    double tempSrc, tempDest;
    for (int i = 1; i <= n; i++) {
        tempSrc = haversine((double)lat1, (double)long1, (double)airports.at(i).latitude, (double)airports.at(i).longitude);
        tempDest = haversine((double)lat2, (double)long2, (double)airports.at(i).latitude, (double)airports.at(i).longitude);
        if (i == 1) {
            parSrc = {i, tempSrc};
            parDest = {i, tempDest};
        }
        if (tempSrc < parSrc.second) parSrc = {i, tempSrc};
        if (tempDest < parDest.second) parDest = {i, tempDest};
    }
    auxShortestPath(getAirportCode(parSrc.first), getAirportCode(parDest.first), {}, {}, 1, airlines);
}

/**
 * Verifica se um caminho é válido.
 * Complexidade Temporal O(n^2).
 * @param indexSrc
 * @param indexDest
 * @param valuesPath
 * @param possiblePaths
 * @return
 */
bool Graph::isWayPossible(int indexSrc, int indexDest, vector<infoFlight> &valuesPath, vector<infoFlight> &possiblePaths) {
    string auxFrom = airports.at(indexSrc).code;
    string auxTo = airports.at(indexDest).code;
    int distancia = airports.at(indexDest).dist;
    bool verify = true, findWay = true;
    while (verify) {
        if (!findWay) break;
        findWay = false;
        for (const auto &values : valuesPath) {
            if (values.src == auxFrom && values.dest == auxTo) {
                verify = false;
                possiblePaths.push_back(values);
                break;
            }
            else if (values.dest == auxTo && airports.at(getAirportInfo(values.dest)).dist == distancia && airports.at(getAirportInfo(values.src)).dist == distancia-1) {
                possiblePaths.push_back(values);
                auxTo = values.src;
                distancia--;
                findWay = true;
                break;
            }
        }
    }
    return !verify;
}

/**
 * Função auxiliar para encontrar o caminho mais curto.
 * Complexidade Temporal O(n^2).
 * @param partida
 * @param dest
 * @param airlines
 * @return um par com o index e a distância do caminho mais curto.
 */
pair<int, int> Graph::auxSPTH(const vector<string> &partida, const string &dest, const vector<string> &airlines) {
    pair<int, int> minFlights; // primeiro é o index e o segundo é a dist
    minFlights.first = 0;
    minFlights.second = 0;
    bool checked = false;
    for (int i = 0; i < partida.size(); i++) {
        bfsAirlines(getAirportInfo(partida.at(i)), airlines);

        vector<infoFlight> valuesPath, possiblePaths;
        for (Airport& airport : airports) airport.visited = false;
        dfsAirlines(getAirportInfo(partida.at(i)), getAirportInfo(dest), valuesPath, airlines);

        bool verify = isWayPossible(getAirportInfo(partida.at(i)), getAirportInfo(dest), valuesPath, possiblePaths);
        if (verify && checked) {
            if ((minFlights.second == 0 && airports.at(getAirportInfo(dest)).dist > 0) || (airports.at(getAirportInfo(dest)).dist < minFlights.second && airports.at(getAirportInfo(dest)).dist > 0))
                minFlights = {i, airports.at(getAirportInfo(dest)).dist};
        }
        else if (verify) {
            minFlights = {i, airports.at(getAirportInfo(dest)).dist};
            checked = true;
        }
    }
    return minFlights;
}

/**
 * Escolhe o destino mais próximo em termos do número de voos necessário.
 * Complexidade Temporal O(n^2).
 * @param src
 * @param chegada
 * @return de um par com o índice do aeroporto e o número de voos.
 */
pair<int, int> Graph::auxSPTW(const string &src, const vector<string> &chegada, const vector<string>& airlines) {
    bfsAirlines(getAirportInfo(src), airlines);
    pair<int, int> minFlights; // primeiro é o index e o segundo é a dist
    minFlights.first = 0;
    minFlights.second = 0;
    bool checked = false;
    for (int i = 0; i < chegada.size(); i++) {
        vector<infoFlight> valuesPath, possiblePaths;
        for (Airport& airport : airports) airport.visited = false;
        dfsAirlines(getAirportInfo(src), getAirportInfo(chegada.at(i)), valuesPath, airlines);

        bool verify = isWayPossible(getAirportInfo(src), getAirportInfo(chegada.at(i)), valuesPath, possiblePaths);
        if (verify && checked) {
            if ((minFlights.second == 0 && airports.at(getAirportInfo(chegada.at(i))).dist > 0) || (airports.at(getAirportInfo(chegada.at(i))).dist < minFlights.second && airports.at(getAirportInfo(chegada.at(i))).dist > 0))
                minFlights = {i, airports.at(getAirportInfo(chegada.at(i))).dist};
        }
        else if (verify) {
            minFlights = {i, airports.at(getAirportInfo(chegada.at(i))).dist};
            checked = true;
        }
    }
    return minFlights;
}

/**
 * Dependendo dos inputs, é associado um tipo e dependendo desse tipo escolhe o aeroporto de partida e de chegada.
 * Complexidade Temporal depende do tipo.
 * @param src
 * @param dest
 * @param partida
 * @param chegada
 * @param type
 */
void Graph::auxShortestPath(const string &src, const string &dest, const vector<string>& partida,  const vector<string>& chegada, int type, const vector<string>& airlines) {
    vector<string> codes = airlineHelper(airlines);
    if (type == 1) {
        bfsAirlines(getAirportInfo(src), codes);
        shortestPath(src, dest, codes);
    }
    else if (type == 2) {
        pair<int, int> minFlights = auxSPTW(src, chegada, codes); // primeiro é o index e o segundo é a dist
        shortestPath(src, chegada.at(minFlights.first), codes);
    }
    else if (type == 3) {
        pair<int, int> minFlights = auxSPTH(partida, dest, codes); // primeiro é o index e o segundo é a dist
        shortestPath(partida.at(minFlights.first), dest, codes);
    }
    else if (type == 4) {
        pair<int, int> minFlights, temp;
        int bestSrc;
        for (int i = 0; i < partida.size(); i++) {
            temp = auxSPTW(partida.at(i), chegada, codes);
            if (i == 0 || (minFlights.second == 0 && temp.second > 0 || temp.second < minFlights.second && temp.second > 0)) {
                minFlights = temp;
                bestSrc = i;
            }
        }
        bfsAirlines(getAirportInfo(partida.at(bestSrc)), airlines);
        shortestPath(partida.at(bestSrc), chegada.at(minFlights.first), codes);
    }
}
/**
 * Calcula a distância mínima entre 2 aeroportos, bem como o caminho (voo) mais curto entre eles.
 * Complexidade Temporal O(n).
 * @param src
 * @param dest
 */
void Graph::shortestPath(const string &src, const string &dest, const vector<string>& airlineCodes) {
    int indexSrc = getAirportInfo(src);
    int indexDest = getAirportInfo(dest);

    if (airports.at(indexDest).dist == 0) {
        Menu::semCaminhoPossivel();
        return;
    }

    vector<infoFlight> valuesPath, possiblePaths;

    for (Airport& airport : airports) airport.visited = false;
    dfsAirlines(indexSrc, indexDest, valuesPath, airlineCodes);

    bool verify = isWayPossible(indexSrc, indexDest, valuesPath, possiblePaths);
    if (!verify) {
        Menu::caminhoCompanhiaPossivel();
        return;
    }
    reverse(possiblePaths.begin(), possiblePaths.end());
    cout << endl;
    string voo;
    if (airports.at(indexDest).dist == 1) voo = " voo.";
    else voo = " voos.";
    cout << "Um dos melhores trajetos (menor numero de voos) do aeroporto " << src << " para " << dest << " utiliza " << airports.at(indexDest).dist << voo << endl;

    double distance = 0, temp;
    for (const infoFlight& par : possiblePaths) {
        temp = haversine((double) airports[getAirportInfo(par.src)].latitude,
                         (double) airports[getAirportInfo(par.src)].longitude,
                         (double) airports[getAirportInfo(par.dest)].latitude,
                         (double) airports[getAirportInfo(par.dest)].longitude);
        distance += temp;
        cout << par.src << " -> " << par.dest << ": " << temp << " km" << " (" << par.airline << ")" << endl;
    }
    cout << "\nDistancia total do voo = " << distance << " km" << endl;
}

/**
 * Procura os aeroportos de uma determinada cidade.
 * Complexidade temporal O(n).
 * @param city
 * @return um vetor com os códigos dos aeroportos encontrados.
 */
vector<string> Graph::getAirportsByCityCountry(const CityCountry &city) {
    vector<string> aux;
    for (const Airport& airport : airports) {
        if (airport.city == city.getCity() && airport.country == city.getCountry())
            aux.push_back(airport.code);
    }
    return aux;
}
