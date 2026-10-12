
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QGroupBox>
#include <QTabWidget>
#include <QMessageBox>
#include <QStringList>
#include <QTableWidgetItem>
#include <QAbstractItemView>

#include "lexer.h"
#include "parser.h"
#include "semantic.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget ventana;
    ventana.setWindowTitle(
        "MovieScript - Analizador Lexico, Sintactico y Semantico"
    );
    ventana.resize(1150, 800);

    QVBoxLayout *layoutPrincipal =
        new QVBoxLayout(&ventana);

    QLabel *titulo =
        new QLabel(
            "MOVIESCRIPT - ANALIZADOR LEXICO, SINTACTICO Y SEMANTICO"
        );

    titulo->setStyleSheet(
        "font-size: 24px;"
        "font-weight: bold;"
        "padding: 10px;"
    );

    QLabel *descripcion =
        new QLabel(
            "Analizador lexico con FLEX, analizador sintactico "
            "descendente recursivo y analizador semantico en C++."
        );

    QTabWidget *pestanas =
        new QTabWidget();

    // =====================================================
    // PESTANA 1: ANALIZADOR
    // =====================================================

    QWidget *paginaAnalizador =
        new QWidget();

    QVBoxLayout *layoutAnalizador =
        new QVBoxLayout(paginaAnalizador);

    QLabel *codigoLabel =
        new QLabel("Codigo MovieScript:");

    QTextEdit *editor =
        new QTextEdit();

    editor->setPlaceholderText(
        "Escribe aqui tu programa MovieScript..."
    );

    editor->setStyleSheet(
        "font-family: Consolas, monospace;"
        "font-size: 14px;"
    );

    editor->setPlainText(
        "MOVIE \"El Viaje\"\n"
        "\n"
        "SCENE 10\n"
        "CHARACTER HERO\n"
        "CHARACTER VILLAIN\n"
        "\n"
        "LOCATION CASTLE\n"
        "\n"
        "SAY \"Tenemos que luchar.\"\n"
        "\n"
        "ACTION RUN\n"
        "ACTION JUMP\n"
        "\n"
        "CAMERA CLOSEUP\n"
        "MUSIC DRAMATIC\n"
        "\n"
        "CUT\n"
        "END"
    );

    QPushButton *analizar =
        new QPushButton("ANALIZAR");

    QPushButton *limpiar =
        new QPushButton("LIMPIAR");

    QPushButton *ejemplo =
        new QPushButton("CARGAR EJEMPLO");

    QHBoxLayout *botones =
        new QHBoxLayout();

    botones->addWidget(analizar);
    botones->addWidget(limpiar);
    botones->addWidget(ejemplo);

    QTableWidget *tabla =
        new QTableWidget();

    tabla->setColumnCount(3);

    QStringList encabezados;
    encabezados << "Lexema"
                << "Token"
                << "Linea";

    tabla->setHorizontalHeaderLabels(encabezados);

    tabla->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch
    );

    tabla->setAlternatingRowColors(true);

    tabla->setEditTriggers(
        QAbstractItemView::NoEditTriggers
    );

    QGroupBox *informacion =
        new QGroupBox("Resultados del analisis");

    QHBoxLayout *infoLayout =
        new QHBoxLayout(informacion);

    QLabel *totalTokens =
        new QLabel("Tokens: 0");

    QLabel *totalErrores =
        new QLabel("Errores lexicos: 0");

    QLabel *estado =
        new QLabel("Lexico: Sin analizar");

    QLabel *estadoSintactico =
        new QLabel("Sintaxis: Sin analizar");

    QLabel *estadoSemantico =
        new QLabel("Semantica: Sin analizar");

    infoLayout->addWidget(totalTokens);
    infoLayout->addWidget(totalErrores);
    infoLayout->addWidget(estado);
    infoLayout->addWidget(estadoSintactico);
    infoLayout->addWidget(estadoSemantico);

    layoutAnalizador->addWidget(codigoLabel);
    layoutAnalizador->addWidget(editor);
    layoutAnalizador->addLayout(botones);
    layoutAnalizador->addWidget(tabla);
    layoutAnalizador->addWidget(informacion);

    // =====================================================
    // PESTANA 2: AUTOMATA LEXICO
    // =====================================================

    QWidget *paginaAutomata =
        new QWidget();

    QVBoxLayout *layoutAutomata =
        new QVBoxLayout(paginaAutomata);

    QLabel *tituloAutomata =
        new QLabel(
            "AUTOMATA FINITO DEL ANALIZADOR LEXICO"
        );

    tituloAutomata->setStyleSheet(
        "font-size: 22px;"
        "font-weight: bold;"
        "padding: 10px;"
    );

    QLabel *explicacion =
        new QLabel(
            "FLEX utiliza expresiones regulares para "
            "generar internamente el automata que reconoce "
            "los lexemas del lenguaje MovieScript."
        );

    explicacion->setWordWrap(true);

    QTextEdit *automata =
        new QTextEdit();

    automata->setReadOnly(true);

    automata->setStyleSheet(
        "font-family: Consolas, monospace;"
        "font-size: 14px;"
    );

    automata->setPlainText(
        "                  MOVIESCRIPT\n"
        "             AUTOMATA LEXICO\n"
        "\n"
        "INICIO\n"
        "  |\n"
        "  | letra o guion bajo\n"
        "  v\n"
        "IDENTIFICADOR\n"
        "  letras, digitos y guion bajo\n"
        "\n"
        "INICIO\n"
        "  |\n"
        "  | digito\n"
        "  v\n"
        "NUMERO\n"
        "  acepta uno o mas digitos\n"
        "\n"
        "INICIO\n"
        "  |\n"
        "  | comilla doble\n"
        "  v\n"
        "CADENA\n"
        "  acepta texto entre comillas\n"
        "\n"
        "ESPACIOS Y TABULACIONES -> IGNORAR\n"
        "SALTO DE LINEA             -> CONTAR LINEA\n"
        "//                         -> COMENTARIO\n"
        "CARACTER NO VALIDO         -> ERROR_LEXICO\n"
        "\n"
        "PALABRAS RESERVADAS:\n"
        "MOVIE SCENE CHARACTER SAY CAMERA\n"
        "MUSIC ACTION LOCATION CUT END\n"
        "\n"
        "REGLAS LEXICAS:\n"
        "[0-9]+                   -> NUMERO\n"
        "\"...\"                    -> CADENA\n"
        "[a-zA-Z_][a-zA-Z0-9_]*  -> IDENTIFICADOR\n"
        "//...                    -> COMENTARIO\n"
    );

    QLabel *notaAutomata =
        new QLabel(
            "Nota: representacion conceptual. FLEX genera "
            "el automata real a partir de las reglas de lexer.l."
        );

    notaAutomata->setWordWrap(true);

    layoutAutomata->addWidget(tituloAutomata);
    layoutAutomata->addWidget(explicacion);
    layoutAutomata->addWidget(automata);
    layoutAutomata->addWidget(notaAutomata);

    // =====================================================
    // PESTANA 3: GRAMATICA
    // =====================================================

    QWidget *paginaGramatica =
        new QWidget();

    QVBoxLayout *layoutGramatica =
        new QVBoxLayout(paginaGramatica);

    QLabel *tituloGramatica =
        new QLabel(
            "GRAMATICA DEL LENGUAJE MOVIESCRIPT"
        );

    tituloGramatica->setStyleSheet(
        "font-size: 22px;"
        "font-weight: bold;"
        "padding: 10px;"
    );

    QLabel *explicacionGramatica =
        new QLabel(
            "Estas reglas definen la estructura que debe "
            "tener un programa para que el analizador "
            "sintactico lo acepte."
        );

    explicacionGramatica->setWordWrap(true);

    QTextEdit *gramatica =
        new QTextEdit();

    gramatica->setReadOnly(true);

    gramatica->setStyleSheet(
        "font-family: Consolas, monospace;"
        "font-size: 14px;"
    );

    gramatica->setPlainText(
        "             GRAMATICA MOVIESCRIPT\n"
        "================================================\n"
        "\n"
        "PROGRAMA\n"
        "  -> MOVIE CADENA ESCENAS END\n"
        "\n"
        "ESCENAS\n"
        "  -> ESCENA ESCENAS\n"
        "  -> ESCENA\n"
        "\n"
        "ESCENA\n"
        "  -> SCENE NUMERO ELEMENTOS\n"
        "\n"
        "ELEMENTOS\n"
        "  -> CHARACTER IDENTIFICADOR\n"
        "  -> LOCATION IDENTIFICADOR\n"
        "  -> SAY CADENA\n"
        "  -> ACTION IDENTIFICADOR\n"
        "  -> CAMERA IDENTIFICADOR\n"
        "  -> MUSIC IDENTIFICADOR\n"
        "  -> CUT\n"
        "\n"
        "================================================\n"
        "\n"
        "EJEMPLO DE PROGRAMA:\n"
        "\n"
        "MOVIE \"El Viaje\"\n"
        "\n"
        "SCENE 10\n"
        "CHARACTER HERO\n"
        "LOCATION CASTLE\n"
        "SAY \"Tenemos que luchar.\"\n"
        "ACTION RUN\n"
        "CAMERA CLOSEUP\n"
        "MUSIC DRAMATIC\n"
        "CUT\n"
        "\n"
        "END\n"
        "\n"
        "================================================\n"
        "\n"
        "REGLAS DEL LENGUAJE:\n"
        "\n"
        "1. El programa comienza con MOVIE y una CADENA.\n"
        "2. Cada escena comienza con SCENE y un NUMERO.\n"
        "3. Cada escena debe contener elementos validos.\n"
        "4. CHARACTER necesita un IDENTIFICADOR.\n"
        "5. LOCATION necesita un IDENTIFICADOR.\n"
        "6. SAY necesita una CADENA entre comillas.\n"
        "7. ACTION necesita un IDENTIFICADOR.\n"
        "8. CAMERA necesita un IDENTIFICADOR.\n"
        "9. MUSIC necesita un IDENTIFICADOR.\n"
        "\n"
        "El parser verifica estas estructuras mediante\n"
        "analisis sintactico descendente recursivo.\n"
    );

    layoutGramatica->addWidget(tituloGramatica);
    layoutGramatica->addWidget(explicacionGramatica);
    layoutGramatica->addWidget(gramatica);

    // =====================================================
    // PESTANA 4: ANALISIS SEMANTICO
    // =====================================================

    QWidget *paginaSemantica =
        new QWidget();

    QVBoxLayout *layoutSemantica =
        new QVBoxLayout(paginaSemantica);

    QLabel *tituloSemantica =
        new QLabel(
            "ANALIZADOR SEMANTICO DE MOVIESCRIPT"
        );

    tituloSemantica->setStyleSheet(
        "font-size: 22px;"
        "font-weight: bold;"
        "padding: 10px;"
    );

    QLabel *explicacionSemantica =
        new QLabel(
            "El analizador semantico comprueba reglas que "
            "van mas alla de la estructura del programa. "
            "Verifica que los numeros de escena no se repitan, "
            "que no se declare dos veces el mismo personaje "
            "en una escena y que cada escena tenga como maximo "
            "una ubicacion."
        );

    explicacionSemantica->setWordWrap(true);

    QTextEdit *reglasSemanticas =
        new QTextEdit();

    reglasSemanticas->setReadOnly(true);

    reglasSemanticas->setStyleSheet(
        "font-family: Consolas, monospace;"
        "font-size: 14px;"
    );

    reglasSemanticas->setPlainText(
        "REGLAS SEMANTICAS DE MOVIESCRIPT\n"
        "========================================\n"
        "\n"
        "1. Los numeros de escena deben ser unicos.\n"
        "\n"
        "2. No se puede declarar dos veces el mismo\n"
        "   personaje dentro de una escena.\n"
        "\n"
        "3. Una escena puede tener como maximo una\n"
        "   ubicacion LOCATION.\n"
        "\n"
        "4. No se permiten instrucciones despues de CUT\n"
        "   dentro de una escena.\n"
        "\n"
        "El analizador sintactico debe aceptar el programa\n"


        "antes de ejecutar el analisis semantico.\n"
    );

    layoutSemantica->addWidget(tituloSemantica);
    layoutSemantica->addWidget(explicacionSemantica);
    layoutSemantica->addWidget(reglasSemanticas);

    // =====================================================
    // AGREGAR LAS CUATRO PESTANAS
    // =====================================================


