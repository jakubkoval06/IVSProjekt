#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>

//main application window - inherits QMainWindow
class CalculatorWindow : public QMainWindow {
    Q_OBJECT
public:
    CalculatorWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
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

    //helper to avoid repeating the same 4 lines for every button
    QPushButton *makeButton(const QString &text) {
        QPushButton *btn = new QPushButton(text, this);
        btn->setMinimumHeight(50);
        return btn;
    }

    void buildDisplay() {
        display = new QLineEdit(this);
        display->setReadOnly(true);
        display->setAlignment(Qt::AlignRight);
        display->setPlaceholderText("Results");
        display->setMinimumHeight(40);
        //display
        layout->addWidget(display, 0, 0, 1, 4);
    }

    void buildDigitButtons() {
        //match mockup (1,2,3 / 4,5,6 / 7,8,9)
        //but nned other functions so not really 1:1
        int number = 1;
        for (int col = 0; col < 3; ++col) {
            for (int row = 1; row <= 3; ++row) {
                layout->addWidget(makeButton(QString::number(number)), row, col);
                number++;
            }
        }
    }

    void buildOperatorButtons() {
        const QString ops[] = { "+", "-", "*", "/" };
        for (int i = 0; i < 4; ++i) {
            layout->addWidget(makeButton(ops[i]), i + 1, 3);
        }
    }

    void buildBottomRow() {
        layout->addWidget(makeButton("0"), 4, 0);
        layout->addWidget(makeButton("."), 4, 1);
        layout->addWidget(makeButton("C"), 4, 2);
    }

    void buildCalculateButton() {
        layout->addWidget(makeButton("Calculate"), 5, 0, 1, 4);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    CalculatorWindow window;
    window.show();
    return app.exec();
}

#include "gui.moc"