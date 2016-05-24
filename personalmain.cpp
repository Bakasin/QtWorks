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
    connect(eList, SIGNAL(edtEqpRow(QString*)), SLOT(edtEqpRow(QString*)));
    connect(eList, SIGNAL(edtWshRow(QString*)), SLOT(edtWshRow(QString*)));

    qtab = new QTabWidget(this);
    qtab->setTabsClosable(true);
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

void PersonalMain::edtEqpRow(QString* str) {
    EmployeeEdit* edit = new EmployeeEdit(&base, str, qtab);
    qtab->addTab(new EmployeeEdit(&base, str, qtab), "Карточка СИЗ");
    connect(edit, SIGNAL(changesCommited()), eList, SLOT(selectChanges()));
}

void PersonalMain::edtWshRow(QString* str) {
    WashingEdit* edit = new WashingEdit(&base, str, qtab);
    qtab->addTab(new WashingEdit(&base, str, qtab), "Карточка МС");
    connect(edit, SIGNAL(changesCommited()), eList, SLOT(selectChanges()));
}
