//  ==============================
//  project:    IVS Calculator
//  author:     xferenj00 Jakub Ferencik
//  date:       2026
//  ==============================

/**
 * @file gui.cpp
 * @brief Qt GUI for the IVS calculator. Builds the gui for our math library.
 * @author Jakub Ferencik / xferenj00
 * @date 2026
 */

#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>
#include "parser.h"

/**
 * @brief Main application window for the calculator.
 *
 * Inherits QMainWindow and builds the full button layout on construction.
 * Q_OBJECT is required for Qt buttons.
 */
class CalculatorWindow : public QMainWindow {
    Q_OBJECT
public:
    /** @brief Constructs the calculator window and initialises all widgets. */
    CalculatorWindow() : QMainWindow(nullptr) {
        setWindowTitle("Calculator");
        //set the window title and fixed size to not loose sanity later
        setFixedSize(380, 580);

        QWidget *central = new QWidget(this);
        setCentralWidget(central);

        //qgrid layout
        layout = new QGridLayout(central);
        layout->setSpacing(6);
        layout->setContentsMargins(12, 12, 12, 12);

        buildDisplay();
        buildDigitButtons();
        buildOperatorButtons();
        buildBottomRow();
        buildParenthesesAndPowerRow();
        buildFunctionRow();
        buildCalculateButton();
    }

private:
    QLineEdit *display;
    QGridLayout *layout;

    /**
     * @brief Creates a button with minimum height to avoid redundancy.
     * @param text Label displayed on the button.
     * @return Pointer to the newly created button.
     */
    QPushButton *makeButton(const QString &text) {
        QPushButton *btn = new QPushButton(text, this);
        btn->setMinimumHeight(50);
        return btn;
    }

    /**
     * @brief Maps press events to their intended function.
     * Digits, operators and parentheses append to the end of the string.
     * Enter calculates, backspace deletes last character, escape clears.
     */
    void keyPressEvent(QKeyEvent *event) override {
        QString key = event->text();

        if (!key.isEmpty() && (key[0].isDigit() || QString("+-*/.^()").contains(key[0]))) {
            appendToDisplay(key);
            return;
        }

        switch (event->key()) {
            case Qt::Key_Return:
            case Qt::Key_Enter:
                try {
                    QString expr = display->text();
                    expr.replace("²√(", "sqrt(");
                    expr.replace("n!(", "fact(");
                    expr.replace("√(", "root(");
                    display->setText(QString::number(evaluate(expr.toStdString())));
                } catch (std::exception &e) {
                    display->setText("Error");
                }
                break;
            case Qt::Key_Backspace:
                if (!display->text().isEmpty())
                    display->setText(display->text().chopped(1));
                break;
            case Qt::Key_Escape:
                display->clear();
                break;
            default:
                QMainWindow::keyPressEvent(event);
        }
    }

    /** @brief Creates and places the read-only text in the result window.  */
    void buildDisplay() {
        display = new QLineEdit(this);
        display->setReadOnly(true);
        display->setAlignment(Qt::AlignRight);
        display->setPlaceholderText("Results");
        display->setMinimumHeight(40);
        layout->addWidget(display, 0, 0, 1, 4);
    }

    /** @brief Adds a symbol to the end of the display when a button is clicked. */
    void appendToDisplay(const QString &text) {
        display->setText(display->text() + text);
    }

    /** @brief Places sqrt, fact and root buttons in top row. */
    void buildFunctionRow() {
        QPushButton *squareRoot  = makeButton("²√");
        QPushButton *factorial   = makeButton("n!");
        QPushButton *generalRoot = makeButton("√");

        connect(squareRoot,  &QPushButton::clicked, this, [this]() { appendToDisplay("²√("); });
        connect(factorial,   &QPushButton::clicked, this, [this]() { appendToDisplay("n!("); });
        connect(generalRoot, &QPushButton::clicked, this, [this]() { appendToDisplay("√("); });

        layout->addWidget(squareRoot,  1, 0);
        layout->addWidget(factorial,   1, 1);
        layout->addWidget(generalRoot, 1, 2, 1, 2);
    }

    /** @brief Places parenthesis, power and backspace buttons in row 2. */
    void buildParenthesesAndPowerRow() {
        QPushButton *openParen  = makeButton("(");
        QPushButton *closeParen = makeButton(")");
        QPushButton *power      = makeButton("^");
        QPushButton *backspace  = makeButton("⌫");

        connect(openParen,  &QPushButton::clicked, this, [this]() { appendToDisplay("("); });
        connect(closeParen, &QPushButton::clicked, this, [this]() { appendToDisplay(")"); });
        connect(power,      &QPushButton::clicked, this, [this]() { appendToDisplay("^"); });
        connect(backspace,  &QPushButton::clicked, this, [this]() {
            QString text = display->text();
            if (!text.isEmpty()) display->setText(text.chopped(1));
        });

        layout->addWidget(openParen,  2, 0);
        layout->addWidget(closeParen, 2, 1);
        layout->addWidget(power,      2, 2);
        layout->addWidget(backspace,  2, 3);
    }

