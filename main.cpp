#include <QApplication>

#include "LMainWidget.h"

int main(int argc, char *argv[])
{
    QApplication* app = new QApplication(argc, argv);
    
    LMainWidget* mainWidget = LMainWidget::getInstance(app);
    mainWidget->show();

    return app->exec();
}
