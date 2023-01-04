#include <fstream>
#include <sstream>
#include <iostream>
#include<set>
#include<queue>
#include "../header/Airline.h"
#include "../header/Graph.h"
#include "../header/Menu.h"
#include "../header/GestaoA.h"

using namespace std;

GestaoA::GestaoA() {
    flightNetwork_ = Graph(3019);
    tabHcities c;
    cities = c;
    tabHairlines al;
    airlines = al;
}

/**
 * Lê o ficheiro airlines.csv e guarda todas as companhias aéreas.
 * Complexidade Temporal O(n) (n é o tamanho do ficheiro retirando o cabeçalho).
 */
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

        if (name.length() > getMaxAirlineNameLength()) setMaxAirlineNameLength((int)name.length());
        if (country.length() > getMaxAirlineCountryLength()) setMaxAirlineCountryLength((int)country.length());

        Airline airline = Airline(code, name, callSign, country);
        airlines.insert(airline);
    }
    ifs1.close();
}

/**
 * Lê o ficheiro airports.csv e vai colocando os aerportos no grafo, assim como guarda todas as cidades diferentes.
 * Complexidade Temporal O(n) (n é o tamanho do ficheiro retirando o cabeçalho).
 */
void GestaoA::readAirports() {
    string ficheiro = "../resources/airports.csv";
    ifstream ifs2;
    ifs2.open(ficheiro, ios::in);
    string line;
    getline(ifs2, line);
    set<CityCountry> cityset;

    while (getline(ifs2, line)) {
        string code, name, city, country, latitude, longitude;
        long double latitudeLD, longitudeLD;

        istringstream stream(line);
        getline(stream, code, ',');
        getline(stream, name, ',');
        getline(stream, city, ',');
        getline(stream, country, ',');
        getline(stream, latitude, ',');
        getline(stream, longitude, '\r');

        latitudeLD = stold(latitude);
        longitudeLD = stold(longitude);

        CityCountry cc(city, country);
        cityset.insert(cc);
        if (city.length() > getMaxCityLength()) setMaxCityLength((int)city.length());
        if (country.length() > getMaxCountryLength()) setMaxCountryLength((int)country.length());
        if (name.length() > getMaxAirportNameLength()) setMaxAirportNameLength((int)name.length());

        flightNetwork_.setNode(code, name, city, country, latitudeLD, longitudeLD);
    }
    for (const auto& i: cityset)
        cities.insert(i);
    ifs2.close();
}

/**
 *
 * Complexidade Temporal O(n) (n é o tamanho do ficheiro retirando o cabeçalho).
 */
