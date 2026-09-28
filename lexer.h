#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

struct Token {
    std::string lexema;
    std::string tipo;
    int linea;
};

extern std::vector<Token> tokens;
extern int linea_actual;

void analizarTexto(const std::string& texto);

#endif
