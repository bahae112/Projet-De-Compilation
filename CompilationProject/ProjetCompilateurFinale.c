#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <stack>
using namespace std;

// Définition des types de jetons
enum TokenType {
    BINARY_OP,
    BINARY_COMP,
    DOUBLE_AND,
    DOUBLE_OR,
    OPEN_ACCOLADE,
    CLOSE_ACCOLADE,
    OPEN_CROCHET,
    CLOSE_CROCHET,
    NEGATION,
    COMMA,
    AFFECT,
    POINT_VRG,
    KEY_WORD,
    CONST,
    ADRESS,
    IDENTIF,
    COMMENT,
    NUMBER,
    AUTRE
};

// Classe UniteLexical
class UniteLexical {
private:
    TokenType token_root;
    string value;

public:
    UniteLexical(TokenType token, const string &val) : token_root(token), value(val) {}

    TokenType getTokenRoot() const {
        return token_root;
    }

    string getValue() const {
        return value;
    }

    void display() const {
        cout << "Token: " << token_root << ", Value: " << value << endl;
    }
};

// Classe Lexer
class Lexer {
private:
    string m_src;
    size_t index;
    string buffer;
    vector<UniteLexical> tokens;

    const string liste_mots[8] = {"else", "then", "for", "while", "void", "int", "return", "if"};
    const string binOp[4] = {"+", "-", "*", "/"};
    const string binComp[6] = {">", "<", ">=", "<=", "==", "!="};

public:
    Lexer(const string &src) : m_src(src), index(0), buffer("") {}

    char pick() {
        return (index < m_src.size()) ? m_src[index] : '\0';
    }

    void consume() {
        if (index < m_src.size()) {
            index++;
        }
    }

    void clearBuffer() {
        buffer.clear();
    }

    bool isWhite(char c) {
        return (c == '\t' || c == '\n' || c == '\r');
    }

    bool chercher(const string liste[], size_t size, const string &buffer) {
        for (size_t i = 0; i < size; ++i) {
            if (buffer == liste[i]) {
                return true;
            }
        }
        return false;
    }

    void handleComment() {
        consume(); // Skip '/'
        if (pick() == '/') {
            consume();
            while (pick() != '\n' && pick() != '\0') {
                buffer += pick();
                consume();
            }
            tokens.emplace_back(TokenType::COMMENT, buffer);
            clearBuffer();
        }
    }

    vector<UniteLexical> tokenization() {
        while (index < m_src.size()) {
            char current = pick();

            while (isspace(current) || isWhite(current)) {
                consume();
                current = pick();
            }

            if (isdigit(current)) {
                clearBuffer();
                while (isdigit(current)) {
                    buffer += current;
                    consume();
                    current = pick();
                }
                tokens.emplace_back(TokenType::NUMBER, buffer);
            } else if (isalpha(current)) {
                clearBuffer();
                while (isalnum(current)) {
                    buffer += current;
                    consume();
                    current = pick();
                }
                if (chercher(liste_mots, 8, buffer)) {
                    tokens.emplace_back(TokenType::KEY_WORD, buffer);
                } else {
                    tokens.emplace_back(TokenType::IDENTIF, buffer);
                }
            } else if (current == '/') {
                handleComment();
            } else {
                switch (current) {
                    case '{':
                        tokens.emplace_back(TokenType::OPEN_ACCOLADE, "{");
                        break;
                    case '}':
                        tokens.emplace_back(TokenType::CLOSE_ACCOLADE, "}");
                        break;
                    case '[':
                        tokens.emplace_back(TokenType::OPEN_CROCHET, "[");
                        break;
                    case ']':
                        tokens.emplace_back(TokenType::CLOSE_CROCHET, "]");
                        break;
                    case ',':
                        tokens.emplace_back(TokenType::COMMA, ",");
                        break;
                    case ';':
                        tokens.emplace_back(TokenType::POINT_VRG, ";");
                        break;
                    case '=':
                        consume();
                        if (pick() == '=') {
                            tokens.emplace_back(TokenType::BINARY_COMP, "==");
                            consume();
                        } else {
                            tokens.emplace_back(TokenType::AFFECT, "=");
                        }
                        break;
                    case '&':
                        consume();
                        if (pick() == '&') {
                            tokens.emplace_back(TokenType::DOUBLE_AND, "&&");
                            consume();
                        }
                        break;
                    case '|':
                        consume();
                        if (pick() == '|') {
                            tokens.emplace_back(TokenType::DOUBLE_OR, "||");
                            consume();
                        }
                        break;
                    case '!':
                        consume();
                        if (pick() == '=') {
                            tokens.emplace_back(TokenType::BINARY_COMP, "!=");
                            consume();
                        } else {
                            tokens.emplace_back(TokenType::NEGATION, "!");
                        }
                        break;
                    default:
                        tokens.emplace_back(TokenType::AUTRE, string(1, current));
                        break;
                }
                consume();
            }
        }
        return tokens;
    }
};

