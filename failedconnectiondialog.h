#ifndef FAILEDCONNECTIONDIALOG_H
#define FAILEDCONNECTIONDIALOG_H

#include <QtWidgets>

class FailedConnectionDialog : public QDialog {
    Q_OBJECT

public:
    FailedConnectionDialog(QWidget* pwgt = 0);

private:
    QLabel* qlbl;
    QPushButton *qpbtn;
};

#endif // FAILEDCONNECTIONDIALOG_H
