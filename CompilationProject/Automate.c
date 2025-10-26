#include <iostream>
#include <string>

// Fonction pour vérifier si un mot est accepté
bool isAccepted(const std::string& word) {
    int state = 0; // État initial q0

    for (char c : word) {
        if (state == 0) { // q0
            if (c == 'a') {
                state = 1; // Transition vers q1
            }
        } else if (state == 1) { // q1
            if (c == 'b') {
                state = 2; // Transition vers q2
            } else {
                state = 0; // Retour à q0
            }
        } else if (state == 2) { // q2
            if (c == 'a') {
                state = 1; // Transition vers q1
            }
            // Si c == 'b', rester en q2
        }
    }

    return state == 2; // Le mot est accepté si on termine en q2
}

int main() {
    std::string word;
    std::cout << "Entrez un mot composé de 'a' et 'b' : ";
    std::cin >> word;

    if (isAccepted(word)) {
        std::cout << "Le mot est accepté." << std::endl;
    } else {
        std::cout << "Le mot n'est pas accepté." << std::endl;
    }

    return 0;
}