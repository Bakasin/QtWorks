#ifndef WASHINGREPORT_H
#define WASHINGREPORT_H

#include <QtWidgets>
#include <QtSql>

class WashingReport : public QWidget {
    Q_OBJECT

public:
    explicit WashingReport(QSqlDatabase dbase, QWidget *parent = 0);

private:
    QSqlDatabase base;
    QSqlQueryModel *qmodel;
    QTableView *view;
};

#endif // WASHINGREPORT_H
