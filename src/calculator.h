#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

namespace Ui {
class Calculator;
}

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0);
    ~Calculator();

private slots:
    void on_b0_clicked();
    void on_b1_clicked();
    void on_b2_clicked();
    void on_b3_clicked();
    void on_b4_clicked();
    void on_b5_clicked();
    void on_b6_clicked();
    void on_b7_clicked();
    void on_b8_clicked();
    void on_b9_clicked();
    void on_signButton_clicked();

    void on_clearButton_clicked();
    void on_backspaceButton_clicked();

    void on_plusButton_clicked();
    void on_minusButton_clicked();
    void on_multiplyButton_clicked();
    void on_divideButton_clicked();
    void on_powerButton_clicked();
    void on_sqrtButton_clicked();
    void on_rootButton_clicked();
    void on_factButton_clicked();
    void on_modButton_clicked();
    void on_fromBaseButton_clicked();
    void on_toBaseButton_clicked();

    void on_answerButton_clicked();

    void on_input_textChanged();

    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::Calculator *ui;
};

#endif // CALCULATOR_H