// Classe Debugeur
class Debugeur {
private:
    vector<UniteLexical> tokens;

    bool checkParenthesesBalance() {
        stack<char> parentheses;
        for (const auto &token : tokens) {
            if (token.getValue() == "{" || token.getValue() == "[") {
                parentheses.push(token.getValue()[0]);
            } else if (token.getValue() == "}" || token.getValue() == "]") {
                if (parentheses.empty() || (parentheses.top() == '{' && token.getValue() != "}") ||
                    (parentheses.top() == '[' && token.getValue() != "]")) {
                    return false;
                }
                parentheses.pop();
            }
        }
        return parentheses.empty();
    }

    void verifierPointsVirgules() {
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (tokens[i].getTokenRoot() == TokenType::AFFECT ||
                tokens[i].getTokenRoot() == TokenType::IDENTIF ||
                tokens[i].getTokenRoot() == TokenType::NUMBER) {
                if (i + 1 < tokens.size() && tokens[i + 1].getTokenRoot() != TokenType::POINT_VRG) {
                    cout << "Erreur : Point-virgule manquant apres '" << tokens[i].getValue() << "'" << endl;
                }
            }
        }
    }

    void verifierTypes() {
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (tokens[i].getTokenRoot() == TokenType::AFFECT) {
                if (i > 0 && i + 1 < tokens.size()) {
                    const UniteLexical &gauche = tokens[i - 1];
                    const UniteLexical &droite = tokens[i + 1];

                    if (gauche.getTokenRoot() == TokenType::IDENTIF && droite.getTokenRoot() != TokenType::NUMBER) {
                        cout << "Erreur : Type incompatible entre '" << gauche.getValue()
                             << "' et '" << droite.getValue() << "'" << endl;
                    }
                }
            }
        }
    }

    void verifierParentheses() {
        int compteurParentheses = 0;
        for (const auto &token : tokens) {
            if (token.getValue() == "(") {
                compteurParentheses++;
            } else if (token.getValue() == ")") {
                compteurParentheses--;
            }

            if (compteurParentheses < 0) {
                cout << "Erreur : Parenthèse fermante sans correspondance." << endl;
                return;
            }
        }

        if (compteurParentheses > 0) {
            cout << "Erreur : Parenthèse ouvrante sans correspondance." << endl;
        }
    }

    void verifierMotsCles() {
        bool dansFonction = false;
        for (const auto &token : tokens) {
            if (token.getValue() == "int" || token.getValue() == "void") {
                dansFonction = true;
            } else if (token.getValue() == "return") {
                if (!dansFonction) {
                    cout << "Erreur : 'return' utilisé en dehors d'une fonction." << endl;
                }
            }
        }
    }

    void verifierCommentaires() {
        bool dansCommentaire = false;
        for (const auto &token : tokens) {
            if (token.getValue() == "/*") {
                dansCommentaire = true;
            } else if (dansCommentaire && token.getValue() == "*/") {
                dansCommentaire = false;
            }
        }

        if (dansCommentaire) {
            cout << "Erreur : commentaire non ferme ." << endl;
        }
    }

    void verifierOperateursInutilises() {
        for (size_t i = 0; i < tokens.size(); ++i) {
            if (tokens[i].getTokenRoot() == TokenType::BINARY_OP) {
                if (i == 0 || i == tokens.size() - 1 ||
                    (tokens[i - 1].getTokenRoot() == TokenType::BINARY_OP ||
                     tokens[i + 1].getTokenRoot() == TokenType::BINARY_OP)) {
                    cout << "Erreur : Opérateur '" << tokens[i].getValue() << "' mal utilisé." << endl;
                }
            }
        }
    }

public:
    Debugeur(const vector<UniteLexical> &tok) : tokens(tok) {}

    void analyser() {
        if (!checkParenthesesBalance()) {
            cout << "Erreur : desequilibre dans les accolades ou crochets." << endl;
        }
        verifierPointsVirgules();
        verifierTypes();
        verifierParentheses();
        verifierMotsCles();
        verifierCommentaires();
        verifierOperateursInutilises();
    }
};

int main() {
    // Demande de saisie du code source à l'utilisateur
    string code;
    cout << "Veuillez entrer le code source : " << endl;
    getline(cin, code);

    Lexer lexer(code);
    vector<UniteLexical> tokens = lexer.tokenization();

    cout << "\n=== Tokens ===" << endl;
    for (const auto &token : tokens) {
        token.display();
    }

    Debugeur debug(tokens);
    debug.analyser();

    return 0;
}