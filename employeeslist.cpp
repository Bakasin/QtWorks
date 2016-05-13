#include "employeeslist.h"

EmployeesList::EmployeesList(QSqlRelationalTableModel* rModel, QWidget *parent) : QWidget(parent) {
    model = rModel;
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Фамилия"));
    model->setHeaderData(2, Qt::Horizontal, tr("Отчество"));
    model->setHeaderData(3, Qt::Horizontal, tr("Имя"));
    model->setHeaderData(4, Qt::Horizontal, tr("Табельный номер"));
    model->setHeaderData(5, Qt::Horizontal, tr("Структурное подразделение"));
    model->setHeaderData(6, Qt::Horizontal, tr("Профессия"));
    model->setHeaderData(7, Qt::Horizontal, tr("Пол"));
    model->setHeaderData(8, Qt::Horizontal, tr("Рост"));
    model->setHeaderData(9, Qt::Horizontal, tr("Одежда"));
    model->setHeaderData(10, Qt::Horizontal, tr("Обувь"));
    model->setHeaderData(11, Qt::Horizontal, tr("Головной убор"));
    model->setHeaderData(12, Qt::Horizontal, tr("Противогаз"));
    model->setHeaderData(13, Qt::Horizontal, tr("Респиратор"));
    model->setHeaderData(14, Qt::Horizontal, tr("Рукавицы"));
    model->setHeaderData(15, Qt::Horizontal, tr("Перчатки"));

    qview = new QTableView(this);
    qview->setModel(model);
    qview->setUpdatesEnabled(true);
    qview->setEditTriggers(QAbstractItemView::CurrentChanged);
    qview->setSelectionBehavior(QAbstractItemView::SelectRows);
    qview->resizeColumnsToContents();
    qview->hideColumn(0);    

    QLabel* qlbl = new QLabel(tr("Список"), this);

    QPushButton* addbtn = new QPushButton(tr("Добавить"), this);
    QPushButton* edtbtn = new QPushButton(tr("Редактировать"), this);
    QPushButton* savebtn = new QPushButton(tr("Сохранить"), this);
    QPushButton* delbtn = new QPushButton(tr("Удалить"), this);

    connect(addbtn, SIGNAL(clicked(bool)), SLOT(rowAddSlot()));
    connect(edtbtn, SIGNAL(clicked(bool)), SLOT(rowEdtSlot()));
    connect(savebtn, SIGNAL(clicked(bool)), SLOT(rowSaveSlot()));
    connect(delbtn, SIGNAL(clicked(bool)), SLOT(rowDelSlot()));

    QVBoxLayout* qvbxmain = new QVBoxLayout(this);
    QVBoxLayout* qvbx = new QVBoxLayout(this);
    QHBoxLayout* qhbx = new QHBoxLayout(this);

    qvbx->addWidget(addbtn);
    qvbx->addWidget(edtbtn);
    qvbx->addWidget(savebtn);
    qvbx->addWidget(delbtn);

    qhbx->addWidget(qview);
    qhbx->addLayout(qvbx);

    qvbxmain->addWidget(qlbl);
    qvbxmain->addLayout(qhbx);
    setLayout(qvbxmain);
}

void EmployeesList::rowAddSlot() {
    model->insertRows(model->rowCount(), 1);
}

void EmployeesList::rowEdtSlot() {
    emit edtrow(getCurrentEmployeeId());
}

void EmployeesList::rowDelSlot() {
    if (!qview->selectionModel()->selectedRows().isEmpty()) {
        model->removeRow(qview->currentIndex().row());
    }
}

void EmployeesList::rowSaveSlot() {
    if (!model->submitAll()) {
        qDebug() << "Employee insertion fail!\n" << model->database().lastError();
    }
}

QString* EmployeesList::getCurrentEmployeeId() {
    int row = qview->selectionModel()->currentIndex().row();
    QString* id = new QString(qview->model()->data(qview->model()->index(row, 0)).toString());
    return id;
}

void EmployeesList::selectChanges() {
    if (!model->select()) {
        qDebug() << model->database().lastError();
    }
}
