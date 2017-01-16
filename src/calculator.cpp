#include<QStringListModel>
#include<QModelIndex>
#include "calculator.h"
#include "ui_calculator.h"
#include "biginteger.h"

BigInteger n1, n2;
bool waitingForOperand = true;
char operand = 'x';
QStringListModel *model;
QString operation = "";


Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Calculator)
{
    ui->setupUi(this);

    model = new QStringListModel(this);
    QStringList List;
    model->setStringList(List);
    ui->listView->setModel(model);

    ui->input->setFocus();
}

Calculator::~Calculator()
{
    delete ui;
}

void addToHistory(QString str) {
    model->insertRow(0);
    QModelIndex index = model->index(0);
    model->setData(index, str);
}

void Calculator::on_b0_clicked() { ui->input->insertPlainText("0"); ui->input->setFocus(); }
void Calculator::on_b1_clicked() { ui->input->insertPlainText("1"); ui->input->setFocus(); }
void Calculator::on_b2_clicked() { ui->input->insertPlainText("2"); ui->input->setFocus(); }
void Calculator::on_b3_clicked() { ui->input->insertPlainText("3"); ui->input->setFocus(); }
void Calculator::on_b4_clicked() { ui->input->insertPlainText("4"); ui->input->setFocus(); }
void Calculator::on_b5_clicked() { ui->input->insertPlainText("5"); ui->input->setFocus(); }
void Calculator::on_b6_clicked() { ui->input->insertPlainText("6"); ui->input->setFocus(); }
void Calculator::on_b7_clicked() { ui->input->insertPlainText("7"); ui->input->setFocus(); }
void Calculator::on_b8_clicked() { ui->input->insertPlainText("8"); ui->input->setFocus(); }
void Calculator::on_b9_clicked() { ui->input->insertPlainText("9"); ui->input->setFocus(); }

void Calculator::on_signButton_clicked() {
    QString txt = ui->input->toPlainText();
    if(txt[0] == '-')
        ui->input->setText(txt.mid(1));
    else
        ui->input->setText("-" + txt);

    ui->input->moveCursor(QTextCursor::End);
    ui->input->setFocus();
}

void Calculator::on_clearButton_clicked() {
    ui->input->setText("");
    ui->input->setFocus();
}
void Calculator::on_backspaceButton_clicked() {
    QString s = ui->input->toPlainText();
    s.remove(s.length()-1, 1);
    ui->input->setText(s);
    ui->input->moveCursor(QTextCursor::End);
    ui->input->setFocus();
}

void Calculator::on_plusButton_clicked() {
    if(waitingForOperand) {
        n1 = ui->input->toPlainText();
        ui->input->setText("");
        waitingForOperand = false;
        operand = '+';
        operation += n1.toString();
        operation += " + ";
    } else {
        on_answerButton_clicked();
    }
    ui->input->setFocus();
}

void Calculator::on_minusButton_clicked(){
    if(waitingForOperand) {
        n1 = ui->input->toPlainText();
        ui->input->setText("");
        waitingForOperand = false;
        operand = '-';
        operation += n1.toString();
        operation += " - ";
    } else {
        on_answerButton_clicked();
    }
    ui->input->setFocus();
}
void Calculator::on_multiplyButton_clicked(){
    if(waitingForOperand) {
        n1 = ui->input->toPlainText();
        ui->input->setText("");
        waitingForOperand = false;
        operand = '*';
        operation += n1.toString();
        operation += " * ";
    } else {
        on_answerButton_clicked();
    }
    ui->input->setFocus();
}
void Calculator::on_divideButton_clicked(){
    if(waitingForOperand) {
        n1 = ui->input->toPlainText();
        ui->input->setText("");
        waitingForOperand = false;
        operand = '/';
        operation += n1.toString();
        operation += " / ";
    } else {
        on_answerButton_clicked();
    }
    ui->input->setFocus();
}
void Calculator::on_powerButton_clicked(){
    if(waitingForOperand) {
        n1 = ui->input->toPlainText();
        ui->input->setText("");
        waitingForOperand = false;
        operand = '^';
        operation += n1.toString();
        operation += " ^ ";
    } else {
        on_answerButton_clicked();
    }
    ui->input->setFocus();
}

