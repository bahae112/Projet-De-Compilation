#include <iostream>
#include <string>

bool ReconnaitreIdentificateur(const std::string& chaine) {
    int n = chaine.size();
    if (n == 0) // Une chaîne vide n'est pas un identificateur valide
        return false;

    // Vérifier le premier caractère : il doit être une lettre ou un underscore
    if (!((chaine[0] >= 'a' && chaine[0] <= 'z') ||
          (chaine[0] >= 'A' && chaine[0] <= 'Z') ||
          (chaine[0] == '_'))) {
        return false;
    }

    // Vérifier les caractères restants : ils doivent être des lettres, des chiffres ou des underscores
    for (int i = 1; i < n; i++) {
        if (!((chaine[i] >= 'a' && chaine[i] <= 'z') ||
              (chaine[i] >= 'A' && chaine[i] <= 'Z') ||
              (chaine[i] >= '0' && chaine[i] <= '9') ||
              (chaine[i] == '_'))) {
            return false;
        }
    }

    return true;
}

int main() {
    std::string id1 = "variable1";
    std::string id2 = "_id";
    std::string id3 = "123var";

    std::cout << "ReconnaîtreIdentificateur(\"" << id1 << "\"): " << (ReconnaitreIdentificateur(id1) ? "True" : "False") << std::endl;
    std::cout << "ReconnaîtreIdentificateur(\"" << id2 << "\"): " << (ReconnaitreIdentificateur(id2) ? "True" : "False") << std::endl;
    std::cout << "ReconnaîtreIdentificateur(\"" << id3 << "\"): " << (ReconnaitreIdentificateur(id3) ? "True" : "False") << std::endl;

    return 0;
}
