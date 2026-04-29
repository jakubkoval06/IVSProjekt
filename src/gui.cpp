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
#include <QMessageBox>
#include <QRegularExpression>
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
        setMinimumSize(460, 500);

        QWidget *central = new QWidget(this);
        setCentralWidget(central);

        // Visual styling - csslike
        central->setStyleSheet(R"(
            QWidget {
                background-color: #f5f5f7;
                font-family: "Segoe UI", "Helvetica Neue", sans-serif;
                font-size: 16px;
            }
            QLineEdit {
                background-color: #ffffff;
                border: none;
                border-radius: 8px;
                padding: 8px 14px;
                font-size: 22px;
                color: #000000;
            }
            QPushButton {
                background-color: #ffffff;
                border: 1px solid #e0e0e4;
                border-radius: 8px;
                color: #000000;
                font-size: 16px;
            }
            QPushButton:hover {
                background-color: #ececf0;
            }
            QPushButton:pressed {
                background-color: #dcdce0;
            }
            QPushButton#op {
                background-color: #ececf0;
                font-weight: none;
            }
            QPushButton#op:hover  { background-color: #dcdce0; }
            QPushButton#op:pressed { background-color: #c8c8cc; }
            QPushButton#clear {
                color: #FF0000;
                font-weight: none;
            }
            QPushButton#primary {
                background-color: #ffffff;
                color: #000000;
                font-size: 18px;
                font-weight: none;
                border: 1px solid #e0e0e4;
            }
            QPushButton#primary:hover  { background-color: #2c2c2e; }
            QPushButton#primary:pressed { background-color: #000000; }
            QPushButton#help {
                background-color: #654848;
                color: #ffffff;
                font-weight: none;
            }
            QPushButton#help:hover { background-color: #1a1a1a; }
        )");

        //qgrid layout
        layout = new QGridLayout(central);
        layout->setSpacing(6);
        layout->setContentsMargins(12, 12, 12, 12);

        // Equal column widths so calculate doesn't eat half the window
        for (int col = 0; col < 5; ++col) layout->setColumnStretch(col, 1);
        for (int row = 0; row < 7; ++row) layout->setRowStretch(row, 1);

        buildDisplay();
        buildFunctionRow();
        buildLogButton();
        buildParenthesesAndClearRow();
        buildDigitButtons();
        buildOperatorButtons();
        buildBottomRow();
        buildCalculateButton();
        buildHelpButton();
    }

