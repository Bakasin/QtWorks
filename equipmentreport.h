#ifndef EMPLOYEESREPORT_H
#define EMPLOYEESREPORT_H

#include <QtWidgets>
#include <QtSql>

class EmployeesReport : public QWidget {
    Q_OBJECT

public:
    explicit EmployeesReport(QSqlDatabase dbase, QWidget *parent = 0);

private:
    QSqlDatabase base;
    QSqlQueryModel *qmodel;
    QTableView *view;

public slots:
};

#endif // EMPLOYEESREPORT_H
