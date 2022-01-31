#ifndef LOGINSTUDENT_H
#define LOGINSTUDENT_H

#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QMessageBox>
#include "student.h"
#include "mainwindow.h"

namespace Ui {
class LoginStudent;
}

class LoginStudent : public QDialog
{
    Q_OBJECT

public:
    explicit LoginStudent(QWidget *parent = nullptr);
    ~LoginStudent();
    QSqlDatabase uni_db;
    void connClose();
    bool connOpen();

private slots:
    void on_signInButton_clicked();

    void on_homeButton_clicked();

private:
    Ui::LoginStudent *ui;
};

#endif // LOGINSTUDENT_H
