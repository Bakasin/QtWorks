#include "washingreport.h"

WashingReport::WashingReport(QSqlDatabase dbase, QWidget *parent) : QWidget(parent), base(dbase) {
    qmodel = new QSqlQueryModel(this);
    qmodel->setQuery("SELECT EMPLOYEE.LASTNAME, EMPLOYEE.FIRSTNAME, EMPLOYEE.MIDDLENAME,"
                     " EMPLOYEE.SUBDIVISION, WASHING_EQUIPMENT.NAME, WASHING_EQUIPMENT.NEXT_ISSUING_DATE"
                     " FROM EMPLOYEE JOIN WASHING_EQUIPMENT ON WASHING_EQUIPMENT.EMPLOYEE_ID = EMPLOYEE.ID"
                     " WHERE WASHING_EQUIPMENT.NEXT_ISSUING_DATE < CURRENT_DATE", base);
    view = new QTableView(this);
    view->setModel(qmodel);

    QVBoxLayout *qvblayout = new QVBoxLayout(this);
    qvblayout->addWidget(new QLabel("Отчет", this));
    qvblayout->addWidget(view);
    setLayout(qvblayout);
    show();
}
