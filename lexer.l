%{
#include "lexer.h"

std::vector<Token> tokens;
int linea_actual = 1;
%}

%option noyywrap

%%

"MOVIE"        { tokens.push_back({yytext, "MOVIE", linea_actual}); }
"SCENE"        { tokens.push_back({yytext, "SCENE", linea_actual}); }
"CHARACTER"    { tokens.push_back({yytext, "CHARACTER", linea_actual}); }
"SAY"          { tokens.push_back({yytext, "SAY", linea_actual}); }
"CAMERA"       { tokens.push_back({yytext, "CAMERA", linea_actual}); }
"MUSIC"        { tokens.push_back({yytext, "MUSIC", linea_actual}); }
"ACTION"       { tokens.push_back({yytext, "ACTION", linea_actual}); }
"LOCATION"     { tokens.push_back({yytext, "LOCATION", linea_actual}); }
"CUT"          { tokens.push_back({yytext, "CUT", linea_actual}); }
"END"          { tokens.push_back({yytext, "END", linea_actual}); }

[0-9]+         { tokens.push_back({yytext, "NUMERO", linea_actual}); }

\"[^\"\n]*\"   { tokens.push_back({yytext, "CADENA", linea_actual}); }

[a-zA-Z_][a-zA-Z0-9_]* {
    tokens.push_back({yytext, "IDENTIFICADOR", linea_actual});
}

[ \t\r]+       { }

\n             { linea_actual++; }

"//".*         { }

.              { tokens.push_back({yytext, "ERROR_LEXICO", linea_actual}); }

%%

void analizarTexto(const std::string& texto)
{
    tokens.clear();
    linea_actual = 1;

    YY_BUFFER_STATE buffer = yy_scan_string(texto.c_str());

    yylex();

    yy_delete_buffer(buffer);
}
