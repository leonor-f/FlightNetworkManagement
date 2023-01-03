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
            vector<Graph::Airport> temp = a.getAirports();
            vector<string> airports;
            for(auto i: temp){
                airports.push_back(i.code);
            }
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
        else if(op == "5"){
            while(true){
                a.drawNumberMenu();
                string op2;
                cin >> op2;
                if (op2.length() != 1) {
                    Menu::teclaErro();
                    continue;
                }
                else if(op2 == "1"){
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
                    a.drawNumberOfAirlines(code);
                    Menu::voltar();
                }
                else if(op2 == "2"){
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
                    a.drawNumberOfTargets(code);
                    Menu::voltar();
                }
                else if(op2 == "3"){
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
                    a.drawNumberOfCountries(code);
                    Menu::voltar();
                }
                else if(op2 == "V" || op2 == "v"){
                    break;
                }
            }
        }
        //TODO
        else if(op == "6"){
            while(true){
                a.drawYMenu();
                string op3;
                cin >> op3;
                if (op3.length() != 1) {
                    Menu::teclaErro();
                    continue;
                }
                else if(op3 == "1"){
                    string code;
                    string temp;
                    int y;
                    while (true) {
                        cout << "\nInsira o codigo do aeroporto de inicio: ";
                        cin >> code;
                        if (code.length() != 3) {
                            Menu::teclaErro();
                            continue;
                        }
                        cout << "\nQuantos voos? (Insira um numero): ";
                        cin >> temp;
                        transform(code.begin(), code.end(), code.begin(), ::toupper);
                        if (a.getFlightNetwork().getAirportFlights(code).empty()) Menu::aeroportoNaoExiste();
                        else break;
                    }
                    y = stoi(temp);
                    a.drawYairports(code, y);
                    Menu::voltar();
                }
                else if(op3 == "2"){
                    string code;
                    string temp;
                    int y;
                    while (true) {
                        cout << "\nInsira o codigo do aeroporto de inicio: ";
                        cin >> code;
                        if (code.length() != 3) {
                            Menu::teclaErro();
                            continue;
                        }
                        cout << "\nQuantos voos? (Insira um numero): ";
                        cin >> temp;
                        transform(code.begin(), code.end(), code.begin(), ::toupper);
                        if (a.getFlightNetwork().getAirportFlights(code).empty()) Menu::aeroportoNaoExiste();
                        else break;
                    }
                    y = stoi(temp);
                    a.drawYcities(code, y);
                    Menu::voltar();
                }
                else if(op3 == "3"){
                    string code;
                    string temp;
                    int y;
                    while (true) {
                        cout << "\nInsira o codigo do aeroporto de inicio: ";
                        cin >> code;
                        if (code.length() != 3) {
                            Menu::teclaErro();
                            continue;
                        }
                        cout << "\nQuantos voos? (Insira um numero): ";
                        cin >> temp;
                        transform(code.begin(), code.end(), code.begin(), ::toupper);
                        if (a.getFlightNetwork().getAirportFlights(code).empty()) Menu::aeroportoNaoExiste();
                        else break;
                    }
                    y = stoi(temp);
                    a.drawYcountries(code, y);
                    Menu::voltar();
                }
                else if(op3 == "V" || op3 == "v"){
                    break;
                }
            }
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