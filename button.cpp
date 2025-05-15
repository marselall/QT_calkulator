#include "button.h"

Button::Button(const QString& text, QWidget* parent)
    : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    QFont font = this->font();
    font.setPointSize(font.pointSize() + 10);
    setFont(font);
    setText(text);
}
