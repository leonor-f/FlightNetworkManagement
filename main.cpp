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

    Menu::abriuAplicacao();

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
        else if (op == "1") {
            while (true) {
                GestaoA::drawListagemMenu();
                string op0;
                cin >> op0;
                if (op0.length() != 1) {
                    Menu::teclaErro();
                    continue;
                } else if (op0 == "1") {
                    bool s = GestaoA::ordenar();
                    vector<CityCountry> aux;
                    GestaoA::tabHcities temp = a.getCities();
                    for (const auto &i: temp) {
                        aux.push_back(i);
                    }

                    sort(aux.begin(), aux.end());
                    if (!s) { reverse(aux.begin(), aux.end()); }
                    a.drawCities(aux);
                    Menu::voltar();
                } else if (op0 == "2") {
                    bool s = GestaoA::ordenar();
                    vector<Graph::Airport> temp = a.getAirports();
                    vector<string> airports;
                    for (const auto &i: temp) {
                        airports.push_back(i.code);
                    }
                    sort(airports.begin(), airports.end());
                    if (!s) reverse(airports.begin(), airports.end());
                    a.drawAirports(airports);
                    Menu::voltar();
                } else if (op0 == "3") {
                    bool s = GestaoA::ordenar();
                    vector<Airline> aux;
                    GestaoA::tabHairlines temp = a.getAirlines();
                    for (const auto &i: temp) {
                        aux.push_back(i);
                    }

                    sort(aux.begin(), aux.end());
                    if (!s) { reverse(aux.begin(), aux.end()); }
                    a.drawAirlines(aux);
                    Menu::voltar();
                } else if (op0 == "4") {
                    string code;
                    while (true) {
                        cout << "\nInsira o codigo do aeroporto de inicio: ";
                        cin >> code;
                        if (code.length() != 3) {
                            Menu::teclaErro();
                            continue;
                        }
                        transform(code.begin(), code.end(), code.begin(), ::toupper);
                        if (a.getFlightNetwork().getAirportFlights(code).empty()) Menu::aeroportoNaoEncontrado();
                        else break;
                    }
                    a.drawFlights(code);
                    Menu::voltar();
                } else if (op0 == "5") {
                    string city, country;
                    vector<string> airports;
                    bool ignoreCin = true;
                    while (true) {
                        cout << "\nInsira o nome do pais: ";
                        if (ignoreCin) cin.ignore();
                        ignoreCin = false;
                        getline(cin, country);
                        if (country.length() < 1) {
                            Menu::teclaErro();
                            continue;
                        }
                        cout << "\nInsira o nome da cidade: ";
                        getline(cin, city);
                        if (city.length() < 1) {
                            Menu::teclaErro();
                            continue;
                        }
                        transform(country.begin(), country.end(), country.begin(), ::toupper);
                        transform(city.begin(), city.end(), city.begin(), ::toupper);
                        CityCountry cityCountry = {city, country};
                        airports = a.getFlightNetwork().getAirportsByCityCountry(cityCountry);
                        if (airports.empty()) Menu::airportNotFound();
                        else break;
                    }
                    a.drawAirportsByCityCountry(airports);
                    Menu::voltar();
                } else if (op0 == "6") {
                    string code;
                    while (true) {
                        cout << "\nInsira o codigo do aeroporto: ";
                        cin >> code;
                        if (code.length() != 3) {
                            Menu::teclaErro();
                            continue;
                        }
                        transform(code.begin(), code.end(), code.begin(), ::toupper);
                        if (a.getFlightNetwork().getAirportFlights(code).empty()) Menu::aeroportoNaoEncontrado();
                        else break;
                    }
                    a.drawAirlinesByAirport(code);
                    Menu::voltar();
                }
                else if (op0 == "V" || op0 == "v") break;
            }
        }
        else if (op == "2") {
            while (true) {
                GestaoA::drawNumberMenu();
                string op2;
                cin >> op2;
                if (op2.length() != 1) {
                    Menu::teclaErro();
                    continue;
                }
                else if (op2 == "1") {
                    string code;
                    while (true) {
                        cout << "\nInsira o codigo do aeroporto de inicio: ";
                        cin >> code;
                        if (code.length() != 3) {
                            Menu::teclaErro();
                            continue;
                        }
                        transform(code.begin(), code.end(), code.begin(), ::toupper);
                        if ( a.getFlightNetwork().getAirportFlights(code).empty()) Menu::aeroportoNaoEncontrado();
                        else break;
                    }
                    a.drawNumberOfAirlines(code);
                    Menu::voltar();
                }
                else if (op2 == "2") {
                    string code;
                    while (true) {
                        cout << "\nInsira o codigo do aeroporto de inicio: ";
                        cin >> code;
                        if (code.length() != 3) {
                            Menu::teclaErro();
                            continue;
                        }
                        transform(code.begin(), code.end(), code.begin(), ::toupper);
                        if ( a.getFlightNetwork().getAirportFlights(code).empty()) Menu::aeroportoNaoEncontrado();
                        else break;
                    }
                    a.drawNumberOfTargets(code);
                    Menu::voltar();
                }
                else if (op2 == "3") {
                    string code;
                    while (true) {
                        cout << "\nInsira o codigo do aeroporto de inicio: ";
                        cin >> code;
                        if (code.length() != 3) {
                            Menu::teclaErro();
                            continue;
                        }
                        transform(code.begin(), code.end(), code.begin(), ::toupper);
                        if ( a.getFlightNetwork().getAirportFlights(code).empty()) Menu::aeroportoNaoEncontrado();
                        else break;
                    }
                    a.drawNumberOfCountries(code);
                    Menu::voltar();
                }
                else if (op2 == "V" || op2 == "v")  {
                    break;
                }
            }
        }
        else if (op == "3") {
            while (true) {
                GestaoA::drawYMenu();
                string op3;
                cin >> op3;
                if (op3.length() != 1) {
                    Menu::teclaErro();
                    continue;
                }
                else if (op3 == "1") {
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
                        if (temp.find_first_not_of("1234567890") != string::npos) {
                            Menu::teclaErro();
                            continue;
                        }
                        transform(code.begin(), code.end(), code.begin(), ::toupper);
                        if (a.getFlightNetwork().getAirportFlights(code).empty()) Menu::aeroportoNaoEncontrado();
                        else break;
                    }
                    y = stoi(temp);
                    a.drawYAirports(code, y);
                    Menu::voltar();
                }
                else if (op3 == "2") {
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
                        if (temp.find_first_not_of("1234567890") != string::npos) {
                            Menu::teclaErro();
                            continue;
                        }
                        transform(code.begin(), code.end(), code.begin(), ::toupper);
                        if (a.getFlightNetwork().getAirportFlights(code).empty()) Menu::aeroportoNaoEncontrado();
                        else break;
                    }
                    y = stoi(temp);
                    a.drawYCities(code, y);
                    Menu::voltar();
                }
                else if (op3 == "3") {
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
                        if (temp.find_first_not_of("1234567890") != string::npos) {
                            Menu::teclaErro();
                            continue;
                        }
                        transform(code.begin(), code.end(), code.begin(), ::toupper);
                        if (a.getFlightNetwork().getAirportFlights(code).empty()) Menu::aeroportoNaoEncontrado();
                        else break;
                    }
                    y = stoi(temp);
                    a.drawYCountries(code, y);
                    Menu::voltar();
                }
                else if (op3 == "V" || op3 == "v") {
                    break;
                }
            }
        }
        else if (op == "4") {
            while (true) {
                GestaoA::drawDiameterMenu();
                string op4;
                cin >> op4;
                if (op4.length() != 1) {
                    Menu::teclaErro();
                    continue;
                }
                else if (op4 == "1") {
                    a.drawDiameter();
                    Menu::voltar();
                }
                else if (op4 == "2") {
                    string country;
                    bool ignoreCin = true;
                    while (true) {
                        cout << "\nInsira o pais de inicio: ";
                        if (ignoreCin) cin.ignore();
                        ignoreCin = false;
                        getline(cin, country);
                        transform(country.begin(), country.end(), country.begin(), ::toupper);
                        if (!a.findCountry(country)) Menu::countryNotFound();
                        else break;
                    }
                    a.drawDiameterCountry(country);
                    Menu::voltar();
                }
                else if (op4 == "V" || op4 == "v") {
                    break;
                }
            }
        }
        else if (op == "5") {
            vector<string> airlineCodes;
            for (const auto& airline : a.getAirlines()) {
                airlineCodes.push_back(airline.getCode());
            }
            while (true) {
                GestaoA::drawFlyMenu();
                string op4;
                cin >> op4;
                if (op4.length() != 1) {
                    Menu::teclaErro();
                    continue;
                }
                else if (op4 == "1") {
                    string src;
                    string dest;
                    while (true) {
                        cout << "\nInsira o codigo do aeroporto de partida: ";
                        cin >> src;
                        if (src.length() != 3) {
                            Menu::teclaErro();
                            continue;
                        }
                        cout << "\nInsira o codigo do aeroporto de chegada: ";
                        cin >> dest;
                        if (dest.length() != 3) {
                            Menu::teclaErro();
                            continue;
                        }
                        transform(src.begin(), src.end(), src.begin(), ::toupper);
                        transform(dest.begin(), dest.end(), dest.begin(), ::toupper);
                        if (a.getFlightNetwork().getAirportFlights(src).empty() || a.getFlightNetwork().getAirportFlights(dest).empty()) Menu::aeroportoNaoExiste();
                        else if (src == dest) Menu::aeroportosIguais();
                        else break;
                    }
                    a.getFlightNetwork().auxShortestPath(src, dest, {}, {}, 1, airlineCodes);
                    Menu::voltar();
                }
                else if (op4 == "2") {
                    string city1, city2, country1, country2;
                    vector<string> partida;
                    vector<string> chegada;
                    bool ignoreCin = true;
                    while (true) {
                        cout << "\nInsira o nome do pais de partida: ";
                        if (ignoreCin) cin.ignore();
                        ignoreCin = false;
                        getline(cin, country1);
                        if (country1.length() < 1) {
                            Menu::teclaErro();
                            continue;
                        }
                        cout << "\nInsira o nome da cidade de partida: ";
                        getline(cin, city1);
                        if (city1.length() < 1) {
                            Menu::teclaErro();
                            continue;
                        }
                        cout << "\nInsira o nome do pais de chegada: ";
                        getline(cin, country2);
                        if (country2.length() < 1) {
                            Menu::teclaErro();
                            continue;
                        }
                        cout << "\nInsira o nome da cidade de chegada: ";
                        getline(cin, city2);
                        if (city2.length() < 1) {
                            Menu::teclaErro();
                            continue;
                        }
                        transform(country1.begin(), country1.end(), country1.begin(), ::toupper);
                        transform(city1.begin(), city1.end(), city1.begin(), ::toupper);
                        transform(country2.begin(), country2.end(), country2.begin(), ::toupper);
                        transform(city2.begin(), city2.end(), city2.begin(), ::toupper);
                        // verificar se existe algum aeroporto nos paises e cidades inseridas
                        CityCountry cityCountry1 = {city1, country1};
                        CityCountry cityCountry2 = {city2, country2};
                        partida = a.getFlightNetwork().getAirportsByCityCountry(cityCountry1);
                        chegada = a.getFlightNetwork().getAirportsByCityCountry(cityCountry2);
                        if (partida.empty() || chegada.empty()) Menu::aeroportoNaoExiste();
                        else break;
                    }
                    /* Verificação do tipo
                     * Tipo 1 ≥ 1 aeroporto de partida: 1 aeroporto de chegada
                     * Tipo 2 ≥ 1 aeroporto de partida: +1 aeroportos de chegada
                     * Tipo 3 ≥ +1 aeroportos de partida: 1 aeroporto de chegada
                     * Tipo 4 ≥ +1 aeroportos de partida: +1 aeroportos de chegada
                    */
                    if (partida.size() == 1 && chegada.size() == 1) {
                        a.getFlightNetwork().auxShortestPath(partida.at(0), chegada.at(0), {}, {}, 1, airlineCodes);
                    }
                    else if (partida.size() == 1 && chegada.size() > 1) {
                        a.getFlightNetwork().auxShortestPath(partida.at(0), "", {}, chegada, 2, airlineCodes);
                    }
                    else if (partida.size() > 1 && chegada.size() == 1) {
                        a.getFlightNetwork().auxShortestPath("", chegada.at(0), partida, {}, 3, airlineCodes);
                    }
                    else if (partida.size() > 1 && chegada.size() > 1) {
                        a.getFlightNetwork().auxShortestPath("", "", partida, chegada, 4, airlineCodes);
                    }
                    Menu::voltar();
                }
                else if (op4 == "3") {
                    string lat1, lat2, long1, long2;
                    while (true) {
                        cout << "\nInsira a latitude do local de partida: ";
                        cin >> lat1;
                        if (lat1.find_first_not_of("0123456789.-") != string::npos) {
                            Menu::teclaErro();
                            continue;
                        }
                        cout << "\nInsira a longitude do local de partida: ";
                        cin >> long1;
                        if (long1.find_first_not_of("0123456789.-") != string::npos) {
                            Menu::teclaErro();
                            continue;
                        }
                        cout << "\nInsira a latitude do local de chegada: ";
                        cin >> lat2;
                        if (lat2.find_first_not_of("0123456789.-") != string::npos) {
                            Menu::teclaErro();
                            continue;
                        }
                        cout << "\nInsira a longitude do local de chegada: ";
                        cin >> long2;
                        if (long2.find_first_not_of("0123456789.-") != string::npos) {
                            Menu::teclaErro();
                            continue;
                        }
                        break;
                    }
                    a.getFlightNetwork().auxLocal(stold(lat1), stold(long1), stold(lat2), stold(long2), airlineCodes);
                    Menu::voltar();
                }
                else if (op4 == "V" || op4 == "v") break;
            }
        }
        else if (op == "6"){
            while (true) {
                GestaoA::drawAPMenu();
                string op6;
                cin >> op6;
                if (op6.length() != 1) {
                    Menu::teclaErro();
                    continue;
                }
                else if (op6 == "1") {
                    a.drawArticulationPoints();
                    Menu::voltar();
                }
                else if (op6 == "2") {
                    a.drawListArticulationPoints();
                    Menu::voltar();
                }
                else if (op6 == "V" || op6 == "v") {
                    break;
                }
            }
        }
        else if (op == "q" || op == "Q") {
            Menu::fechouAplicacao();
            break;
        }
        else Menu::teclaErro();
    }
    return 0;
}