    /** @brief Places digit buttons 7-9, 4-6, 1-3 in rows 3-5. */
    void buildDigitButtons() {
        QPushButton *btn7 = makeButton("7");
        QPushButton *btn8 = makeButton("8");
        QPushButton *btn9 = makeButton("9");
        QPushButton *btn4 = makeButton("4");
        QPushButton *btn5 = makeButton("5");
        QPushButton *btn6 = makeButton("6");
        QPushButton *btn1 = makeButton("1");
        QPushButton *btn2 = makeButton("2");
        QPushButton *btn3 = makeButton("3");

        connect(btn7, &QPushButton::clicked, this, [this]() { appendToDisplay("7"); });
        connect(btn8, &QPushButton::clicked, this, [this]() { appendToDisplay("8"); });
        connect(btn9, &QPushButton::clicked, this, [this]() { appendToDisplay("9"); });
        connect(btn4, &QPushButton::clicked, this, [this]() { appendToDisplay("4"); });
        connect(btn5, &QPushButton::clicked, this, [this]() { appendToDisplay("5"); });
        connect(btn6, &QPushButton::clicked, this, [this]() { appendToDisplay("6"); });
        connect(btn1, &QPushButton::clicked, this, [this]() { appendToDisplay("1"); });
        connect(btn2, &QPushButton::clicked, this, [this]() { appendToDisplay("2"); });
        connect(btn3, &QPushButton::clicked, this, [this]() { appendToDisplay("3"); });

        layout->addWidget(btn7, 3, 0);
        layout->addWidget(btn8, 3, 1);
        layout->addWidget(btn9, 3, 2);
        layout->addWidget(btn4, 4, 0);
        layout->addWidget(btn5, 4, 1);
        layout->addWidget(btn6, 4, 2);
        layout->addWidget(btn1, 5, 0);
        layout->addWidget(btn2, 5, 1);
        layout->addWidget(btn3, 5, 2);
    }

    /** @brief Places operator buttons /, *, -, + in column 3. */
    void buildOperatorButtons() {
        QPushButton *divide   = makeButton("/");
        QPushButton *multiply = makeButton("*");
        QPushButton *minus    = makeButton("-");
        QPushButton *plus     = makeButton("+");

        connect(divide,   &QPushButton::clicked, this, [this]() { appendToDisplay("/"); });
        connect(multiply, &QPushButton::clicked, this, [this]() { appendToDisplay("*"); });
        connect(minus,    &QPushButton::clicked, this, [this]() { appendToDisplay("-"); });
        connect(plus,     &QPushButton::clicked, this, [this]() { appendToDisplay("+"); });

        layout->addWidget(divide,   3, 3);
        layout->addWidget(multiply, 4, 3);
        layout->addWidget(minus,    5, 3);
        layout->addWidget(plus,     6, 3);
    }

    /** @brief Places 0, decimal point and clear in the bottom row. */
    void buildBottomRow() {
        QPushButton *zero  = makeButton("0");
        QPushButton *dot   = makeButton(".");
        QPushButton *clear = makeButton("C");

        connect(zero,  &QPushButton::clicked, this, [this]() { appendToDisplay("0"); });
        connect(dot,   &QPushButton::clicked, this, [this]() { appendToDisplay("."); });
        connect(clear, &QPushButton::clicked, this, [this]() { display->clear(); });

        layout->addWidget(zero,  6, 0);
        layout->addWidget(dot,   6, 1);
        layout->addWidget(clear, 6, 2);
    }

    /** @brief Places the Calculate button spanning the full width at the bottom. */
    void buildCalculateButton() {
        QPushButton *button = makeButton("Calculate");
        connect(button, &QPushButton::clicked, this, [this]() {
            try {
                QString expr = display->text();
                expr.replace("²√(", "sqrt(");
                expr.replace("n!(", "fact(");
                expr.replace("√(", "root(");
                double result = evaluate(expr.toStdString());
                display->setText(QString::number(result));
            } catch (std::exception &e) {
                display->setText("Error");
            }
        });
        layout->addWidget(button, 7, 0, 1, 4);
    }
};

/**
 * @brief Initialises Qt and launches the calculator window.
 * @param argc Argument count.
 * @param argv Argument values.
 * @return Exit code from Qt event loop.
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CalculatorWindow window;
    window.show();
    return app.exec();
}

#include "gui.moc"