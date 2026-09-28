
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

#include "lexer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget ventana;
    ventana.setWindowTitle("MovieScript - Analizador Lexico");
    ventana.resize(1150, 800);

    QVBoxLayout *layoutPrincipal =
        new QVBoxLayout(&ventana);

    QLabel *titulo =
        new QLabel("MOVIESCRIPT - ANALIZADOR LEXICO");

    titulo->setStyleSheet(
        "font-size: 26px;"
        "font-weight: bold;"
        "padding: 10px;"
    );

    QLabel *descripcion =
        new QLabel(
            "Analizador lexico desarrollado con FLEX"
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

    QGroupBox *informacion =
        new QGroupBox("Resultado del analisis");

    QHBoxLayout *infoLayout =
        new QHBoxLayout(informacion);

    QLabel *totalTokens =
        new QLabel("Tokens: 0");

    QLabel *totalErrores =
        new QLabel("Errores: 0");

    QLabel *estado =
        new QLabel("Estado: Listo");

    infoLayout->addWidget(totalTokens);
    infoLayout->addWidget(totalErrores);
    infoLayout->addWidget(estado);

    layoutAnalizador->addWidget(codigoLabel);
    layoutAnalizador->addWidget(editor);
    layoutAnalizador->addLayout(botones);
    layoutAnalizador->addWidget(tabla);
    layoutAnalizador->addWidget(informacion);

    // =====================================================
    // PESTAÑA 2: AUTOMATA
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
            "generar internamente un automata finito "
            "que reconoce los diferentes tipos de lexemas."
        );

    explicacion->setWordWrap(true);

    QTextEdit *automata =
        new QTextEdit();

    automata->setReadOnly(true);

    automata->setPlainText(
        "                         MOVIESCRIPT\n"
        "                    AUTOMATA LEXICO\n"
        "\n"
        "                              letra / _\n"
        "                         ┌───────────────────┐\n"
        "                         │                   ▼\n"
        "                      (INICIO) ───────> (IDENTIFICADOR)\n"
        "                         │                   ▲\n"
        "                         │                   │\n"
        "                         │             letra / digito / _\n"
        "                         │\n"
        "                         │ digito\n"
        "                         ▼\n"
        "                      (NUMERO)\n"
        "                         ▲\n"
        "                         │\n"
        "                         └────── digito\n"
        "\n"
        "                         (INICIO)\n"
        "                            │\n"
        "                            │ \"\n"
        "                            ▼\n"
        "                         (CADENA)\n"
        "                            │\n"
        "                            │ caracteres\n"
        "                            │ diferentes de \"\n"
        "                            └───────────────┐\n"
        "                                            │\n"
        "                                            │ \"\n"
        "                                            ▼\n"
        "                                      [ACEPTACION]\n"
        "\n"
        "                         (INICIO)\n"
        "                            │\n"
        "                            ├── espacio/tab ──> IGNORAR\n"
        "                            │\n"
        "                            ├── // ──────────> COMENTARIO\n"
        "                            │\n"
        "                            └── otro ────────> ERROR_LEXICO\n"
        "\n"
        "  PALABRAS RESERVADAS:\n"
        "  MOVIE  SCENE  CHARACTER  SAY  CAMERA\n"
        "  MUSIC  ACTION  LOCATION  CUT  END\n"
        "\n"
        "  REGLAS PRINCIPALES:\n"
        "  [0-9]+                         -> NUMERO\n"
        "  \"...\"                         -> CADENA\n"
        "  [a-zA-Z_][a-zA-Z0-9_]*       -> IDENTIFICADOR\n"
        "  //...                          -> COMENTARIO\n"
        "  otro caracter                  -> ERROR_LEXICO\n"
    );

    automata->setStyleSheet(
        "font-family: Consolas, monospace;"
        "font-size: 14px;"
    );

    QLabel *nota =
        new QLabel(
            "Nota: el diagrama mostrado es una representacion "
            "conceptual del automata. FLEX genera automaticamente "
            "el automata utilizado por el analizador."
        );

    nota->setWordWrap(true);

    layoutAutomata->addWidget(tituloAutomata);
    layoutAutomata->addWidget(explicacion);
    layoutAutomata->addWidget(automata);
    layoutAutomata->addWidget(nota);

    // =====================================================
    // AGREGAR PESTAÑAS
    // =====================================================

    pestanas->addTab(
        paginaAnalizador,
        "ANALIZADOR"
    );

    pestanas->addTab(
        paginaAutomata,
        "AUTOMATA"
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

            tabla->setRowCount(0);

            int errores = 0;

            for (const Token &token : tokens)
            {
                int fila =
                    tabla->rowCount();

                tabla->insertRow(fila);

                tabla->setItem(
                    fila,
                    0,
                    new QTableWidgetItem(
                        QString::fromStdString(
                            token.lexema
                        )
                    )
                );

                tabla->setItem(
                    fila,
                    1,
                    new QTableWidgetItem(
                        QString::fromStdString(
                            token.tipo
                        )
                    )
                );

                tabla->setItem(
                    fila,
                    2,
                    new QTableWidgetItem(
                        QString::number(
                            token.linea
                        )
                    )
                );

                if (token.tipo ==
                    "ERROR_LEXICO")
                {
                    errores++;
                }
            }

            totalTokens->setText(
                "Tokens: " +
                QString::number(
                    tokens.size()
                )
            );

            totalErrores->setText(
                "Errores: " +
                QString::number(
                    errores
                )
            );

            if (errores == 0)
            {
                estado->setText(
                    "Estado: ANALISIS CORRECTO"
                );
            }
            else
            {
                estado->setText(
                    "Estado: CON ERRORES LEXICOS"
                );
            }
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

            totalTokens->setText(
                "Tokens: 0"
            );

            totalErrores->setText(
                "Errores: 0"
            );

            estado->setText(
                "Estado: Listo"
            );
        }
    );

    // =====================================================
    // BOTON EJEMPLO
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
    // VENTANA
    // =====================================================

    layoutPrincipal->addWidget(titulo);
    layoutPrincipal->addWidget(descripcion);
    layoutPrincipal->addWidget(pestanas);
    ventana.show();

    return app.exec();
}

