#include "calculator.h"

calculator::calculator(QWidget *parent)
    : QWidget(parent)
{
    m_display_down = new QLineEdit;
    m_display_up = new QLabel;
    QGridLayout* mainLayout = new QGridLayout;

    m_display_down->setAlignment(Qt::AlignRight);
    m_display_up->setAlignment(Qt::AlignRight);
    m_display_down->setReadOnly(true);
    QFont font = m_display_down->font();
    font.setPointSize(font.pointSize() + 12);
    m_display_down->setFont(font);
    font.setPointSize(font.pointSize() - 5);
    m_display_up->setFont(font);
    m_display_down->setText("0");

    //create buttons
    for(int i=0; i<10;++i)
        m_digit_button[i] = create_button(QString::number(i), SLOT(digit_clicked()));

    Button* clear_all       = create_button("CA",              SLOT(clear_all_clicked()));
    Button* clear           = create_button("C",               SLOT(clear_clicked()));
    Button* backspase       = create_button(m_backspase,       SLOT(backspase_clicked()));
    memory_clear            = create_button("MC",              SLOT(memory_clear_clicked()));
    memory_read             = create_button("MR",              SLOT(memory_read_clicked()));
    memory_add              = create_button("M+",              SLOT(memory_add_clicked()));
    memory_sub              = create_button("M-",              SLOT(memory_sub_clicked()));
    Button* change_sing     = create_button(m_change_sing,     SLOT(change_sing_clicked()));
    Button* point           = create_button(".",               SLOT(point_clicked()));
    Button* subtraction     = create_button(m_subtraction,     SLOT(binary_operation_clicked()));
    Button* addition        = create_button(m_addition,        SLOT(binary_operation_clicked()));
    Button* multiplication  = create_button(m_multiplication,  SLOT(binary_operation_clicked()));
    Button* division        = create_button(m_division,        SLOT(binary_operation_clicked()));
    Button* division_by_one = create_button(m_division_by_one, SLOT(unary_operation_clicked()));
    Button* equal           = create_button("=",               SLOT(equal_clicked()));
    Button* square_root     = create_button(m_square_root,     SLOT(unary_operation_clicked()));
    Button* squaring        = create_button(m_squaring,        SLOT(unary_operation_clicked()));


    equal->setStyleSheet("QToolButton{background:#A84B74;}");

    //set elements on widget
    mainLayout->addWidget(m_display_up,   0,0,1,6);
    mainLayout->addWidget(m_display_down, 1,0,1,6);
    mainLayout->addWidget(clear_all,      2,0,1,2);
    mainLayout->addWidget(clear,          2,2,1,2);
    mainLayout->addWidget(backspase,      2,4,1,2);
    mainLayout->addWidget(memory_clear,   3,0);
    mainLayout->addWidget(memory_read,    4,0);
    mainLayout->addWidget(memory_add,     5,0);
    mainLayout->addWidget(memory_sub,     6,0);

    for(int i=1; i<10; ++i)
    {
        int row = ((9-i)/3)+3;
        int col = ((i-1)%3)+1;
        mainLayout->addWidget(m_digit_button[i], row, col);
    }
    mainLayout->addWidget(change_sing,      6,1,1,1);
    mainLayout->addWidget(m_digit_button[0],6,2,1,1);
    mainLayout->addWidget(point,            6,3,1,1);
    mainLayout->addWidget(subtraction,      6,4,1,1);
    mainLayout->addWidget(equal,            6,5,1,1);
    mainLayout->addWidget(addition,         5,4,1,1);
    mainLayout->addWidget(multiplication,   4,4,1,1);
    mainLayout->addWidget(division,         3,4,1,1);
    mainLayout->addWidget(division_by_one,  3,5,1,1);
    mainLayout->addWidget(squaring,         4,5,1,1);
    mainLayout->addWidget(square_root,      5,5,1,1);
    setLayout(mainLayout);

    memory_clear->setEnabled(false);
    memory_sub->setEnabled(false);
    memory_read->setEnabled(false);

}

calculator::~calculator() {}

void calculator::unary_operation_clicked()
{
    Button* btn = (Button*)sender();
    QString operation = btn->text();

    if(m_display_down->text() == "")
        return;

    double operand = m_display_down->text().toDouble();
    if(operation == m_squaring)
    {
        operand = std::pow(operand, 2.0);
    }
    else if(operation == m_square_root)
    {
        if(operand < 0.0)
        {
            invalid_operation();
            return;
        }
        operand = std::sqrt(operand);
    }
    else if(operation == m_division_by_one)
    {
        if(operand == 0.0)
        {
            invalid_operation();
            return;
        }
        operand = 1 / operand;
    }

    m_display_down->setText(QString::number(operand));
    m_display_up->setText(m_display_up->text() + m_display_down->text());
    m_display_down->clear();
}

void calculator::binary_operation_clicked()
{
    Button* btn = (Button*)sender();
    QString operation = btn->text();

    if(m_display_up->text() != "" && m_display_up->text().back() == "=")
    {
        m_display_up->setText(m_display_down->text() + operation);
        m_display_down->clear();
    }

    if(m_display_down->text() == "" && m_display_up->text() == "")
        return;
    if(m_display_down->text() == "" && m_display_up->text() != "")
    {
        m_display_up->setText(m_display_up->text().chopped(1) + operation);
        return;
    }

    m_display_up->setText(m_display_up->text() + m_display_down->text() + operation);
    m_display_down->clear();
}

