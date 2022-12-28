#include <iostream>
#include <algorithm>
#include "header/GestaoA.h"
#include "header/Airline.h"
#include "header/Airport.h"
#include "header/Flight.h"
#include "header/menu.h"

int main() {
    GestaoA a;
    a.readAirlines();
    a.readAirports();

    // ciclo do programa
    while (true) {
        a.drawMenu(); // desenha o menu
        string op;
        cin >> op;
        if (op.length() != 1) {
            Menu::teclaErro();
            continue;
        }
        // dependendo do input do utilizador, vai executar tarefas diferentes
        if (op == "1") {
            bool s = a.ordenar();
            vector<CityCountry> aux;
            GestaoA::tabHcities temp = a.getCities();
            for(auto i: temp){
                aux.push_back(i);
            }

            sort(aux.begin(), aux.end());
            if(!s){reverse(aux.begin(), aux.end());}
            a.drawCities(aux);
            Menu::voltar();
        }
        else if (op == "2") {
            bool s = a.ordenar();
            vector<Airport> aux;
            GestaoA::tabHairports temp = a.getAirports();
            for(auto i: temp){
                aux.push_back(i);
            }

            sort(aux.begin(), aux.end());
            if(!s){reverse(aux.begin(), aux.end());}
            a.drawAirports(aux);
            Menu::voltar();
        }
        else if (op == "3") {
            bool s = a.ordenar();
            vector<Airline> aux;
            GestaoA::tabHairlines temp = a.getAirlines();
            for(auto i: temp){
                aux.push_back(i);
            }

            sort(aux.begin(), aux.end());
            if(!s){reverse(aux.begin(), aux.end());}
            a.drawAirlines(aux);
            Menu::voltar();
        }
        else if (op == "4") {

            Menu::voltar();
        }
        else if (op == "5") {

            Menu::voltar();
        }
        else if (op == "6") {

            Menu::voltar();
        }
        else if (op == "7") {

            Menu::voltar();
        }
        else if (op == "8") {

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