
#include "semantic.h"

#include <set>
#include <string>

ResultadoSemantico analizarSemantica(
    const std::vector<Token>& tokens)
{
    std::set<std::string> numerosEscena;
    std::set<std::string> personajesEscena;

    bool dentroEscena = false;
    bool ubicacionDefinida = false;
    bool corteVisto = false;

    for (size_t i = 0; i < tokens.size(); i++)
    {
        const Token& token = tokens[i];

        // Verificar que cada escena tenga un numero unico.
        if (token.tipo == "SCENE")
        {
            if (i + 1 >= tokens.size())
            {
                return {
                    false,
                    "Falta el numero de la escena.",
                    token.linea
                };
            }

            std::string numero = tokens[i + 1].lexema;

            if (!numerosEscena.insert(numero).second)
            {
                return {
                    false,
                    "Error semantico: numero de escena repetido: "
                    + numero,
                    tokens[i + 1].linea
                };
            }

            dentroEscena = true;
            personajesEscena.clear();
            ubicacionDefinida = false;
            corteVisto = false;

            continue;
        }

        if (token.tipo == "END")
            break;

        if (!dentroEscena)
            continue;

        // No permitir instrucciones despues de CUT.
        if (corteVisto)
        {
            return {
                false,
                "Error semantico: hay instrucciones despues de CUT.",
                token.linea
            };
        }

        // Verificar personajes duplicados en la escena.
        if (token.tipo == "CHARACTER")
        {
            if (i + 1 < tokens.size())
            {
                std::string personaje = tokens[i + 1].lexema;

                if (!personajesEscena.insert(personaje).second)
                {
                    return {
                        false,
                        "Error semantico: personaje duplicado: "
                        + personaje,
                        tokens[i + 1].linea
                    };
                }
            }
        }

        // Una escena solo puede tener una ubicacion.
        if (token.tipo == "LOCATION")
        {
            if (ubicacionDefinida)
            {
                return {
                    false,
                    "Error semantico: hay mas de una ubicacion "
                    "en la misma escena.",
                    token.linea
                };
            }

            ubicacionDefinida = true;
        }

        if (token.tipo == "CUT")
            corteVisto = true;
    }

    return {
        true,
        "Analisis semantico correcto. No se encontraron errores.",
        0
    };
}
