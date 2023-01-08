#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_set>
#include "Airline.h"
#include "CityCountry.h"

using namespace std;

class Graph { // grafo do sistema
    public:
        struct infoFlight {
            string src;
            string dest;
            string airline;
        };

        struct Flight {
            int dest;       // node de destino
            string airline; // airline
        };

        struct Airport {
            list<Flight> flights;  // lista de flights/edges deste aeroporto (adjacências)
            string code;           // código
            string name;           // nome
            string city;           // cidade
            string country;        // país
            long double latitude;  // latitude
            long double longitude; // longitude
            bool visited;          // para futuras pesquisas
            int dist;              // dist to source node
        };

        Graph();                   // default constructor
        explicit Graph(int nodes); // Constructor: n.º nodes

        // getters

        vector<Airport> getAirports() const;
        string getAirportName(const string& code) const;
        string getAirportCountry(const string& code) const;
        string getAirportCode(const int& dest) const;
        string getAirportName(const int& dest) const;
        string getAirportCountry(const int& dest) const;
        list<pair<int, string>> getAirportFlights(const string& code) const;
        int getAirportInfo(const string& code) const;
        vector<string> getAirportsByCityCountry(const CityCountry &city);

        // setters

        void setNode(const string& code, const string& name, const string& city, const string& country, long double latitude, long double longitude);
        void addFlight(int src, int dest, const string& airline); // adiciona voo de src para dest

        static bool isAirlineValid(const string& airline, const vector<string>& airlines);
        void dfsAirlines(int v, int u, vector<infoFlight>& valuesPath, const vector<string>& airlines);
        void bfsAirlines(int v, const vector<string> &airlines);
        static bool auxAirlineExist(const string &code, const vector<string>& airlines);
        static vector<string> airlineHelper(const vector<string>& airlines);
        void auxLocal(long double lat1, long double long1, long double lat2, long double long2, const vector<string>& airlines);
        bool isWayPossible(int indexSrc, int indexDest, vector<infoFlight> &valuesPath, vector<infoFlight> &possiblePaths);
        pair<int, int> auxSPTH(const vector<string>& partida, const string& dest, const vector<string>& airlines);
        pair<int, int> auxSPTW(const string& src, const vector<string>& chegada, const vector<string>& airlines);
        void auxShortestPath(const string &src, const string &dest,const vector<string>& partida, const vector<string>& chegada, int type, const vector<string>& airlines);
        void shortestPath(const string &src, const string &dest, const vector<string>& airlineCodes);

        int n;                         // tamanho do grafo, n.º de aeroportos
        vector<Airport> airports;      // lista de aeroportos/nodes
        map<string, int> airportsInfo; // relaciona cada aeroporto com um inteiro
};

#endif
