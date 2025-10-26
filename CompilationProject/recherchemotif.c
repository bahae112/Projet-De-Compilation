#include <iostream>
#include <string>
#include <vector>

std::vector<int> Recherche_motif(const std::string& motif, const std::string& texte) {
    std::vector<int> positions;
    size_t pos = texte.find(motif, 0); // Cherche le motif à partir du début
    while (pos != std::string::npos) {
        positions.push_back(pos); // Ajoute la position trouvée
        pos = texte.find(motif, pos + 1); // Continue la recherche après la position actuelle
    }
    return positions;
}

int main() {
    std::string texte = "if x>2 : if x<5 : print(x) else: print(x-2)";
    std::string motif = "if";

    std::vector<int> positions = Recherche_motif(motif, texte);
    std::cout << "Positions du motif \"" << motif << "\": ";
    for (int pos : positions) {
        std::cout << pos << " ";
    }
    return 0;
}