private:
    QLineEdit *display;
    QGridLayout *layout;
    bool hasError = false;

    /**
     * @brief Creates a button with minimum height to avoid redundancy.
     * @param text Label displayed on the button.
     * @return Pointer to the newly created button.
     */
    QPushButton *makeButton(const QString &text) {
        QPushButton *btn = new QPushButton(text, this);
        btn->setMinimumHeight(50);
        btn->setFocusPolicy(Qt::NoFocus);
        btn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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
                    display->setText(QString::number(evaluate(prepareExpression(autoCloseParens(display->text())).toStdString())));
                } catch (std::exception &e) {
                    display->setText(QString::fromStdString(e.what()));
                    hasError = true;
                }
                break;
            case Qt::Key_Backspace:
                if (!display->text().isEmpty())
                    display->setText(display->text().chopped(1));
                break;
            case Qt::Key_L:
                appendToDisplay("log");
                break;
            case Qt::Key_Escape:
            case Qt::Key_C:
                display->clear();
                break;
            default:
                QMainWindow::keyPressEvent(event);
        }
    }

    /** @brief Creates and places the read-only text in the result window. */
    void buildDisplay() {
        display = new QLineEdit(this);
        display->setReadOnly(true);
        display->setFocusPolicy(Qt::NoFocus);
        display->setAlignment(Qt::AlignRight);
        display->setMinimumHeight(40);
        display->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        layout->addWidget(display, 0, 0, 1, 5);
    }

    /** @brief Places the help button in the slot next to the decimal point. */
    void buildHelpButton() {
        QPushButton *helpBtn = makeButton("?");
        helpBtn->setObjectName("help");
        connect(helpBtn, &QPushButton::clicked, this, [this]() {
            QMessageBox::information(this, "Help",
                "OPERATIONS\n"
                "  +  -  *  /     basic arithmetic\n"
                "  ^              power  (e.g. 2^8)\n"
                "\n"
                "FUNCTIONS\n"
                "  ²√(x)         square root       (e.g. ²√(9))\n"
                "  n√(x)         nth root of x     (e.g. 3√(27) = cube root of 27)\n"
                "  fact(x)       factorial         (e.g. fact(5))\n"
                "  log<base>(x)  logarithm of x w base x (e.g. log2(5))"
                "\n"
                "KEYBOARD\n"
                "  Enter         calculate\n"
                "  Backspace     delete last character\n"
                "  Escape        clear\n"
                "  L             insert log\n"
            );
        });
        layout->addWidget(helpBtn, 6, 3);
    }

    /** @brief Converts display notation to parser syntax before evaluation. */
    QString prepareExpression(const QString &expression) {
        QString result = expression;
        result.replace("²√(", "sqrt(");

        // Convert n√(expr) -> root(expr,n)  e.g. 3√(27) -> root(27,3)
        // doing backend work imo
        QRegularExpression nthRootRegex(R"((\d+(?:\.\d+)?)√\()");
        int searchOffset = 0;
        while (true) {
            QRegularExpressionMatch match = nthRootRegex.match(result, searchOffset);
            if (!match.hasMatch()) break;

            int matchStart   = match.capturedStart();
            int openParenPos = match.capturedEnd() - 1;
            QString rootDegree = match.captured(1);

            int parenDepth    = 1;
            int scanPos       = openParenPos + 1;
            while (scanPos < result.size() && parenDepth > 0) {
                if (result[scanPos] == '(') parenDepth++;
                else if (result[scanPos] == ')') parenDepth--;
                scanPos++;
            }

            QString innerExpr   = result.mid(openParenPos + 1, scanPos - openParenPos - 2);
            QString replacement = "root(" + innerExpr + "," + rootDegree + ")";
            result.replace(matchStart, scanPos - matchStart, replacement);
            searchOffset = matchStart + replacement.size();
        }

        return result;
    }

    /** @brief Appends missing closing parentheses to the expression. */
    QString autoCloseParens(const QString &expression) {
        int openParenCount = 0;
        for (QChar character : expression) {
            if (character == '(') {
                openParenCount++;
            } else if (character == ')') {
                openParenCount--;
            }
        }
        QString balanced = expression;
        for (int missing = 0; missing < openParenCount; ++missing) {
            balanced += ')';
        }
        return balanced;
    }

    /** @brief Adds a symbol to the end of the display. Clears first if the last result was an error. */
    void appendToDisplay(const QString &text) {
        if (hasError) { display->clear(); hasError = false; }
        display->setText(display->text() + text);
    }

    /**
     * @brief Places square root, factorial, root, power and backspace in row 1.
     */
    void buildFunctionRow() {
        QPushButton *squareRoot  = makeButton("²√");
        squareRoot->setObjectName("op");
        QPushButton *factorial   = makeButton("n!");
        factorial->setObjectName("op");
        QPushButton *generalRoot = makeButton("√");
        generalRoot->setObjectName("op");
        QPushButton *power       = makeButton("^");
        power->setObjectName("op");
        QPushButton *backspace   = makeButton("⌫");

        connect(squareRoot,  &QPushButton::clicked, this, [this]() { appendToDisplay("²√("); });
        connect(factorial,   &QPushButton::clicked, this, [this]() { appendToDisplay("fact("); });
        connect(generalRoot, &QPushButton::clicked, this, [this]() { appendToDisplay("√("); });
        connect(power,       &QPushButton::clicked, this, [this]() { appendToDisplay("^"); });
        connect(backspace,   &QPushButton::clicked, this, [this]() {
            QString text = display->text();
            if (!text.isEmpty()) display->setText(text.chopped(1));
        });

        layout->addWidget(squareRoot,  1, 0);
        layout->addWidget(factorial,   1, 1);
        layout->addWidget(generalRoot, 1, 2);
        layout->addWidget(power,       1, 3);
        layout->addWidget(backspace,   1, 4);
    }

    /**
     * @brief Places opening parenthesis, closing parenthesis, clear and divide in row 2.
     */
    void buildParenthesesAndClearRow() {
        QPushButton *openParen  = makeButton("(");
        QPushButton *closeParen = makeButton(")");
        QPushButton *clear      = makeButton("C");
        clear->setObjectName("clear");
        QPushButton *divide     = makeButton("/");
        divide->setObjectName("op");

        connect(openParen,  &QPushButton::clicked, this, [this]() { appendToDisplay("("); });
        connect(closeParen, &QPushButton::clicked, this, [this]() { appendToDisplay(")"); });
        connect(clear,      &QPushButton::clicked, this, [this]() { display->clear(); });
        connect(divide,     &QPushButton::clicked, this, [this]() { appendToDisplay("/"); });

        layout->addWidget(openParen,  2, 0);
        layout->addWidget(closeParen, 2, 1);
        layout->addWidget(clear,      2, 2);
        layout->addWidget(divide,     2, 3);
    }

    /** @brief Places digit buttons. */
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

    /** @brief Places operator buttons *, -, + in column 3, rows 3-5. */
    void buildOperatorButtons() {
        QPushButton *multiply = makeButton("*");
        multiply->setObjectName("op");
        QPushButton *minus    = makeButton("-");
        minus->setObjectName("op");
        QPushButton *plus     = makeButton("+");
        plus->setObjectName("op");

        connect(multiply, &QPushButton::clicked, this, [this]() { appendToDisplay("*"); });
        connect(minus,    &QPushButton::clicked, this, [this]() { appendToDisplay("-"); });
        connect(plus,     &QPushButton::clicked, this, [this]() { appendToDisplay("+"); });

        layout->addWidget(multiply, 3, 3);
        layout->addWidget(minus,    4, 3);
        layout->addWidget(plus,     5, 3);
    }

    /** @brief Places 0 and decimal point in the bottom row. */
    void buildBottomRow() {
        QPushButton *zero = makeButton("0");
        QPushButton *dot  = makeButton(".");

        connect(zero, &QPushButton::clicked, this, [this]() { appendToDisplay("0"); });
        connect(dot,  &QPushButton::clicked, this, [this]() { appendToDisplay("."); });

        layout->addWidget(zero, 6, 0, 1, 2);
        layout->addWidget(dot,  6, 2);
    }

    /** @brief Places log<base>(x) button. */
    void buildLogButton() {
        QPushButton *logBtn = makeButton("log");
        logBtn->setObjectName("op");
        connect(logBtn, &QPushButton::clicked, this, [this]() { appendToDisplay("log"); });
        layout->addWidget(logBtn, 2, 4);
    }

    /** @brief Places the Calculate button in column 4, in rows 3-6. */
    void buildCalculateButton() {
        QPushButton *button = makeButton("=");
        button->setObjectName("primary");
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(button, &QPushButton::clicked, this, [this]() {
            try {
                double result = evaluate(prepareExpression(autoCloseParens(display->text())).toStdString());
                display->setText(QString::number(result));
                hasError = false;
            } catch (std::exception &e) {
                display->setText(QString::fromStdString(e.what()));
                hasError = true;
            }
        });
        layout->addWidget(button, 3, 4, 4, 1);
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