void Calculator::on_modButton_clicked()
{
    if(waitingForOperand) {
        n1 = ui->input->toPlainText();
        ui->input->setText("");
        waitingForOperand = false;
        operand = '%';
        operation += n1.toString();
        operation += " % ";
    } else {
        on_answerButton_clicked();
    }
    ui->input->setFocus();
}
void Calculator::on_rootButton_clicked()
{
    if(waitingForOperand) {
        n1 = ui->input->toPlainText();
        ui->input->setText("");
        waitingForOperand = false;
        operand = 'r';
        operation += n1.toString();
        operation += " root ";
    } else {
        on_answerButton_clicked();
    }
    ui->input->setFocus();
}
void Calculator::on_fromBaseButton_clicked()
{
    if(waitingForOperand) {
        n1 = ui->input->toPlainText();
        ui->input->setText("");
        waitingForOperand = false;
        operand = 'f';
        operation += n1.toString();
        operation += " from base ";
    } else {
        on_answerButton_clicked();
    }
    ui->input->setFocus();
}
void Calculator::on_toBaseButton_clicked()
{
    if(waitingForOperand) {
        n1 = ui->input->toPlainText();
        ui->input->setText("");
        waitingForOperand = false;
        operand = 't';
        operation += n1.toString();
        operation += " to base ";
    } else {
        on_answerButton_clicked();
    }
    ui->input->setFocus();
}

void Calculator::on_sqrtButton_clicked(){
    BigInteger n = ui->input->toPlainText();
    BigInteger s = n.sqrt();
    ui->input->setText(s.toString());
    ui->input->moveCursor(QTextCursor::End);
    addToHistory("sqrt " + n.toString() + " = " + s.toString());
    ui->input->setFocus();
}
void Calculator::on_factButton_clicked(){
    BigInteger n = ui->input->toPlainText();
    BigInteger s = n.fact();
    ui->input->setText(s.toString());
    ui->input->moveCursor(QTextCursor::End);
    addToHistory(n.toString() + "! = " + s.toString());
    ui->input->setFocus();
}



void Calculator::on_answerButton_clicked()
{
    if(waitingForOperand) return;

    n2 = ui->input->toPlainText();

    operation += n2.toString();
    operation += " = ";
    BigInteger ans;

    switch (operand) {
    case '+':
        ans = n1 + n2;
        break;
    case '-':
        ans = n1 - n2;
        break;
    case '*':
        ans = n1 * n2;
        break;
    case '/':
        ans = n1 / n2;
        break;
    case '^':
        ans = n1 ^ n2.toLong();
        break;
    case '%':
        ans = n1 % n2;
        break;
    case 'r':
        ans = n1.root(n2.toLong());
        break;
    case 'f':
        ans = n1.fromBase(n2.toLong());
        break;
    case 't':
        ans = n1.toBase(n2.toLong());
        break;
    default:
        break;
    }

    ui->input->setText(ans.toString());
    ui->input->moveCursor(QTextCursor::End);
    ui->input->setFocus();
    waitingForOperand = true;

    operation += ans.toString();
    addToHistory(operation);
    operation = "";
}

void Calculator::on_input_textChanged()
{
    QString txt = ui->input->toPlainText();
    if(txt != "" && txt != "-" && !QRegExp("-?[0-9]+").exactMatch(txt)) {
        on_backspaceButton_clicked();
    }
}

void Calculator::on_listView_doubleClicked(const QModelIndex &index)
{
    ui->input->setText(index.data().toString().split(" ").last());
    ui->input->moveCursor(QTextCursor::End);
    ui->input->setFocus();
}
