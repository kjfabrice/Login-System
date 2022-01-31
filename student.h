#ifndef STUDENT_H
#define STUDENT_H

#include <QDialog>
#include "loginstudent.h"

namespace Ui {
class Student;
}

class Student : public QDialog
{
    Q_OBJECT

public:
    explicit Student(QWidget *parent = nullptr);
    ~Student();
    QString user;

private slots:
    void on_aboutMeButton_clicked();

    void on_updateButton_clicked();

    void on_coursesButton_clicked();

    void on_yearComboBox_currentTextChanged(const QString &arg1);

    void on_fallButton_clicked();

    void on_springButton_clicked();

    void on_courseIdComboBox_currentTextChanged(const QString &arg1);

    void on_logOutButton_clicked();


private:
    Ui::Student *ui;
};

#endif // STUDENT_H
