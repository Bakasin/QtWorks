#include "failedconnectiondialog.h"

FailedConnectionDialog::FailedConnectionDialog(QWidget* pwgt)
    : QDialog(pwgt) {
    qlbl = new QLabel(tr("Ошибка соединения с базой данных, приложение будет завершено"), this);
    qpbtn = new QPushButton(tr("&Ok"), this);
    connect(qpbtn, SIGNAL(clicked(bool)), SLOT(accept()));

    QVBoxLayout* qvbl = new QVBoxLayout(this);
    qvbl->addWidget(qlbl);
    qvbl->addWidget(qpbtn);
    setLayout(qvbl);
    setModal(true);
}
