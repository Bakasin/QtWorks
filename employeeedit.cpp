#include "employeeedit.h"

EmployeeEdit::EmployeeEdit(QSqlDatabase* base, QString* employeeId, QWidget *parent) : QWidget(parent) {
    id = employeeId;
    dBase = base;
    empModel = new QSqlTableModel(this, *base);
    stdModel = new QSqlTableModel(this, *base);
    eqpModel = new QSqlTableModel(this, *base);
    empModel->setTable("EMPLOYEE");
    stdModel->setTable("STANDARTS");
    eqpModel->setTable("EQUIPMENT");
    empModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    stdModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    eqpModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    empTable = new QTableView(this);
    stdTable = new QTableView(this);
    eqpTable = new QTableView(this);
    empTable->setEditTriggers(QAbstractItemView::DoubleClicked);
    stdTable->setEditTriggers(QAbstractItemView::DoubleClicked);
    eqpTable->setEditTriggers(QAbstractItemView::DoubleClicked);
    empTable->setModel(empModel);
    stdTable->setModel(stdModel);
    eqpTable->setModel(eqpModel);

    setModelMode();

    commit = new QPushButton("Сохранить", this);
    revert = new QPushButton("Отмена", this);

    connect(commit, SIGNAL(clicked(bool)), SLOT(commitChanges()));
    connect(revert, SIGNAL(clicked(bool)), SLOT(revertChanges()));

    stdAddBtn = new QPushButton("Добавить", this);
    stdDelBtn = new QPushButton("Удалить", this);
    eqpAddBtn = new QPushButton("Добавить", this);
    eqpDelBtn = new QPushButton("Удалить", this);

    connect(stdAddBtn, SIGNAL(clicked(bool)), SLOT(addStdRowSlot()));
    connect(stdDelBtn, SIGNAL(clicked(bool)), SLOT(delStdRowSlot()));
    connect(eqpAddBtn, SIGNAL(clicked(bool)), SLOT(addEqpRowSlot()));
    connect(eqpDelBtn, SIGNAL(clicked(bool)), SLOT(delEqpRowSlot()));

    QVBoxLayout* mlayout = new QVBoxLayout(this);
    QHBoxLayout* emplayout = new QHBoxLayout(this);
    QVBoxLayout* empbuttons = new QVBoxLayout(this);
    QHBoxLayout* stdlayout = new QHBoxLayout(this);
    QVBoxLayout* stdbuttons = new QVBoxLayout(this);
    QHBoxLayout* eqplayout = new QHBoxLayout(this);
    QVBoxLayout* eqpbuttons = new QVBoxLayout(this);

    empbuttons->addWidget(commit);
    empbuttons->addWidget(revert);
    emplayout->addWidget(empTable);
    emplayout->addLayout(empbuttons);

    stdbuttons->addWidget(stdAddBtn);
    stdbuttons->addWidget(stdDelBtn);
    stdlayout->addWidget(stdTable);
    stdlayout->addLayout(stdbuttons);

    eqpbuttons->addWidget(eqpAddBtn);
    eqpbuttons->addWidget(eqpDelBtn);
    eqplayout->addWidget(eqpTable);
    eqplayout->addLayout(eqpbuttons);

    mlayout->addLayout(emplayout);
    mlayout->addLayout(stdlayout);
    mlayout->addLayout(eqplayout);
    setLayout(mlayout);
}

void EmployeeEdit::setModelMode() {
    if (*id != "") {
        empModel->setFilter(QString("ID = '%1'").arg(*id));
        stdModel->setFilter(QString("EMPLOYEE_ID = '%1'").arg(*id));
        eqpModel->setFilter(QString("EMPLOYEE_ID = '%1'").arg(*id));
        empModel->select();
        stdModel->select();
        eqpModel->select();
    } else {
        addEmpRowSlot();
        addStdRowSlot();
        addEqpRowSlot();
    }
}

void EmployeeEdit::addEmpRowSlot() {
    empModel->insertRows(empModel->rowCount(), 1);
    for (int i = 0; i < empModel->columnCount(); i++) {
        empModel->setData(empModel->index(0, i), "");
    }
}

void EmployeeEdit::addStdRowSlot() {
    stdModel->insertRows(stdModel->rowCount(), 1);
    for (int i = 0; i < stdModel->columnCount(); i++) {
        stdModel->setData(stdModel->index(0, i), "");
    }
}

void EmployeeEdit::delStdRowSlot() {
    if (!stdTable->selectionModel()->selectedRows().isEmpty()) {
        stdModel->removeRow(stdTable->currentIndex().row());
    }
}

void EmployeeEdit::addEqpRowSlot() {
    eqpModel->insertRows(eqpModel->rowCount(), 1);
    for (int i = 0; i < eqpModel->columnCount(); i++) {
        eqpModel->setData(eqpModel->index(0, i), "");
    }
}

void EmployeeEdit::delEqpRowSlot() {
    if (!eqpTable->selectionModel()->selectedRows().isEmpty()) {
        eqpModel->removeRow(eqpTable->currentIndex().row());
    }
}

void EmployeeEdit::commitChanges() {
    if (!empModel->submitAll()) {
        qDebug() << "Employee insertion fail!\n" << dBase->lastError();
    }
    if (!stdModel->submitAll()) {
        qDebug() << "Standarts insertion fail!\n" << dBase->lastError();
    }
    if (!eqpModel->submitAll()) {
        qDebug() << "Equipment insertion fail!\n" << dBase->lastError();
    }
    emit changesCommited();
}

void EmployeeEdit::revertChanges() {

}
