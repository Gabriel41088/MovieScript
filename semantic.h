

#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "lexer.h"
#include <string>
#include <vector>

struct ResultadoSemantico
{
    bool correcto;
    std::string mensaje;
    int linea;
};

ResultadoSemantico analizarSemantica(
    const std::vector<Token>& tokens
);

#endif
