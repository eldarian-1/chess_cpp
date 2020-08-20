#include <QApplication>

#include "LMainWidget.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication app(argc, argv);
    LMainWidget& mainWidget = *LMainWidget::getInstance();
    mainWidget.show();
    return app.exec();
}
