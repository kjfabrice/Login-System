#ifndef INSTRUCTORLOGIN_H
#define INSTRUCTORLOGIN_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "mainwindow.h"
#include "instructor.h"
namespace Ui {
class instructorLogin;
}

class instructorLogin : public QDialog
{
    Q_OBJECT
public:
    QSqlDatabase mydb;

    //***********close connection with db**************//
    void connClose() {
        mydb.close();
        mydb.removeDatabase(QSqlDatabase::defaultConnection);
    }
    //***********open connection with db**************//
    bool connOpen() {
        mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("unidb.db");
        if(!mydb.open()) {
            qDebug() <<("Failed to open database");
            return false;
        }

        else {
            qDebug() <<("Connected to university database");
            return true;
        }

    }

public:
    explicit instructorLogin(QWidget *parent = nullptr);
    ~instructorLogin();

private slots:
    void on_homeButton_clicked();

    void on_signInButton_clicked();

private:
    Ui::instructorLogin *ui;
};

#endif // INSTRUCTORLOGIN_H
