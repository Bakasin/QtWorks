#ifndef EMPLOYEEEDIT_H
#define EMPLOYEEEDIT_H

#include <QtWidgets>
#include <QtSql>

class EmployeeEdit : public QWidget {
    Q_OBJECT

public:
    explicit EmployeeEdit(QSqlDatabase* base, QString* employeeId, QWidget *parent = 0);

private:
    QString* id;
    QSqlDatabase* dBase;
    QSqlTableModel* stdModel;
    QSqlTableModel* eqpModel;
    QTableView* stdTable;
    QTableView* eqpTable;

    QPushButton* stdAddBtn;
    QPushButton* stdDelBtn;
    QPushButton* eqpAddBtn;
    QPushButton* eqpDelBtn;

    QPushButton* commit;
    QPushButton* revert;

    void setModelMode();

signals:
    void changesCommited();

private slots:
    void addStdRowSlot();
    void delStdRowSlot();

    void addEqpRowSlot();
    void delEqpRowSlot();

    void commitChanges();
    void revertChanges();

public slots:
};

#endif // EMPLOYEEEDIT_H
