#include <QApplication>

#include "LMainWidget.h"

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication* app = new QApplication(argc, argv);
    
    LMainWidget* mainWidget = LMainWidget::getInstance(app);
    mainWidget->show();

    return app->exec();
}
