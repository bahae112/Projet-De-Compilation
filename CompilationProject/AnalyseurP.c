#include <iostream>
#include <string>

void Analyseur(const std::string& P) {
    std::string mot = "";
    bool motEnCours = false;

    std::cout << "[";

    for (size_t i = 0; i < P.size(); ++i) {
        char c = P[i];

        if (c == ' ' || c == ';') {
            if (motEnCours) {
                std::cout << "\"" << mot << "\"";
                mot = ""; // Réinitialise le mot
                motEnCours = false;

                // Vérifie si ce n'est pas le dernier mot à afficher
                if (i < P.size() - 1 && P[i + 1] != ' ' && P[i + 1] != ';') {
                    std::cout << ", ";
                }
            }
        } else {
            mot += c;
            motEnCours = true;
        }
    }

    // Vérifie s'il reste un mot à afficher à la fin
    if (!mot.empty()) {
        std::cout << "\"" << mot << "\"";
    }

    std::cout << "]" << std::endl;
}

int main() {
    std::string P = "analyseur lexical ; et syntaxique";

    Analyseur(P);

    return 0;
}