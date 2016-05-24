#include "washingedit.h"

WashingEdit::WashingEdit(QSqlDatabase *base, QString *employeeId, QWidget *parent) : QWidget(parent) {
    id = employeeId;
    dBase = base;

    stdModel = new QSqlTableModel(this, *base);
    stdModel->setTable("WASHING_STANDARTS");
    stdModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    stdModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    stdModel->setHeaderData(1, Qt::Horizontal, tr("EMP_ID"));
    stdModel->setHeaderData(2, Qt::Horizontal, tr("Пункт типовых норм"));
    stdModel->setHeaderData(3, Qt::Horizontal, tr("Вид смываюищих или обезжиривающих средств"));
    stdModel->setHeaderData(4, Qt::Horizontal, tr("Единица измерения"));
    stdModel->setHeaderData(5, Qt::Horizontal, tr("Количество на год"));
    stdModel->setHeaderData(6, Qt::Horizontal, tr("Количество на месяц"));

    wshModel = new QSqlTableModel(this, *base);
    wshModel->setTable("WASHING_EQUIPMENT");
    wshModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    wshModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
    wshModel->setHeaderData(1, Qt::Horizontal, tr("EMP_ID"));
    wshModel->setHeaderData(2, Qt::Horizontal, tr("Вид смывающих и/или обезжиривающих средств"));
    wshModel->setHeaderData(3, Qt::Horizontal, tr("Свидетельство о государственной сертификации, сертификат соответствия"));
    wshModel->setHeaderData(4, Qt::Horizontal, tr("Дата выдачи"));
    wshModel->setHeaderData(5, Qt::Horizontal, tr("Количество"));
    wshModel->setHeaderData(6, Qt::Horizontal, tr("Способ выдачи"));
    wshModel->setHeaderData(7, Qt::Horizontal, tr("Дата следующей выдачи"));

    stdTable = new QTableView(this);
    stdTable->setEditTriggers(QAbstractItemView::CurrentChanged);
    stdTable->setModel(stdModel);
    stdTable->resizeColumnsToContents();
    stdTable->hideColumn(0);
    stdTable->hideColumn(1);

    wshTable = new QTableView(this);
    wshTable->setEditTriggers(QAbstractItemView::CurrentChanged);
    wshTable->setModel(wshModel);
    wshTable->resizeColumnsToContents();
    wshTable->hideColumn(0);
    wshTable->hideColumn(1);

    setModelMode();

    commit = new QPushButton("Сохранить", this);
    revert = new QPushButton("Отмена", this);

    connect(commit, SIGNAL(clicked(bool)), SLOT(commitChanges()));
    connect(revert, SIGNAL(clicked(bool)), SLOT(revertChanges()));

    stdAddBtn = new QPushButton("Добавить", this);
    stdDelBtn = new QPushButton("Удалить", this);
    wshAddBtn = new QPushButton("Добавить", this);
    wshDelBtn = new QPushButton("Удалить", this);

    connect(stdAddBtn, SIGNAL(clicked(bool)), SLOT(addStdRowSlot()));
    connect(stdDelBtn, SIGNAL(clicked(bool)), SLOT(delStdRowSlot()));
    connect(wshAddBtn, SIGNAL(clicked(bool)), SLOT(addWshRowSlot()));
    connect(wshDelBtn, SIGNAL(clicked(bool)), SLOT(delWshRowSlot()));

    QVBoxLayout* mlayout = new QVBoxLayout(this);
    QHBoxLayout* emplayout = new QHBoxLayout(this);
    QVBoxLayout* empbuttons = new QVBoxLayout(this);
    QHBoxLayout* stdlayout = new QHBoxLayout(this);
    QVBoxLayout* stdbuttons = new QVBoxLayout(this);
    QHBoxLayout* wshlayout = new QHBoxLayout(this);
    QVBoxLayout* wshbuttons = new QVBoxLayout(this);

    empbuttons->addWidget(commit);
    empbuttons->addWidget(revert);
    emplayout->addLayout(empbuttons);

    stdbuttons->addWidget(stdAddBtn);
    stdbuttons->addWidget(stdDelBtn);
    stdlayout->addWidget(stdTable);
    stdlayout->addLayout(stdbuttons);

    wshbuttons->addWidget(wshAddBtn);
    wshbuttons->addWidget(wshDelBtn);
    wshlayout->addWidget(wshTable);
    wshlayout->addLayout(wshbuttons);

    mlayout->addLayout(stdlayout);
    mlayout->addLayout(wshlayout);
    mlayout->addLayout(emplayout);
    setLayout(mlayout);
}

void WashingEdit::setModelMode() {
    stdModel->setFilter(QString("EMPLOYEE_ID = '%1'").arg(*id));
    wshModel->setFilter(QString("EMPLOYEE_ID = '%1'").arg(*id));
    stdModel->select();
    wshModel->select();

    if (stdModel->rowCount() == 0)
        addStdRowSlot();
    if (wshModel->rowCount() == 0)
        addWshRowSlot();
}

void WashingEdit::addStdRowSlot() {
    stdModel->insertRows(stdModel->rowCount(), 1);
    QVariant qVariantId(*id);
    qDebug() << qVariantId;
    stdModel->setData(stdModel->index(stdModel->rowCount() - 1, 1), qVariantId);
}

void WashingEdit::delStdRowSlot() {
    if (!stdTable->selectionModel()->selectedRows().isEmpty()) {
        stdModel->removeRow(stdTable->currentIndex().row());
    }
}

void WashingEdit::addWshRowSlot() {
    wshModel->insertRows(wshModel->rowCount(), 1);
    QVariant qVariantId(*id);
    qDebug() << qVariantId;
    wshModel->setData(wshModel->index(wshModel->rowCount() - 1, 1), qVariantId);
}

void WashingEdit::delWshRowSlot() {
    if (!wshTable->selectionModel()->selectedRows().isEmpty()) {
        wshModel->removeRow(wshTable->currentIndex().row());
    }
}

void WashingEdit::commitChanges() {
    if (!stdModel->submitAll()) {
        qDebug() << "Standarts insertion fail!\n" << dBase->lastError();
    }
    if (!wshModel->submitAll()) {
        qDebug() << "Equipment insertion fail!\n" << dBase->lastError();
    }
    emit changesCommited();
}

void WashingEdit::revertChanges() { }