pestanas->addTab(
        paginaAnalizador,
        "ANALIZADOR"

    );


    pestanas->addTab(
        paginaAutomata,
        "AUTOMATA"

    );


    pestanas->addTab(
        paginaGramatica,
        "GRAMATICA"
    );


    pestanas->addTab(
        paginaSemantica,
        "SEMANTICA"

    );

    // =====================================================
    // BOTON ANALIZAR
    // =====================================================

    QObject::connect(
        analizar,
        &QPushButton::clicked,
        [&]()
        {
            analizarTexto(
                editor->toPlainText().toStdString()
            );

            ResultadoSintactico resultado =
                analizarSintaxis(tokens);

            ResultadoSemantico resultadoSemantico;

            if (resultado.correcto)
            {
                resultadoSemantico =
                    analizarSemantica(tokens);
            }
            else
            {
                resultadoSemantico = {
                    false,
                    "Analisis semantico omitido: "
                    "primero debe corregirse el error "
                    "lexico o sintactico.",
                    resultado.linea
                };
            }

            tabla->setRowCount(0);

            int erroresLexicos = 0;

            for (const Token &token : tokens)
            {
                int fila = tabla->rowCount();

                tabla->insertRow(fila);

                tabla->setItem(
                    fila,
                    0,
                    new QTableWidgetItem(
                        QString::fromStdString(token.lexema)
                    )
                );

                tabla->setItem(
                    fila,
                    1,
                    new QTableWidgetItem(
                        QString::fromStdString(token.tipo)
                    )
                );

                tabla->setItem(
                    fila,
                    2,
                    new QTableWidgetItem(
                        QString::number(token.linea)
                    )
                );

                if (token.tipo == "ERROR_LEXICO")
                {
                    erroresLexicos++;
                }
            }

            totalTokens->setText(
                "Tokens: " +
                QString::number(tokens.size())
            );

            totalErrores->setText(
                "Errores lexicos: " +
                QString::number(erroresLexicos)
            );

            // Resultado lexico

            if (erroresLexicos == 0)
            {
                estado->setText(
                    "Lexico: CORRECTO"
                );
            }
            else
            {
                estado->setText(
                    "Lexico: CON ERRORES"
                );
            }

            // Resultado sintactico

            if (resultado.correcto)
            {
                estadoSintactico->setText(
                    "Sintaxis: CORRECTA"
                );
            }
            else
            {
                QString textoError =
                    "Sintaxis: ERROR";

                if (resultado.linea > 0)
                {
                    textoError +=
                        " - Linea " +
                        QString::number(resultado.linea);
                }

                estadoSintactico->setText(
                    textoError
                );
            }

            // Resultado semantico

            if (resultadoSemantico.correcto)
            {
                estadoSemantico->setText(
                    "Semantica: CORRECTA"
                );
            }
            else
            {
                QString textoError =
                    "Semantica: ERROR";

                if (resultadoSemantico.linea > 0)
                {
                    textoError +=
                        " - Linea " +
                        QString::number(
                            resultadoSemantico.linea
                        );
                }

                estadoSemantico->setText(
                    textoError
                );
            }

            // Mostrar los resultados de ambos analizadores

            QString resumen =
                "Analisis sintactico:\n" +
                QString::fromStdString(
                    resultado.mensaje
                );

            resumen +=
                "\n\nAnalisis semantico:\n";

            resumen +=
                QString::fromStdString(
                    resultadoSemantico.mensaje
                );

            QMessageBox::information(
                &ventana,
                "Resultados del analisis",
                resumen
            );
        }
    );

    // =====================================================
    // BOTON LIMPIAR
    // =====================================================

    QObject::connect(
        limpiar,
        &QPushButton::clicked,
        [&]()
        {
            editor->clear();
            tabla->setRowCount(0);

            totalTokens->setText("Tokens: 0");
            totalErrores->setText("Errores lexicos: 0");

            estado->setText(
                "Lexico: Sin analizar"
            );

            estadoSintactico->setText(
                "Sintaxis: Sin analizar"
            );

            estadoSemantico->setText(
                "Semantica: Sin analizar"
            );
        }
    );

    // =====================================================
    // BOTON CARGAR EJEMPLO
    // =====================================================

    QObject::connect(
        ejemplo,
        &QPushButton::clicked,
        [&]()
        {
            editor->setPlainText(
                "MOVIE \"El Viaje\"\n"
                "\n"
                "SCENE 10\n"
                "CHARACTER HERO\n"
                "CHARACTER VILLAIN\n"
                "\n"
                "LOCATION CASTLE\n"
                "\n"
                "SAY \"Tenemos que luchar.\"\n"
                "\n"
                "ACTION RUN\n"
                "ACTION JUMP\n"
                "\n"
                "CAMERA CLOSEUP\n"
                "MUSIC DRAMATIC\n"
                "\n"
                "CUT\n"
                "END"
            );
        }
    );

    // =====================================================
    // MOSTRAR VENTANA
    // =====================================================

    layoutPrincipal->addWidget(titulo);
    layoutPrincipal->addWidget(descripcion);
    layoutPrincipal->addWidget(pestanas);

    ventana.show();

    return app.exec();
}
