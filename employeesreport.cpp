#include "employeesreport.h"

EmployeesReport::EmployeesReport(QSqlDatabase dbase, QWidget *parent) : QWidget(parent), base(dbase) {
    qmodel = new QSqlQueryModel(this);
    qmodel->setQuery("SELECT EMPLOYEE.LASTNAME, EMPLOYEE.FIRSTNAME, EMPLOYEE.MIDDLENAME, EQUIPMENT.EXPIRATION_DATE"
                     " FROM EMPLOYEE JOIN EQUIPMENT ON EQUIPMENT.EMPLOYEE_ID = EMPLOYEE.ID"
                     " WHERE EQUIPMENT.EXPIRATION_DATE < CURRENT_DATE", base);
    view = new QTableView(this);
    view->setModel(qmodel);

    QVBoxLayout *qvblayout = new QVBoxLayout(this);
    qvblayout->addWidget(new QLabel("Отчет", this));
    qvblayout->addWidget(view);
    setLayout(qvblayout);
    show();
}
