#include <iostream>
#include <string>

// Fonction pour vérifier si une chaîne est un entier valide
bool ReconnaitreEntier(const std::string& chaine) {
    if (chaine.empty()) // Une chaîne vide n'est pas un entier
        return false;

    int i = 0;

    // Vérifier le signe (+ ou -)
    if (chaine[0] == '+' || chaine[0] == '-') {
        i++;
    }

    // Vérifier que les caractères restants sont des chiffres
    for (; i < chaine.size(); i++) {
        if (!isdigit(chaine[i])) {
            return false;
        }
    }

    return true;
}

int main() {
    // Cas de test
    std::string tests[] = {"123", "-456", "12a3", "+789", "-", ""};
    for (const auto& test : tests) {
        std::cout << "ReconnaîtreEntier(\"" << test << "\"): "
                  << (ReconnaitreEntier(test) ? "True" : "False") << std::endl;
    }

    return 0;
}