#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    calculator window;
    window.setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);
    window.resize(500,550);
    window.show();
    return app.exec();
}
