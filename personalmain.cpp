#include "personalmain.h"
/*
 * Class PersonalMain
 */
PersonalMain::PersonalMain(QApplication* qapp, QWidget *parent) : QMainWindow(parent) {
    qApplication = qapp;
    base.setDatabaseName("postgres");
    base.setUserName("postgres");
    base.setPassword("776688");
    base.setHostName("localhost");
    base.setPort(5432);
    checkDatabaseConnection(&base);

    QSqlRelationalTableModel* relModel = new QSqlRelationalTableModel(this, base);
    relModel->setTable("EMPLOYEE");
    relModel->select();

    eList = new EmployeesList(relModel, this);
    connect(eList, SIGNAL(addrow(QString*)), SLOT(addRow(QString*)));
    connect(eList, SIGNAL(edtrow(QString*)), SLOT(edtRow(QString*)));


    qtab = new QTabWidget(this);
    qtab->addTab(eList, tr("Список работников"));

    QVBoxLayout* qvbx = new QVBoxLayout(this);
    qvbx->addWidget(qtab);

    QWidget *widg = new QWidget(this);
    widg->setLayout(qvbx);
    setCentralWidget(widg);
}

void PersonalMain::checkDatabaseConnection(QSqlDatabase *base) {
    if (!base->open()) {
        fDialog = new FailedConnectionDialog(this);
        connect(fDialog, SIGNAL(accepted()), qApplication, SLOT(quit()));
        fDialog->show();
        qDebug() << base->lastError();
    }
}

void PersonalMain::addRow(QString* str) {
    EmployeeEdit* edit = new EmployeeEdit(&base, str, qtab);
    qtab->addTab(edit , "Новая запись");
    connect(edit, SIGNAL(changesCommited()), eList, SLOT(selectChanges()));
}

void PersonalMain::edtRow(QString* str) {
    EmployeeEdit* edit = new EmployeeEdit(&base, str, qtab);
    qtab->addTab(new EmployeeEdit(&base, str, qtab), "Редактирование записи");
    connect(edit, SIGNAL(changesCommited()), eList, SLOT(selectChanges()));
}
