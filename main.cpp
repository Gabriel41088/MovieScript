
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

#include "lexer.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget ventana;
    ventana.setWindowTitle(
        "MovieScript - Analizador Lexico y Sintactico"
    );
    ventana.resize(1150, 800);

    QVBoxLayout *layoutPrincipal =
        new QVBoxLayout(&ventana);

    QLabel *titulo =
        new QLabel(
            "MOVIESCRIPT - ANALIZADOR LEXICO Y SINTACTICO"
        );

    titulo->setStyleSheet(
        "font-size: 24px;"
        "font-weight: bold;"
        "padding: 10px;"
    );

    QLabel *descripcion =
        new QLabel(
            "Analizador lexico con FLEX y analizador "
            "sintactico descendente recursivo en C++."
        );

    QTabWidget *pestanas =
        new QTabWidget();

    // =====================================================
    // PESTAÑA 1: ANALIZADOR
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

    tabla->setHorizontalHeaderLabels(
        encabezados
    );

    tabla->horizontalHeader()
         ->setSectionResizeMode(
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

    infoLayout->addWidget(totalTokens);
    infoLayout->addWidget(totalErrores);
    infoLayout->addWidget(estado);
    infoLayout->addWidget(estadoSintactico);

    layoutAnalizador->addWidget(codigoLabel);
    layoutAnalizador->addWidget(editor);
    layoutAnalizador->addLayout(botones);
    layoutAnalizador->addWidget(tabla);
    layoutAnalizador->addWidget(informacion);

    // =====================================================
    // PESTAÑA 2: AUTOMATA LEXICO
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
        "  |\n"
        "  | digito\n"
        "  v\n"
        "NUMERO\n"
        "  acepta uno o mas digitos\n"
        "\n"
        "INICIO\n"
        "  |\n"
        "  | comilla doble (\")\n"
        "  v\n"
        "CADENA\n"
        "  |\n"
        "  +-- espacios y tabulaciones -> IGNORAR\n"
        "  |\n"
        "  +-- salto de linea -> CONTAR LINEA\n"
        "  |\n"
        "  +-- // -> COMENTARIO\n"
        "  |\n"
        "  +-- otro caracter -> ERROR_LEXICO\n"
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
    // PESTAÑA 3: GRAMATICA
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
        "3. Cada escena debe contener al menos un elemento.\n"
        "4. CHARACTER necesita un IDENTIFICADOR.\n"
        "5. LOCATION necesita un IDENTIFICADOR.\n"
        "6. SAY necesita una CADENA entre comillas.\n"
        "7. ACTION necesita un IDENTIFICADOR.\n"
        "8. CAMERA necesita un IDENTIFICADOR.\n"
        "9. MUSIC necesita un IDENTIFICADOR.\n"
        "10. END es obligatorio al final del programa.\n"
        "\n"
        "El parser verifica estas estructuras mediante\n"
        "analisis sintactico descendente recursivo.\n"
    );

    layoutGramatica->addWidget(tituloGramatica);
    layoutGramatica->addWidget(explicacionGramatica);
    layoutGramatica->addWidget(gramatica);

    // =====================================================
    // AGREGAR LAS TRES PESTANAS
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

                estadoSintactico->setText(textoError);
            }

            QMessageBox::information(
                &ventana,
                "Resultado del analisis sintactico",
                QString::fromStdString(resultado.mensaje)
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
            estado->setText("Lexico: Sin analizar");

            estadoSintactico->setText(
                "Sintaxis: Sin analizar"
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
