#ifndef EMPLOYEESLIST_H
#define EMPLOYEESLIST_H

#include <QtWidgets>
#include <QtSql>

class EmployeesList : public QWidget {
    Q_OBJECT

public:
    explicit EmployeesList(QSqlRelationalTableModel* rModel, QWidget *parent = 0);

private:
    QSqlRelationalTableModel* model;
    QTableView* qview;

    QString* getCurrentEmployeeId();

signals:
    void addrow();
    void edtrow(QString*);
    void delrow(QString*);

private slots:
    void rowAddSlot() { emit addrow(); }
    void rowEdtSlot() { emit edtrow(getCurrentEmployeeId()); }
    void rowDelSlot() { emit delrow(getCurrentEmployeeId()); }

public slots:
    void selectChanges();
};

#endif // EMPLOYEESLIST_H
