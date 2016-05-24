#ifndef EMPLOYEESLIST_H
#define EMPLOYEESLIST_H

#include <QtWidgets>
#include <QtSql>
#include "equipmentreport.h"
#include "washingreport.h"

class EmployeesList : public QWidget {
    Q_OBJECT

public:
    explicit EmployeesList(QSqlRelationalTableModel* rModel, QWidget *parent = 0);

private:
    QSqlRelationalTableModel* model;
    QTableView* qview;
    QPushButton* rowEdtbtn;

    QString* getCurrentEmployeeId();

signals:
    void edtEqpRow(QString*);
    void edtWshRow(QString*);
    void delrow(QString*);

private slots:
    void rowAddSlot();
    void rowEdtEqpSlot();
    void rowEdtWshSlot();
    void setRowEditableSlot();
    void rowDelSlot();
    void showEqpReport();
    void showWshReport();

public slots:
    void selectChanges();
};

#endif // EMPLOYEESLIST_H
