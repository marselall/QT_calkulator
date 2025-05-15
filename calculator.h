#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QFont>
#include <QtMath>
#include <stack>
#include "button.h"

class calculator : public QWidget
{
    Q_OBJECT

public:
    calculator(QWidget *parent = nullptr);
    ~calculator();

private slots:
    void unary_operation_clicked();
    void binary_operation_clicked();
    void digit_clicked();
    void clear_all_clicked();
    void clear_clicked();
    void backspase_clicked();
    void memory_clear_clicked();
    void memory_read_clicked();
    void memory_add_clicked();
    void memory_sub_clicked();
    void change_sing_clicked();
    void point_clicked();
    void equal_clicked();


private:
    double memory = 0.0;
    void RPN();
    std::stack<QString> m_operations;  //stack of operations for binary operations
    std::stack<double> m_operands;     //stack of doubles for binary operations
    void invalid_operation();
    Button* create_button(const QString& text, const char* m_slot);
    //fields
    QLineEdit* m_display_down;
    QLabel* m_display_up;
    //buttons
    Button* m_digit_button[10];        //arrey buttons of number 0-9
    Button* memory_clear;
    Button* memory_read;
    Button* memory_add;
    Button* memory_sub;

    QString m_addition = "+";
    QString m_subtraction = "-";
    QString m_division = QChar(0x000000F7);
    QString m_multiplication = QChar(0x000000D7);

    QString m_square_root = QChar(0x221A);
    QString m_squaring = 'x' + QChar(0x000000B2);
    QString m_division_by_one = "1/x";
    QString m_change_sing = QChar(0x000000B1);
    QString m_backspase = "Backspase";
};
#endif // CALCULATOR_H
