#ifndef EMPLOYEESREPORT_H
#define EMPLOYEESREPORT_H

#include <QtWidgets>
#include <QtSql>

class EquipmentReport : public QWidget {
    Q_OBJECT

public:
    explicit EquipmentReport(QSqlDatabase dbase, QWidget *parent = 0);

private:
    QSqlDatabase base;
    QSqlQueryModel *qmodel;
    QTableView *view;
};

#endif // EMPLOYEESREPORT_H
