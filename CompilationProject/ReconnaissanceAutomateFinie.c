#include <iostream>
#include <string>

// Vérifie si une chaîne est un identificateur
bool isIdentifier(const std::string& word) {
    if (word.empty() || (!isalpha(word[0]) && word[0] != '_')) {
        return false;
    }
    for (char c : word) {
        if (!isalnum(c) && c != '_') {
            return false;
        }
    }
    return true;
}

// Vérifie si une chaîne est un entier
bool isInteger(const std::string& word) {
    if (word.empty()) {
        return false;
    }
    for (char c : word) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Vérifie si une chaîne est un nombre réel
bool isReal(const std::string& word) {
    bool foundDot = false; // Pour détecter un seul point
    if (word.empty()) {
        return false;
    }
    for (char c : word) {
        if (c == '.') {
            if (foundDot) {
                return false; // Plus d'un point
            }
            foundDot = true;
        } else if (!isdigit(c)) {
            return false;
        }
    }
    return foundDot; // Doit contenir un point pour être un réel
}

// Vérifie si une chaîne est un commentaire
bool isComment(const std::string& word) {
    if (word.size() >= 2 && word[0] == '/' && word[1] == '/') {
        return true; // Commentaire sur une ligne
    }
    if (word.size() >= 4 && word.substr(0, 2) == "/*" && word.substr(word.size() - 2) == "*/") {
        return true; // Commentaire multi-lignes
    }
    return false;
}

int main() {
    std::string test;

    std::cout << "Entrez une chaîne : ";
    std::getline(std::cin, test);

    if (isIdentifier(test)) {
        std::cout << "C'est un identificateur valide." << std::endl;
    } else if (isInteger(test)) {
        std::cout << "C'est un entier." << std::endl;
    } else if (isReal(test)) {
        std::cout << "C'est un nombre réel." << std::endl;
    } else if (isComment(test)) {
        std::cout << "C'est un commentaire." << std::endl;
    } else {
        std::cout << "Non reconnu par l'automate." << std::endl;
    }

    return 0;
}