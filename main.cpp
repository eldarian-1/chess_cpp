#include <QApplication>

#include "LMain.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication app(argc, argv);
    LMain& wgtMain = *LMain::getInstance();
    wgtMain.show();
    return app.exec();
}
