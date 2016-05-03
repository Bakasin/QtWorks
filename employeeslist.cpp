#include "employeeslist.h"

EmployeesList::EmployeesList(QSqlRelationalTableModel* rModel, QWidget *parent) : QWidget(parent) {
    model = rModel;
    qview = new QTableView(this);
    QLabel* qlbl = new QLabel(tr("Список"), this);
    qview->setModel(model);
    qview->setSelectionBehavior(QAbstractItemView::SelectRows);

    QPushButton* addbtn = new QPushButton(tr("Добавить"), this);
    QPushButton* edtbtn = new QPushButton(tr("Редактировать"), this);
    QPushButton* delbtn = new QPushButton(tr("Удалить"), this);

    connect(addbtn, SIGNAL(clicked(bool)), SLOT(rowAddSlot()));
    connect(edtbtn, SIGNAL(clicked(bool)), SLOT(rowEdtSlot()));
    connect(delbtn, SIGNAL(clicked(bool)), SLOT(rowDelSlot()));

    QVBoxLayout* qvbxmain = new QVBoxLayout(this);
    QVBoxLayout* qvbx = new QVBoxLayout(this);
    QHBoxLayout* qhbx = new QHBoxLayout(this);

    qvbx->addWidget(addbtn);
    qvbx->addWidget(edtbtn);
    qvbx->addWidget(delbtn);

    qhbx->addWidget(qview);
    qhbx->addLayout(qvbx);

    qvbxmain->addWidget(qlbl);
    qvbxmain->addLayout(qhbx);
    setLayout(qvbxmain);
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
