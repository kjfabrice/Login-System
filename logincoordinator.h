#ifndef LOGINCOORDINATOR_H
#define LOGINCOORDINATOR_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include "student.h"
#include "mainwindow.h"
#include "coordinator.h"

namespace Ui {
class LoginCoordinator;
}

class LoginCoordinator : public QDialog
{
    Q_OBJECT

public:
    explicit LoginCoordinator(QWidget *parent = nullptr);
    ~LoginCoordinator();
    QSqlDatabase uni_db;
    void connClose();
    bool connOpen();

private slots:
    void on_homeButton_clicked();

    void on_signInButton_clicked();

private:
    Ui::LoginCoordinator *ui;
};

#endif // LOGINCOORDINATOR_H
