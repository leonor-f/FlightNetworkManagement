#include "../header/Menu.h"
#include <iostream>

using namespace std;

/**
 * Caso o input do utilizador não esteja entre os aceitados, apresenta uma mensagem de erro.
 */
void Menu::teclaErro() {
    cout << "\n+--------------+\n"
            "|Input Invalido|\n"
            "+--------------+\n";
}

/**
 * Depois do utilizador escolher uma tarefa, aparece a opção de voltar ao menu.
 */
void Menu::voltar() {
    string op;
    cout << "\nPressione [V] para voltar ao Menu:";
    cin >> op;
    while (op != "V" && op != "v") {
        teclaErro();
        cout << "\nPressione [V] para voltar ao Menu:";
        cin >> op;
    }
}

void Menu::aeroportoNaoExiste() {
    cout << "\n+-------------------------------+\n"
            "|O aeroporto indicado nao existe|\n"
            "+-------------------------------+\n";
}
