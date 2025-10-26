#include <iostream>
#include <string>

bool Appartient(const std::string& u) {
    int n = u.size();
    if (n < 4) // La chaîne doit contenir au moins "abab"
        return false;

    int i = 0;

    // Vérifier les 'a' au début
    while (i < n && u[i] == 'a') {
        i++;
    }

    // Il doit y avoir au moins un 'a'
    if (i == 0)
        return false;

    // Vérifier 'b'
    if (i < n && u[i] == 'b') {
        i++;
    } else {
        return false;
    }

    // Vérifier 'a'
    if (i < n && u[i] == 'a') {
        i++;
    } else {
        return false;
    }

    // Vérifier les 'b' restants
    while (i < n && u[i] == 'b') {
        i++;
    }

    // Il doit y avoir au moins un 'b' après 'a'
    if (i == n - 1 && u[n - 1] == 'b') {
        return true;
    }

    return (i == n); 
}

int main() {
    std::string mot1 = "aaababb";
    std::string mot2 = "aabbb";

    std::cout << "Appartient(\"" << mot1 << "\"): " << (Appartient(mot1) ? "True" : "False") << std::endl;
    std::cout << "Appartient(\"" << mot2 << "\"): " << (Appartient(mot2) ? "True" : "False") << std::endl;

    return 0;
}