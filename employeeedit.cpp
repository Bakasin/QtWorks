#include "employeeedit.h"

EmployeeEdit::EmployeeEdit(QSqlDatabase* base, QString* employeeId, QWidget *parent) : QWidget(parent) {
    id = employeeId;
    dBase = base;

    stdModel = new QSqlTableModel(this, *base);
    stdModel->setTable("STANDARTS");
    stdModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    stdModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    stdModel->setHeaderData(1, Qt::Horizontal, tr("EMP_ID"));
    stdModel->setHeaderData(2, Qt::Horizontal, tr("Наименование СИЗ"));
    stdModel->setHeaderData(3, Qt::Horizontal, tr("Пункт типовых отраслевых норм"));
    stdModel->setHeaderData(4, Qt::Horizontal, tr("Единица измерения"));
    stdModel->setHeaderData(5, Qt::Horizontal, tr("Количество на год"));

    eqpModel = new QSqlTableModel(this, *base);
    eqpModel->setTable("EQUIPMENT");
    eqpModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    eqpModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    eqpModel->setHeaderData(1, Qt::Horizontal, tr("EMP_ID"));
    eqpModel->setHeaderData(2, Qt::Horizontal, tr("Наименование СИЗ"));
    eqpModel->setHeaderData(3, Qt::Horizontal, tr("ГОСТ, ОСТ, ТУ"));
    eqpModel->setHeaderData(4, Qt::Horizontal, tr("Дата"));
    eqpModel->setHeaderData(5, Qt::Horizontal, tr("Количество"));
    eqpModel->setHeaderData(6, Qt::Horizontal, tr("% износа"));
    eqpModel->setHeaderData(7, Qt::Horizontal, tr("Стоимость"));
    eqpModel->setHeaderData(8, Qt::Horizontal, tr("Дата"));
    eqpModel->setHeaderData(9, Qt::Horizontal, tr("Количество"));
    eqpModel->setHeaderData(10, Qt::Horizontal, tr("% износа"));
    eqpModel->setHeaderData(11, Qt::Horizontal, tr("Стоимость"));
    eqpModel->setHeaderData(12, Qt::Horizontal, tr("Срок"));

    stdTable = new QTableView(this);
    stdTable->setEditTriggers(QAbstractItemView::DoubleClicked);
    stdTable->setModel(stdModel);
    stdTable->hideColumn(0);
    stdTable->hideColumn(1);

    eqpTable = new QTableView(this);
    eqpTable->setEditTriggers(QAbstractItemView::DoubleClicked);
    eqpTable->setModel(eqpModel);
    eqpTable->hideColumn(0);
    eqpTable->hideColumn(1);


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
    emplayout->addLayout(empbuttons);

    stdbuttons->addWidget(stdAddBtn);
    stdbuttons->addWidget(stdDelBtn);
    stdlayout->addWidget(stdTable);
    stdlayout->addLayout(stdbuttons);

    eqpbuttons->addWidget(eqpAddBtn);
    eqpbuttons->addWidget(eqpDelBtn);
    eqplayout->addWidget(eqpTable);
    eqplayout->addLayout(eqpbuttons);

    mlayout->addLayout(stdlayout);
    mlayout->addLayout(eqplayout);
    mlayout->addLayout(emplayout);
    setLayout(mlayout);
}

void EmployeeEdit::setModelMode() {
    if (*id != "" && id != nullptr) {
        stdModel->setFilter(QString("EMPLOYEE_ID = '%1'").arg(*id));
        eqpModel->setFilter(QString("EMPLOYEE_ID = '%1'").arg(*id));
        stdModel->select();
        eqpModel->select();
    } else {
        addStdRowSlot();
        addEqpRowSlot();
    }
}

//void EmployeeEdit::addEmpRowSlot() {
//    empModel->insertRows(empModel->rowCount(), 1);
//    for (int i = 0; i < empModel->columnCount(); i++) {
//        empModel->setData(empModel->index(0, i), "");
//    }
//}

void EmployeeEdit::addStdRowSlot() {
    stdModel->insertRows(stdModel->rowCount(), 1);
    QVariant qVariantId(*id);
    if (!stdModel->setData(stdModel->index(stdModel->rowCount(), 1), qVariantId))
        qDebug() << "Failed insert new row for standarts table!";
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
    QVariant qVariantId(*id);
    if (!eqpModel->setData(eqpModel->index(eqpModel->rowCount(), 1), qVariantId))
        qDebug() << "Failed insert new row for eqipment table!";
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
//    if (!empModel->submitAll()) {
//        qDebug() << "Employee insertion fail!\n" << dBase->lastError();
//    }
    if (!stdModel->submitAll()) {
        qDebug() << "Standarts insertion fail!\n" << dBase->lastError();
    }
    if (!eqpModel->submitAll()) {
        qDebug() << "Equipment insertion fail!\n" << dBase->lastError();
    }
    emit changesCommited();
}

void EmployeeEdit::revertChanges() { }
