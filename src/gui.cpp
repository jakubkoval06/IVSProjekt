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
        setFixedSize(380, 420);

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

    /** @brief Places digit buttons 1-9 and connects each to add its digit to the display. */
    void buildDigitButtons() {
        //match mockup (vertically):(1,2,3 / 4,5,6 / 7,8,9)
        //but i need other functions so not really 1:1
        int number = 1;
        for (int col = 0; col < 3; ++col) {
            for (int row = 1; row <= 3; ++row) {
                QPushButton *btn = makeButton(QString::number(number));
                connect(btn, &QPushButton::clicked, this, [this, number]() {
                    appendToDisplay(QString::number(number));
                });
                layout->addWidget(btn, row, col);
                number++;
            }
        }
    }

    /** @brief Places operator buttons (+, -, *, /) and connects each to add symbols to the string. */
    void buildOperatorButtons() {
        const QString ops[] = { "+", "-", "*", "/" };
        for (int i = 0; i < 4; ++i) {
            QPushButton *button = makeButton(ops[i]);
            connect(button, &QPushButton::clicked, this, [this, op = ops[i]]() {
                appendToDisplay(op);
            });
            layout->addWidget(button, i + 1, 3);
        }
    }

    /** @brief Places 0, decimal point and clear. */
    void buildBottomRow() {
        QPushButton *zero = makeButton("0");
        QPushButton *dot = makeButton(".");
        QPushButton *clear = makeButton("C");

        connect(zero, &QPushButton::clicked, this, [this]() { appendToDisplay("0"); });
        connect(dot, &QPushButton::clicked, this, [this]() { appendToDisplay("."); });
        connect(clear, &QPushButton::clicked, this, [this]() { display->clear(); });

        layout->addWidget(zero,  4, 0);
        layout->addWidget(dot,   4, 1);
        layout->addWidget(clear, 4, 2);
    }

    /** @brief Places the Calculate button and connects it to calculate the display expression with parser. */
    void buildCalculateButton() {
        QPushButton *button = makeButton("Calculate");
        connect(button, &QPushButton::clicked, this, [this]() {
            try {
                double result = evaluate(display->text().toStdString());
                display->setText(QString::number(result));
            } catch (std::exception &e) {
                display->setText("Error");
            }
        });
        layout->addWidget(button, 5, 0, 1, 4);
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