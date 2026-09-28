# MovieScript - Analizador Léxico

## Descripción

MovieScript es un pequeño lenguaje diseñado para representar elementos básicos de una película, como escenas, personajes, diálogos, acciones, cámaras, música y ubicaciones.

El proyecto implementa un analizador léxico utilizando FLEX y una interfaz gráfica desarrollada con C++ y Qt.

## Tecnologías utilizadas

* FLEX
* C++
* Qt 6
* CMake
* Git
* GitHub

## ¿Qué hace el programa?

El programa recibe código escrito en el lenguaje MovieScript y realiza un análisis léxico.

El analizador identifica:

* Palabras reservadas
* Identificadores
* Números
* Cadenas de texto
* Comentarios
* Errores léxicos

Los resultados se muestran en una tabla dentro de la interfaz gráfica.

## Palabras reservadas

El lenguaje utiliza las siguientes palabras reservadas:

* MOVIE
* SCENE
* CHARACTER
* SAY
* CAMERA
* MUSIC
* ACTION
* LOCATION
* CUT
* END

## Tokens

| Expresión              | Token         |
| ---------------------- | ------------- |
| MOVIE                  | MOVIE         |
| SCENE                  | SCENE         |
| CHARACTER              | CHARACTER     |
| SAY                    | SAY           |
| CAMERA                 | CAMERA        |
| MUSIC                  | MUSIC         |
| ACTION                 | ACTION        |
| LOCATION               | LOCATION      |
| CUT                    | CUT           |
| END                    | END           |
| [0-9]+                 | NUMERO        |
| "..."                  | CADENA        |
| [a-zA-Z_][a-zA-Z0-9_]* | IDENTIFICADOR |
| //...                  | COMENTARIO    |
| Otro carácter          | ERROR_LEXICO  |

## Ejemplo de MovieScript

MOVIE "El Viaje"

SCENE 10
CHARACTER HERO
CHARACTER VILLAIN

LOCATION CASTLE

SAY "Tenemos que luchar."

ACTION RUN
ACTION JUMP

CAMERA CLOSEUP
MUSIC DRAMATIC

CUT
END

## Análisis léxico

FLEX recibe las reglas definidas en `lexer.l` y genera el analizador léxico.

El analizador lee la entrada y reconoce los diferentes lexemas según sus expresiones regulares.

Por ejemplo:

`[0-9]+` reconoce números.

`"[^"\n]*"` reconoce cadenas.

`[a-zA-Z_][a-zA-Z0-9_]*` reconoce identificadores.

Los caracteres que no coinciden con ninguna regla son identificados como errores léxicos.

## Autómata

El analizador utiliza un autómata finito generado internamente por FLEX a partir de las expresiones regulares.

El proyecto incluye una representación conceptual del autómata dentro de la interfaz gráfica.

## Interfaz gráfica

La aplicación cuenta con dos secciones principales:

### Analizador

Permite escribir código MovieScript, analizarlo y visualizar los tokens encontrados.

### Autómata

Muestra una representación conceptual del autómata utilizado durante el análisis léxico.

## Estructura del proyecto

* `main.cpp` - Interfaz gráfica y funcionamiento principal.
* `lexer.l` - Reglas del analizador léxico FLEX.
* `lexer.h` - Definición de tokens y funciones.
* `lexer.cpp` - Analizador generado por FLEX.
* `CMakeLists.txt` - Configuración de compilación.
* `build/` - Archivos generados durante la compilación.

## Ejecución

Desde MSYS2 UCRT64:

```bash
cd ~/MovieScript/build
cmake ..
cmake --build .
./MovieScript.exe
```

## Autor

Proyecto académico de análisis léxico.
