#include <iostream>
#include <algorithm>
#include "header/GestaoA.h"
#include "header/Airline.h"
#include "header/Menu.h"

int main() {
    GestaoA a;
    a.readAirlines();
    a.readAirports();
    a.readFlights();

    // ciclo do programa
    while (true) {
        GestaoA::drawMenu(); // desenha o menu
        string op;
        cin >> op;
        if (op.length() != 1) {
            Menu::teclaErro();
            continue;
        }
        // dependendo do input do utilizador, vai executar tarefas diferentes
        if (op == "1") {
            bool s = GestaoA::ordenar();
            vector<CityCountry> aux;
            GestaoA::tabHcities temp = a.getCities();
            for(const auto& i: temp){
                aux.push_back(i);
            }

            sort(aux.begin(), aux.end());
            if(!s){reverse(aux.begin(), aux.end());}
            a.drawCities(aux);
            Menu::voltar();
        }
        else if (op == "2") {
            bool s = GestaoA::ordenar();
            vector<string> airports = a.getAirports();

            sort(airports.begin(), airports.end());
            if(!s) reverse(airports.begin(), airports.end());
            a.drawAirports(airports);
            Menu::voltar();
        }
        else if (op == "3") {
            bool s = GestaoA::ordenar();
            vector<Airline> aux;
            GestaoA::tabHairlines temp = a.getAirlines();
            for(const auto& i: temp){
                aux.push_back(i);
            }

            sort(aux.begin(), aux.end());
            if(!s){reverse(aux.begin(), aux.end());}
            a.drawAirlines(aux);
            Menu::voltar();
        }
        else if (op == "4") {
            string code;
            while (true) {
                cout << "\nInsira o codigo do aeroporto de inicio: ";
                cin >> code;
                if (code.length() != 3) {
                    Menu::teclaErro();
                    continue;
                }
                transform(code.begin(), code.end(), code.begin(), ::toupper);
                if ( a.getFlightNetwork().getAirportFlights(code).empty()) Menu::aeroportoNaoExiste();
                else break;
            }
            a.drawFlights(code);
            Menu::voltar();
        }
        else if(op == "P" || op == "p"){
            Menu::voltar();
        }
        else if (op == "q" || op == "Q"){
            break;
        }
        else Menu::teclaErro();
    }
    return 0;
}