void calculator::digit_clicked()
{
    Button* btn = (Button*)sender();
    unsigned digit = btn->text().toUInt();

    if(m_display_down->text() == "0")
        m_display_down->clear();
    m_display_down->setText(m_display_down->text() + QString::number(digit));
}

void calculator::clear_all_clicked()
{
    m_display_down->clear();
    m_display_up->clear();
    m_display_down->setText("0");
}

void calculator::clear_clicked()
{
    m_display_down->clear();
}

void calculator::backspase_clicked()
{
    QString text = m_display_down->text();

    if(!text.isEmpty())
        text.chop(1);
    m_display_down->setText(text);
}

void calculator::memory_clear_clicked()
{
    memory = 0.0;
    memory_clear->setEnabled(false);
    memory_sub->setEnabled(false);
    memory_read->setEnabled(false);
}

void calculator::memory_read_clicked()
{
    m_display_down->setText(QString::number(memory));
}

void calculator::memory_add_clicked()
{
    memory_clear->setEnabled(true);
    memory_sub->setEnabled(true);
    memory_read->setEnabled(true);
    memory += m_display_down->text().toDouble();
}

void calculator::memory_sub_clicked()
{
    memory -= m_display_down->text().toDouble();
}

void calculator::change_sing_clicked()
{
    QString text = m_display_down->text();
    double value = text.toDouble();

    if(value>0.0)
        text.prepend('-');
    else if(value<0.0)
        text.remove(0,1);
    m_display_down->setText(text);
}

void calculator::point_clicked()
{
    QString text = m_display_down->text();

    if(!text.contains('.'))
        text.append('.');
    m_display_down->setText(text);
}

void calculator::equal_clicked()
{
    if(m_display_down->text() != "")
    {
        m_display_up->setText(m_display_up->text() + m_display_down->text() + "=");
        m_display_down->clear();
    }
    RPN();
    m_display_down->setText(QString::number(m_operands.top()));
    m_operands.pop();
}

void calculator::RPN()
{
    int index_first = 0;

    QString text = m_display_up->text().sliced(0 ,m_display_up->text().length()-1);

    for(int i = 0; i < text.length(); ++i)
    {
        if(text[i].isLetterOrNumber() || text[i] == m_subtraction || text[i] == ".")
        {
            if(text[i] == m_subtraction)
            {
                if(i != 0 && text[i-1].isLetterOrNumber())
                {
                    m_operands.push(text.sliced(index_first, (i- index_first)).toDouble());
                    index_first = i;
                    m_operations.push(m_addition);
                }
                else if(text[i-1] == m_subtraction)
                {
                    index_first = i + 1;
                }
            }

            continue;
        }

        m_operands.push(text.sliced(index_first, (i- index_first)).toDouble());

        if(!m_operations.empty() && (m_operations.top() == m_division || m_operations.top() == m_multiplication))
        {
            double current_result = m_operands.top();
            m_operands.pop();
            if(m_operations.top() == m_division)
            {
                if(current_result == 0.0)
                {
                    invalid_operation();
                    return;
                }
                m_operations.pop();
                current_result = m_operands.top() / current_result;
                // if(m_operations.top() == m_subtraction)
                // {
                //     current_result = - (m_operands.top() / current_result);
                //     m_operations.pop();
                //     m_operations.push(m_addition);
                // }
                // else
                //     current_result = m_operands.top() / current_result;
            }
            else if(m_operations.top() == m_multiplication)
            {
                m_operations.pop();
                current_result = m_operands.top() * current_result;
                // if(m_operations.top() == m_subtraction)
                // {
                //     current_result = - (m_operands.top() * current_result);
                //     m_operations.pop();
                //     m_operations.push(m_addition);
                // }
                // else
                //     current_result = m_operands.top() * current_result;
            }
            m_operands.pop();
            m_operands.push(current_result);
        }
        m_operations.push(text[i]);
        index_first = i + 1;
    }
    m_operands.push(text.slice(index_first).toDouble());

    double result = m_operands.top();
    m_operands.pop();
    while(!m_operands.empty())
    {
        if(m_operations.top() == m_multiplication)
        {
            result = m_operands.top() * result;
            m_operands.pop();
            m_operations.pop();
        }
        else if(m_operations.top() == m_division)
        {
            if(result == 0.0)
            {
                invalid_operation();
                return;
            }
            result = m_operands.top() / result;
            m_operands.pop();
            m_operations.pop();
        }
        else if(m_operations.top() == m_addition)
        {
            result = m_operands.top() + result;
            m_operands.pop();
            m_operations.pop();
        }
    }
    m_operands.push(result);
}

void calculator::invalid_operation()
{
    m_display_down->setText("ERROR");
    m_display_up->setText("Is invalid value");
}

Button* calculator::create_button(const QString& text, const char* m_slot)
{
    Button* btn = new Button(text);
    connect(btn, SIGNAL(clicked()), this, m_slot);
    return btn;
}
