#ifndef WASHINGEDIT_H
#define WASHINGEDIT_H

#include <QtWidgets>
#include <QtSql>

class WashingEdit : public QWidget {
    Q_OBJECT

public:
    explicit WashingEdit(QSqlDatabase* base, QString* employeeId, QWidget *parent = 0);

private:
    QString* id;
    QSqlDatabase* dBase;
    QSqlTableModel* stdModel;
    QSqlTableModel* wshModel;
    QTableView* stdTable;
    QTableView* wshTable;

    QPushButton* stdAddBtn;
    QPushButton* stdDelBtn;
    QPushButton* wshAddBtn;
    QPushButton* wshDelBtn;

    QPushButton* commit;
    QPushButton* revert;

    void setModelMode();

signals:
    void changesCommited();

private slots:
    void addStdRowSlot();
    void delStdRowSlot();

    void addWshRowSlot();
    void delWshRowSlot();

    void commitChanges();
    void revertChanges();
};

#endif // WASHINGEDIT_H
