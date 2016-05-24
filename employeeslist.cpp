#include "employeeslist.h"

EmployeesList::EmployeesList(QSqlRelationalTableModel* rModel, QWidget *parent) : QWidget(parent) {
    model = rModel;
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Фамилия"));
    model->setHeaderData(2, Qt::Horizontal, tr("Имя"));
    model->setHeaderData(3, Qt::Horizontal, tr("Отчество"));
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
    qview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    qview->setSelectionBehavior(QAbstractItemView::SelectRows);
    qview->resizeColumnsToContents();
    qview->hideColumn(0);    

    QLabel* qlbl = new QLabel(tr("Список"), this);

    QPushButton* addbtn = new QPushButton(tr("Добавить"), this);
    QPushButton* edtEqpBtn = new QPushButton(tr("Карточка СИЗ"), this);
    QPushButton* edtWshBtn = new QPushButton(tr("Карточка МС"), this);
    QPushButton* delbtn = new QPushButton(tr("Удалить"), this);
    QPushButton* eqpReportbtn = new QPushButton(tr("Отчет СИЗ"), this);
    QPushButton* wshReportbtn = new QPushButton(tr("Отчет МС"), this);

    rowEdtbtn = new QPushButton(tr("Редактировать"), this);
    rowEdtbtn->setCheckable(true);
    connect(rowEdtbtn, SIGNAL(clicked(bool)), SLOT(setRowEditableSlot()));

    connect(addbtn, SIGNAL(clicked(bool)), SLOT(rowAddSlot()));
    connect(edtEqpBtn, SIGNAL(clicked(bool)), SLOT(rowEdtEqpSlot()));
    connect(edtWshBtn, SIGNAL(clicked(bool)), SLOT(rowEdtWshSlot()));
    connect(delbtn, SIGNAL(clicked(bool)), SLOT(rowDelSlot()));
    connect(eqpReportbtn, SIGNAL(clicked(bool)), SLOT(showEqpReport()));
    connect(wshReportbtn, SIGNAL(clicked(bool)), SLOT(showWshReport()));

    QVBoxLayout* qvbxmain = new QVBoxLayout(this);
    QVBoxLayout* qvbx = new QVBoxLayout(this);
    QHBoxLayout* qhbx = new QHBoxLayout(this);

    qvbx->addWidget(addbtn);
    qvbx->addWidget(rowEdtbtn);
    qvbx->addWidget(delbtn);
    qvbx->addWidget(edtEqpBtn);
    qvbx->addWidget(edtWshBtn);
    qvbx->addWidget(eqpReportbtn);
    qvbx->addWidget(wshReportbtn);

    qhbx->addWidget(qview);
    qhbx->addLayout(qvbx);

    qvbxmain->addWidget(qlbl);
    qvbxmain->addLayout(qhbx);
    setLayout(qvbxmain);
}

void EmployeesList::rowAddSlot() {
    model->insertRows(model->rowCount(), 1);
}

void EmployeesList::rowEdtEqpSlot() {
    emit edtEqpRow(getCurrentEmployeeId());
}

void EmployeesList::rowEdtWshSlot() {
    emit edtWshRow(getCurrentEmployeeId());
}

void EmployeesList::rowDelSlot() {
    if (!qview->selectionModel()->selectedRows().isEmpty()) {
        model->removeRow(qview->currentIndex().row());
    }
}

void EmployeesList::setRowEditableSlot() {
    if (rowEdtbtn->isChecked()) {
        qview->setEditTriggers(QAbstractItemView::CurrentChanged);
    } else {
        qview->setEditTriggers(QAbstractItemView::NoEditTriggers);
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

void EmployeesList::showEqpReport() {
    new EquipmentReport(model->database());
}

void EmployeesList::showWshReport() {
    new WashingReport(model->database());
}
