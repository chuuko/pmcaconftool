#include "pmcaconf_mainwin.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pmcaconf_mainwin w;
    w.show();

    return a.exec();
}
