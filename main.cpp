#include <QApplication>

#include "LMain.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication app(argc, argv);
    LMain wgtMain;
    wgtMain.show();
    return app.exec();
}