void GestaoA::readFlights() {
    string ficheiro = "../resources/flights.csv";
    ifstream ifs3;
    ifs3.open(ficheiro, ios::in);
    string line;
    getline(ifs3, line);

    while (getline(ifs3, line)) {
        string source, destination, airline;

        istringstream stream(line);
        getline(stream, source, ',');
        getline(stream, destination, ',');
        getline(stream, airline, '\r');

        int src = flightNetwork_.getAirportInfo(source);
        int dest = flightNetwork_.getAirportInfo(destination);

        flightNetwork_.addFlight(src, dest, airline);
    }
    ifs3.close();
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
 * Desenho do Menu principal.
 * Complexidade Temporal O(1).
 */
void GestaoA::drawMenu() {
    cout << "\n+---------------------------------------------+\n"
            "|           GESTAO DE AEROPORTOS              |\n"
            "+---------------------------------------------+\n"
            "| [1] - Listar Cidades                        |\n"
            "| [2] - Listar Aeroportos                     |\n"
            "| [3] - Listar Companhias                     |\n"
            "| [4] - Listar Voos                           |\n"
            "| [5] - N a partir de um Aeroporto            |\n" // irá abrir novo menu
            "| [6] - Destinos com maximo de Y voos         |\n" // irá abrir novo menu
            "| [Q] - Sair da aplicacao                     |\n"
            "+---------------------------------------------+\n";
    cout << "\nEscolha a opcao e pressione ENTER:";
}

/**
 * Desenho de um menu secundário para mais opções.
 * Complexidade Temporal O(1).
 */
void GestaoA::drawNumberMenu() {
    cout << "\n+-----------------------------------------------------+\n"
            "|                GESTAO DE AEROPORTOS                 |\n"
            "+-----------------------------------------------------+\n"
            "| [1] - N Companhias Aereas num Aeroporto             |\n"
            "| [2] - N Destinos Diferentes a partir de um Aeroporto|\n"
            "| [3] - N Paises Diferentes a partir de um Aeroporto  |\n"
            "| [V] - Voltar                                        |\n"
            "+-----------------------------------------------------+\n";
    cout << "\nEscolha a opcao e pressione ENTER:";
}

/**
 * Desenho de um menu secundário para mais opções.
 * Complexidade Temporal O(1).
 */
void GestaoA::drawYMenu() {
    cout << "\n+---------------------------------------------------+\n"
            "|                GESTAO DE AEROPORTOS               |\n"
            "+---------------------------------------------------+\n"
            "| [1] - Aeroportos Atingiveis num maximo de Y voos  |\n"
            "| [2] - Cidades Atingiveis num maximo de Y voos     |\n"
            "| [3] - Paises Atingiveis num maximo de Y voos      |\n"
            "| [V] - Voltar                                      |\n"
            "+---------------------------------------------------+\n";
    cout << "\nEscolha a opcao e pressione ENTER:";
}

/**
 * Desenha uma cidade (parâmetro cc) e identifica se é a 1ª cidade a ser escrita para desenhar o cabeçalho da tabela (parâmetro header).
 * Complexidade Temporal O(n).
 * @param cc
 * @param header
 */
void GestaoA::drawCity(const CityCountry& cc, bool header) const {
    if (header) {
        cout << "\n+-------------------------------+---------------------------------+\n"
                "|             CITY              |             COUNTRY             |\n"
                "+-------------------------------+---------------------------------+\n";
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

/**
 * Desenha todas as cidades e chama a função drawCity para desenhar uma de cada vez.
 * Complexidade Temporal O(n^2).
 * @param citiesaux
 */
void GestaoA::drawCities(const vector<CityCountry>& citiesaux) const {
    bool v = true;
    for (const CityCountry& s : citiesaux) {
        drawCity(s, v);
        v = false;
    }
    cout << "+-------------------------------+---------------------------------+\n";
}

/**
 * Desenha uma aeroporto e identifica se é o 1º aeroporto a ser escrito para desenhar o cabeçalho da tabela (parâmetro header).
 * Complexidade Temporal O(n).
 * @param code
 * @param header
 */
void GestaoA::drawAirport(const string& code, bool header) {
    if (header) {
        cout << "\n+-----+--------------------------------------------------------+---------------------------------+\n"
                "| COD |                          NAME                          |             COUNTRY             |\n"
                "+-----+--------------------------------------------------------+---------------------------------+\n";
    }
    cout << "| " << code << " |";
    pair<int, int> pad = auxCenterDraw(getMaxAirportNameLength() - (int)flightNetwork_.getAirportName(code).length(), (int)flightNetwork_.getAirportName(code).length()%2 == 1);
    for (int f = 0; f < pad.first; f++) {
        cout << " ";
        ++f;
    }
    cout << flightNetwork_.getAirportName(code);
    for (int e = 0; e < pad.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|";
    pair<int, int> padCountry = auxCenterDraw(getMaxCountryLength() - (int)flightNetwork_.getAirportCountry(code).length(), (int)flightNetwork_.getAirportCountry(code).length()%2 == 0);
    for (int f = 0; f < padCountry.first; f++) {
        cout << " ";
        ++f;
    }
    cout << flightNetwork_.getAirportCountry(code);
    for (int e = 0; e < padCountry.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|" << "\n";
}

/**
 * Desenha todos os aeroportos e chama a função drawAirport para desenhar uma de cada vez.
 * Complexidade Temporal O(n^2).
 * @param airports
 */
void GestaoA::drawAirports(const vector<string>& airports) {
    bool v = true;
    for (int i = 1; i < airports.size(); i++) {
        drawAirport(airports.at(i), v);
        v = false;
    }
    cout << "+-----+--------------------------------------------------------+---------------------------------+\n";
}

/**
 * Desenha uma companhia aérea e identifica se é a 1ª companhia a ser escrito para desenhar o cabeçalho da tabela (parâmetro header).
 * Complexidade Temporal O(n).
 * @param a
 * @param header
 */
void GestaoA::drawAirline(const Airline& a, bool header) const {
    if (header) {
        cout << "\n+-----+------------------------------------------+--------------------------------------+\n"
                "| COD |                  NAME                    |                COUNTRY               |\n"
                "+-----+------------------------------------------+--------------------------------------+\n";
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

/**
 * Desenha todas as companhias aéreas e chama a função drawAirline para desenhar uma de cada vez.
 * Complexidade Temporal O(n^2).
 * @param airlinesaux
 */
void GestaoA::drawAirlines(const vector<Airline>& airlinesaux) const {
    bool v = true;
    for (const Airline& s: airlinesaux) {
        drawAirline(s, v);
        v = false;
    }
    cout << "+-----+------------------------------------------+--------------------------------------+\n";
}

/**
 * Desenha um voo, representado pelo nome do aeroporto de destino (parâmetro name) e nome da companhia aérea (parâmetro airline), desenhando o cabeçalho para o 1º desenho (parâmetro header)
 * Complexidade Temporal O(n)
 * @param name
 * @param airline
 * @param header
 */
void GestaoA::drawFlight(const string& name, const string& airline, bool header) {
    if (header) {
        cout << "\n+--------------------------------------------------------+------------------------------------------+\n"
                "|                   AIRPORT DESTINATION                  |                  AIRLINE                 |\n"
                "+--------------------------------------------------------+------------------------------------------+\n";
    }
    cout << "|";
    pair<int, int> pad = auxCenterDraw(getMaxAirportNameLength() - (int)name.length(), (int)name.length()%2 == 1);
    for (int f = 0; f < pad.first; f++) {
        cout << " ";
        ++f;
    }
    cout << name;
    for (int e = 0; e < pad.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|";
    pad = auxCenterDraw(getMaxAirlineNameLength() - (int)airline.length(), (int)airline.length()%2 == 1);
    for (int f = 0; f < pad.first; f++) {
        cout << " ";
        ++f;
    }
    cout << airline;
    for (int e = 0; e < pad.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|\n";
}

/**
 * Vai buscar os voos de um aeroporto (parâmetro code) e chama a função drawFlight para desenhar um a um.
 * Complexidade Temporal O(n^2).
 * @param code
 */
void GestaoA::drawFlights(const string& code) {
    bool v = true;
    list<pair<int, string>> airportFlights = flightNetwork_.getAirportFlights(code);
    for (const auto &flight: airportFlights) {
        string cd = flightNetwork_.getAirportName(flight.first);
        string airlinename;
        for (auto airline: airlines) {
            if (airline.getCode() == flight.second) {
                airlinename = airline.getName();
            }
        }
        drawFlight(cd, airlinename, v);
        v = false;
    }
    cout << "+--------------------------------------------------------+------------------------------------------+\n";
}

/**
 * Conta as companhias aéreas que têm voos num aeroporto (parâmetro code) e desenha no terminal.
 * Complexidade Temporal O(n).
 * @param code
 */
void GestaoA::drawNumberOfAirlines(const string &code) {
    set<string> temp;
    list<pair<int, string>> aux = flightNetwork_.getAirportFlights(code);
    int size;
    string helpme;
    for(auto i: aux){
        temp.insert(i.second);
    }
    size = (int)temp.size();
    if(size < 10){
        helpme = "0" + to_string(size);
    }
    else{helpme = to_string(size);}

    cout << "\n+---------+----------+\n"
            "| AIRPORT | AIRLINES |\n"
            "+---------+----------+\n";

    cout << "|   " << code << "   |";
    pair<int, int> pad = auxCenterDraw(9 - helpme.length(), helpme.length()%2 == 1);
    for (int f = 0; f < pad.first; f++) {
        cout << " ";
        ++f;
    }
    cout << helpme;
    for (int e = 0; e < pad.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|\n";
    cout << "+---------+----------+\n";
}

/**
 * Conta os destinos/aeroportos a que se pode chegar a partir de um aeroporto (parâmetro code) e desenha no terminal.
 * Complexidade Temporal O(n).
 * @param code
 */
void GestaoA::drawNumberOfTargets(const string &code) {
    set<string> temp;
    list<pair<int, string>> aux = flightNetwork_.getAirportFlights(code);
    int size;
    string helpme;
    for(auto i: aux){
        temp.insert(flightNetwork_.getAirportCode(i.first));
    }

    size = (int)temp.size();
    if(size < 10){
        helpme = "00" + to_string(size);
    }
    else if(size >= 10 && size < 100){
        helpme = "0" + to_string(size);
    }
    else{helpme = to_string(size);}

    cout << "\n+---------+-------------+\n"
            "| AIRPORT | DESTINATION |\n"
            "+---------+-------------+\n";
    cout << "|   " << code << "   |";
    pair<int, int> pad = auxCenterDraw(12 - helpme.length(), helpme.length()%2 == 1);
    for (int f = 0; f < pad.first; f++) {
        cout << " ";
        ++f;
    }
    cout << helpme;
    for (int e = 0; e < pad.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|\n";
    cout << "+---------+-------------+\n";
}

/**
 * Conta os países a que se pode chegar a partir de um aeroporto (parâmetro code) e desenha no terminal.
 * Complexidade Temporal O(n).
 * @param code
 */
void GestaoA::drawNumberOfCountries(const string &code) {
    set<string> temp;
    list<pair<int, string>> aux = flightNetwork_.getAirportFlights(code);
    int size;
    string helpme;
    for(auto i: aux){
        temp.insert(flightNetwork_.getAirportCountry(i.first));
    }

    size = (int)temp.size();
    if(size < 10){
        helpme = "0" + to_string(size);
    }
    else{helpme = to_string(size);}

    cout << "\n+---------+-----------+\n"
            "| AIRPORT | COUNTRIES |\n"
            "+---------+-----------+\n";
    cout << "|   " << code << "   |";
    pair<int, int> pad = auxCenterDraw(10 - helpme.length(), helpme.length()%2 == 0);
    for (int f = 0; f < pad.first; f++) {
        cout << " ";
        ++f;
    }
    cout << helpme;
    for (int e = 0; e < pad.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|\n";
    cout << "+---------+-----------+\n";
}

/**
 * Busca todos os aeroportos diferentes acessíveis a partir do inicial e dentro de y voos (usa BFS).
 * Complexidade Temporal O(n^2).
 * @param code
 * @param y
 * @return um set de strings com o código dos aeroportos que são acessíveis a partir do inicial
 */
set<int> GestaoA::Yairports(string code, int y) { //TODO
    queue<int> search;
    set<int> aux;
    set<int> airportsReached;
    search.push(flightNetwork_.getAirportInfo(code));

    for(auto &help: flightNetwork_.airports){
        help.visited = false;
        help.dist = -1;
    }
    flightNetwork_.airports[flightNetwork_.getAirportInfo(code)].dist = 0;
    flightNetwork_.airports[flightNetwork_.getAirportInfo(code)].visited = true;
    bool flag = false;


    while(!search.empty()){
        int currkey = search.front();
        for(auto flight: flightNetwork_.airports[currkey].flights){
            if(!flightNetwork_.airports[flight.dest].visited){
                flightNetwork_.airports[flight.dest].visited = true;
                search.push(flight.dest);
                aux.insert(flight.dest);
                flightNetwork_.airports[flight.dest].dist = flightNetwork_.airports[currkey].dist + 1;
                if(flightNetwork_.airports[flight.dest].dist > y){flag = true;}
            }
        }
        search.pop();
        if (flag) {break;}
    }


    for(auto k: aux){
        if(k == flightNetwork_.getAirportInfo(code) || flightNetwork_.airports[k].dist > y){continue;}
        else{airportsReached.insert(k);}
    }
    return airportsReached;
}

/**
 * Busca todas as cidades diferentes acessíveis a partir de um aeroporto inicial e dentro de y voos (Chama a função Yairports, logo usa BFS).
 * Complexidade Temporal O(n^2).
 * @param code
 * @param y
 * @return um set da classe CityCountry de forma a verificar se cidades com o mesmo nome podem ser de países diferentes
 */
set<CityCountry> GestaoA::Ycities(string code, int y) { //TODO
    set<int> airportsReached = Yairports(code, y);
    set<CityCountry> citiesReached;

    for(auto i: airportsReached){
        CityCountry cc(flightNetwork_.airports[i].city, flightNetwork_.airports[i].country);
        citiesReached.insert(cc);
    }

    return citiesReached;
}

/**
 * Busca todos os países diferentes acessíveis a partir de um aeroporto inicial e dentro de y voos (Chama a função Yairports, logo usa BFS).
 * Complexidade Temporal O(n^2).
 * @param code
 * @param y
 * @return um set de strings com os países acessíveis
 */
set<string> GestaoA::Ycountries(string code, int y) { //TODO
    set<int> airportsReached = Yairports(code, y);
    set<string> countriesReached;

    for(auto i: airportsReached){
        countriesReached.insert(flightNetwork_.airports[i].country);
    }

    return countriesReached;
}

/**
 * Desenha uma tabela com o código do aeroporto inicial e o número de destinos acessíveis a partir desse.
 * Complexidade Temporal O(n^2) (chama Yairports).
 * @param code
 * @param y
 */
void GestaoA::drawYairports(string code, int y) {
    set<int> airportsReached = Yairports(code, y);

    int size = airportsReached.size();
    string helpme;

    cout << "\n+---------+-------------+\n"
            "| AIRPORT | DESTINATION |\n"
            "+---------+-------------+\n";
    cout << "|   " << code << "   |";

    if(size < 10){
        helpme = "000" + to_string(size);
    }
    else if(size >= 10 && size < 100){
        helpme = "00" + to_string(size);
    }
    else if(size >= 100 && size < 1000){
        helpme = "0" + to_string(size);
    }
    else{helpme = to_string(size);}

    pair<int, int> pad = auxCenterDraw(12 - helpme.length(), helpme.length()%2 == 0);
    for (int f = 0; f < pad.first; f++) {
        cout << " ";
        ++f;
    }
    cout << helpme;
    for (int e = 0; e < pad.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|\n";
    cout << "+---------+-------------+\n";
}

/**
 * Desenha uma tabela com o código do aeroporto inicial e o número de cidades acessíveis.
 * Complexidade Temporal O(n^2) (chama Ycities que por sua vez chama Yairports).
 * @param code
 * @param y
 */
void GestaoA::drawYcities(string code, int y) {
    set<CityCountry> citiesReached = Ycities(code, y);

    int size = citiesReached.size();
    string helpme;

    cout << "\n+---------+--------+\n"
            "| AIRPORT | CITIES |\n"
            "+---------+--------+\n";
    cout << "|   " << code << "   |";

    if(size < 10){
        helpme = "00" + to_string(size);
    }
    else if(size >= 10 && size < 100){
        helpme = "0" + to_string(size);
    }
    else{helpme = to_string(size);}

    pair<int, int> pad = auxCenterDraw(7 - helpme.length(), helpme.length()%2 == 1);
    for (int f = 0; f < pad.first; f++) {
        cout << " ";
        ++f;
    }
    cout << helpme;
    for (int e = 0; e < pad.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|\n";
    cout << "+---------+--------+\n";
}

/**
 * Desenha uma tabela com o código do aeroporto inicial e o número de países acessíveis.
 * Complexidade Temporal O(n^2) (chama Ycountries que por sua vez chama Yairports).
 * @param code
 * @param y
 */
void GestaoA::drawYcountries(string code, int y) {
    set<string> countriesReached = Ycountries(code, y);

    int size = countriesReached.size();
    string helpme;

    cout << "\n+---------+-----------+\n"
            "| AIRPORT | COUNTRIES |\n"
            "+---------+-----------+\n";
    cout << "|   " << code << "   |";

    if(size < 10){
        helpme = "00" + to_string(size);
    }
    else if(size >= 10 && size < 100){
        helpme = "0" + to_string(size);
    }
    else{helpme = to_string(size);}

    pair<int, int> pad = auxCenterDraw(10 - helpme.length(), helpme.length()%2 == 1);
    for (int f = 0; f < pad.first; f++) {
        cout << " ";
        ++f;
    }
    cout << helpme;
    for (int e = 0; e < pad.second; e++) {
        cout << " ";
        ++e;
    }
    cout << "|\n";
    cout << "+---------+-----------+\n";
}

/**
 * Pergunta ao utilizador se quer organizar a tabela de forma ascendente ou descendente.
 * A Complexidade Temporal desta função depende do tempo que o utilizador demora a dar o input.
 * @return True para input Ascendente (A) e false para input Descendente (D).
 */
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

void GestaoA::setMaxCityLength(int maxLength_) { maxCityLength = maxLength_; }

void GestaoA::setMaxCountryLength(int maxLength_) { maxCountryLength = maxLength_; }

void GestaoA::setMaxAirportNameLength(int maxLength_) { maxAirportNameLength = maxLength_; }

void GestaoA::setMaxAirlineNameLength(int maxLength_) { maxAirlineNameLength = maxLength_; }

void GestaoA::setMaxAirlineCountryLength(int maxLength_) { maxAirlineCountryLength = maxLength_; }

vector<Graph::Airport> GestaoA::getAirports() const { return flightNetwork_.getAirports(); }

GestaoA::tabHcities GestaoA::getCities() const { return cities; }

GestaoA::tabHairlines GestaoA::getAirlines() const { return airlines; }

Graph GestaoA::getFlightNetwork() const { return flightNetwork_; }

int GestaoA::getMaxCityLength() const { return maxCityLength; }

int GestaoA::getMaxCountryLength() const { return maxCountryLength; }

int GestaoA::getMaxAirportNameLength() const { return maxAirportNameLength; }

int GestaoA::getMaxAirlineNameLength() const { return maxAirlineNameLength; }

int GestaoA::getMaxAirlineCountryLength() const { return maxAirlineCountryLength; }
