
#include "parser.h"

class Parser
{
private:

    const std::vector<Token>& tokens;
    size_t posicion;

public:

    Parser(const std::vector<Token>& tokens)
        : tokens(tokens), posicion(0)
    {
    }

    const Token* actual()
    {
        if (posicion < tokens.size())
            return &tokens[posicion];

        return nullptr;
    }

    bool aceptar(const std::string& tipo)
    {
        if (actual() != nullptr &&
            actual()->tipo == tipo)
        {
            posicion++;
            return true;
        }

        return false;
    }

    ResultadoSintactico error(
        const std::string& mensaje)
    {
        ResultadoSintactico resultado;

        resultado.correcto = false;
        resultado.mensaje = mensaje;

        if (actual() != nullptr)
            resultado.linea = actual()->linea;
        else
            resultado.linea = -1;

        return resultado;
    }

    ResultadoSintactico programa()
    {
        if (!aceptar("MOVIE"))
            return error(
                "Se esperaba MOVIE al inicio del programa."
            );

        if (!aceptar("CADENA"))
            return error(
                "Se esperaba una CADENA despues de MOVIE."
            );

        while (actual() != nullptr &&
               actual()->tipo == "SCENE")
        {
            ResultadoSintactico resultado =
                escena();

            if (!resultado.correcto)
                return resultado;
        }

        if (!aceptar("END"))
            return error(
                "Se esperaba END al final del programa."
            );

        if (actual() != nullptr)
            return error(
                "Existen tokens despues de END."
            );

        ResultadoSintactico resultado;

        resultado.correcto = true;
        resultado.mensaje =
            "Analisis sintactico correcto.";

        resultado.linea = 0;

        return resultado;
    }

    ResultadoSintactico escena()
    {
        if (!aceptar("SCENE"))
            return error(
                "Se esperaba SCENE."
            );

        if (!aceptar("NUMERO"))
            return error(
                "Se esperaba un NUMERO despues de SCENE."
            );

        bool tieneElemento = false;

        while (actual() != nullptr &&
               actual()->tipo != "SCENE" &&
               actual()->tipo != "END")
        {
            tieneElemento = true;

            ResultadoSintactico resultado =
                elemento();

            if (!resultado.correcto)
                return resultado;
        }

        if (!tieneElemento)
            return error(
                "La escena debe contener al menos un elemento."
            );

        return {
            true,
            "",
            0
        };
    }

    ResultadoSintactico elemento()
    {
        if (aceptar("CHARACTER"))
        {
            if (!aceptar("IDENTIFICADOR"))
                return error(
                    "Se esperaba un IDENTIFICADOR despues de CHARACTER."
                );

            return {true, "", 0};
        }

        if (aceptar("LOCATION"))
        {
            if (!aceptar("IDENTIFICADOR"))
                return error(
                    "Se esperaba un IDENTIFICADOR despues de LOCATION."
                );

            return {true, "", 0};
        }

        if (aceptar("SAY"))
        {
            if (!aceptar("CADENA"))
                return error(
                    "Se esperaba una CADENA despues de SAY."
                );

            return {true, "", 0};
        }

        if (aceptar("ACTION"))
        {
            if (!aceptar("IDENTIFICADOR"))
                return error(
                    "Se esperaba un IDENTIFICADOR despues de ACTION."
                );

            return {true, "", 0};
        }

        if (aceptar("CAMERA"))
        {
            if (!aceptar("IDENTIFICADOR"))
                return error(
                    "Se esperaba un IDENTIFICADOR despues de CAMERA."
                );

            return {true, "", 0};
        }

        if (aceptar("MUSIC"))
        {
            if (!aceptar("IDENTIFICADOR"))
                return error(
                    "Se esperaba un IDENTIFICADOR despues de MUSIC."
                );

            return {true, "", 0};
        }

        if (aceptar("CUT"))
        {
            return {true, "", 0};
        }

        return error(
            "Elemento no reconocido dentro de la escena."
        );
    }
};

ResultadoSintactico analizarSintaxis(
    const std::vector<Token>& tokens)
{
    for (const Token& token : tokens)
    {
        if (token.tipo == "ERROR_LEXICO")
        {
            return {
                false,
                "No se puede realizar el analisis sintactico porque existen errores lexicos.",
                token.linea
            };
        }
    }

    if (tokens.empty())
    {
        return {
            false,
            "El programa esta vacio.",
            0
        };
    }

    Parser parser(tokens);

    return parser.programa();
}

