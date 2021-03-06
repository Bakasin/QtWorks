#ifndef PERSONALMAIN_H
#define PERSONALMAIN_H

#include <QtWidgets>
#include <QtSql>
#include "failedconnectiondialog.h"
#include "employeeslist.h"
#include "employeeedit.h"
#include "washingedit.h"

class PersonalMain : public QMainWindow {
    Q_OBJECT

public:
    PersonalMain(QApplication* qapp, QWidget *parent = 0);

private:
    FailedConnectionDialog* fDialog;
    QApplication* qApplication;
    QTabWidget* qtab;
    QSqlDatabase* pdBase;
    EmployeesList* eList;
    QSqlDatabase base = QSqlDatabase::addDatabase("QPSQL");

    void setDatabaseConnection(QSqlDatabase base);
    void checkDatabaseConnection(QSqlDatabase* base);

private slots:
    void edtEqpRow(QString* str);
    void edtWshRow(QString* str);
};

#endif // PERSONALMAIN_H
