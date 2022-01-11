#include "alphastim.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AlphaStim w;
    w.show();
    return a.exec();
}
