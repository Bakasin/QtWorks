#include "employeeslist.h"

EmployeesList::EmployeesList(QSqlRelationalTableModel* rModel, QWidget *parent) : QWidget(parent) {
    model = rModel;

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
    QLabel* qlbl = new QLabel(tr("Список"), this);
    qview->setModel(model);
    qview->setSelectionBehavior(QAbstractItemView::SelectRows);
    qview->hideColumn(0);

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
