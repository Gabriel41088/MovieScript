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

#include "lexer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QWidget ventana;
    ventana.setWindowTitle("MovieScript - Analizador Lexico");
    ventana.resize(1100, 750);

    QVBoxLayout *layout = new QVBoxLayout(&ventana);

    // =========================
    // TITULO
    // =========================

    QLabel *titulo = new QLabel(
        "MOVIESCRIPT - ANALIZADOR LEXICO"
    );

    titulo->setStyleSheet(
        "font-size: 26px;"
        "font-weight: bold;"
        "padding: 10px;"
    );

    QLabel *descripcion = new QLabel(
        "Analizador lexico desarrollado con FLEX"
    );

    // =========================
    // EDITOR
    // =========================

    QLabel *codigoLabel = new QLabel(
        "Codigo MovieScript:"
    );

    QTextEdit *editor = new QTextEdit();

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

    // =========================
    // BOTONES
    // =========================

    QHBoxLayout *botones = new QHBoxLayout();

    QPushButton *analizar =
        new QPushButton("ANALIZAR");

    QPushButton *limpiar =
        new QPushButton("LIMPIAR");

    QPushButton *ejemplo =
        new QPushButton("CARGAR EJEMPLO");

    botones->addWidget(analizar);
    botones->addWidget(limpiar);
    botones->addWidget(ejemplo);

    // =========================
    // TABLA
    // =========================

    QTableWidget *tabla = new QTableWidget();

    tabla->setColumnCount(3);

    QStringList encabezados;

    encabezados << "Lexema"
                << "Token"
                << "Linea";

    tabla->setHorizontalHeaderLabels(encabezados);

    tabla->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch
    );

    // =========================
    // INFORMACION
    // =========================

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

    // =========================
    // AGREGAR A LA VENTANA
    // =========================

    layout->addWidget(titulo);
    layout->addWidget(descripcion);
    layout->addWidget(codigoLabel);
    layout->addWidget(editor);
    layout->addLayout(botones);
    layout->addWidget(tabla);
    layout->addWidget(informacion);

    // =========================
    // BOTON ANALIZAR
    // =========================

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
                int fila = tabla->rowCount();

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

                if (token.tipo == "ERROR_LEXICO")
                {
                    errores++;
                }
            }

            totalTokens->setText(
                "Tokens: " +
                QString::number(tokens.size())
            );

            totalErrores->setText(
                "Errores: " +
                QString::number(errores)
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

    // =========================
    // BOTON LIMPIAR
    // =========================

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

    // =========================
    // BOTON EJEMPLO
    // =========================

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

    ventana.show();

    return app.exec();
}
