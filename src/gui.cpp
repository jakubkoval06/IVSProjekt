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

    /** @brief Places digit buttons 1-9 in order to match the mockup layout. */
    void buildDigitButtons() {
        //match mockup (vertically):(1,2,3 / 4,5,6 / 7,8,9)
        //but i need other functions so not really 1:1
        int number = 1;
        for (int col = 0; col < 3; ++col) {
            for (int row = 1; row <= 3; ++row) {
                layout->addWidget(makeButton(QString::number(number)), row, col);
                number++;
            }
        }
    }

    /** @brief Places operator buttons (+, -, *, /) in their column of the grid. */
    void buildOperatorButtons() {
        const QString ops[] = { "+", "-", "*", "/" };
        for (int i = 0; i < 4; ++i) {
            layout->addWidget(makeButton(ops[i]), i + 1, 3);
        }
    }

    /** @brief Places 0, "." and clear buttons in the bottom row. */
    void buildBottomRow() {
        layout->addWidget(makeButton("0"), 4, 0);
        layout->addWidget(makeButton("."), 4, 1);
        layout->addWidget(makeButton("C"), 4, 2);
    }

    /** @brief Places the Calculate button spanning the full width of the bottom row. */
    void buildCalculateButton() {
        layout->addWidget(makeButton("Calculate"), 5, 0, 1, 4);
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