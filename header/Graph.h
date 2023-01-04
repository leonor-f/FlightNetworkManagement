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

    struct Flight {
        int dest;       // node de destino
        string airline; // airline
        float distance;   // distância entre os dois aeroportos, NÃO NECESSÁRIO IMPLEMENTAR JÁ
    };

    struct Airport {
        list<Flight> flights;  // lista de flights/edges deste aeroporto
        string code;           // código
        string name;           // nome
        string city;           // cidade
        string country;        // país
        long double latitude;  // latitude
        long double longitude; // longitude
        bool visited;          // para futuras pesquisas
        int dist;              // dist to source node
    };

    Graph();          // default constructor
    explicit Graph(int nodes); // Constructor: n.º nodes

    float calcDistance(const string& code1, const string& code2); //Calcular Distância usando a fórmula do enunciado do projeto

    // getters

    vector<Airport> getAirports() const; // return de vetor de códigos que representam cada aeroporto
    string getAirportCode(const string& code) const;
    string getAirportName(const string& code) const;
    string getAirportCity(const string& code) const;
    string getAirportCountry(const string& code) const;
    long double getAirportLatitude(const string& code) const;
    long double getAirportLongitude(const string& code) const;
    string getAirportCode(const int& dest) const;
    string getAirportName(const int& dest) const;
    string getAirportCity(const int& dest) const;
    string getAirportCountry(const int& dest) const;
    long double getAirportLatitude(const int& dest) const;
    long double getAirportLongitude(const int& dest) const;
    bool getAirportVisited(int airport) const;
    list<pair<int, string>> getAirportFlights(const string& code) const;
    const map<string, int>& getAirportsInfo() const;
    int getAirportInfo(const string& code) const;

    // setters

    void setNode(const string& code, const string& name, const string& city, const string& country, long double latitude, long double longitude);
    void addFlight(int src, int dest, const string& airline); // adiciona voo de src para dest

    int n;              // tamanho do grafo, n.º de aeroportos
    vector<Airport> airports; // lista de aeroportos/nodes
    map<string, int> airportsInfo; // relaciona cada aeroporto com um inteiro
};

#endif
