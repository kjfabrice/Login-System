#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include <QMessageBox>
#include "instructorlogin.h"
namespace Ui {
class instructor;
}

class instructor : public QDialog
{
    Q_OBJECT

public:
    QString userID; //==> ID entered in login
public:
    explicit instructor(QWidget *parent = nullptr);
    ~instructor();

private slots:
    void on_aboutMeButton_clicked();

    void on_updateButton_clicked();

    void on_courseDetailsButton_clicked();

    void on_coursesComboBox_currentTextChanged(const QString &arg1);

    void on_yearComboBox_currentTextChanged(const QString &arg1);

    void on_fallButton_clicked();

    void on_springButton_clicked();

    void on_registerStudentsButton_clicked();

    void on_yearComboBox2_currentTextChanged(const QString &arg1);

    void on_coursesComboBox2_currentTextChanged(const QString &arg1);

    void on_semesterComboBox2_currentTextChanged(const QString &arg1);

    void on_studentIdComboBox_currentTextChanged(const QString &arg1);

    void on_registerButton_clicked();

    void on_logOutButton_clicked();

private:
    Ui::instructor *ui;
};

#endif // INSTRUCTOR_H
