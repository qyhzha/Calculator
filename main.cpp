#include "Calculator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Calculator *w = Calculator::NewInstance();
    int ret = 0;

    if (w != NULL)
    {
        w->show();
        ret = a.exec();
    }

    delete w;

    return ret;
}
