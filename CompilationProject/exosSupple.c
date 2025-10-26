#include <string>

using namespace std;

// Fonction pour exécuter l'automate
int executeAutomate(const char automate[][3], const string& input) {
    char currentState = '0'; // État initial

    for (char symbol : input) {
        int columnIndex = -1;
        if (symbol == 'a') columnIndex = 1;
        else if (symbol == 'b') columnIndex = 2;

        if (columnIndex == -1) {
            cout << "Symbole invalide : " << symbol << endl;
            return -1;
        }
        currentState = automate[currentState - '0' + 1][columnIndex];
        
    }

    return currentState - '0';
}

bool isAccepted(int finalState) {
    return finalState == 2;
}

int main() {
    // Table de transition
    char automate[4][3] = {
        {'e', 'a', 'b'},
        {'0', '1', '0'},
        {'1', '1', '2'},
        {'2', '2', '2'}
    };
    string input;
    cout << "Entrez une chaîne composée des symboles 'a' et 'b' : ";
    cin >> input;

    int finalState = executeAutomate(automate, input);

    if (finalState == -1) {
        cout << "Erreur lors de l'exécution de l'automate. Chaîne invalide." << endl;
    } else {
        cout << "État final : " << finalState << endl;

        if (isAccepted(finalState)) {
            cout << "La chaine appartient au langage." << endl;
        } else {
            cout << "La chaine n'appartient pas au langage." << endl;
        }
    }

    return 0;
}