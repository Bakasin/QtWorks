#include "personalmain.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    PersonalMain* personal = new PersonalMain(&a);
    personal->setWindowState(Qt::WindowMaximized);
    personal->show();
    return a.exec();
}
