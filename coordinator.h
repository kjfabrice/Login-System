#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <QDialog>
#include"logincoordinator.h"

namespace Ui {
class Coordinator;
}

class Coordinator : public QDialog
{
    Q_OBJECT

public:
    explicit Coordinator(QWidget *parent = nullptr);
    ~Coordinator();

private slots:
    void on_addCourseButton_clicked();

    void on_addNewCourseButton_clicked();

    void on_selectDeptComboBox_currentTextChanged(const QString &arg1);

    void on_addTeacherButton_clicked();

    void on_addNewInstrButton_clicked();

    void on_selectInstDeptComboBox_currentTextChanged(const QString &arg1);

    void on_addStudentButton_clicked();

    void on_addNewStudentButton_clicked();

    void on_s_selectDeptComboBox_currentTextChanged(const QString &arg1);

    void on_addCourseSection_2_clicked();

    void on_addNewCourseSectionButton_clicked();

    void on_yearComboBox_currentTextChanged(const QString &arg1);

    void on_assignCourseButton_clicked();

    void on_assignPushButton_clicked();

    void on_select_yearComboBox_currentTextChanged(const QString &arg1);

    void on_advisorButton_clicked();

    void on_advisor_deptComboBox_currentTextChanged(const QString &arg1);

    void on_advisor_insIDComboBox_currentTextChanged(const QString &arg1);

    void on_advisor_sID_ComboBox_currentTextChanged(const QString &arg1);

    void on_advisorpushButton_clicked();

    void on_logOutButton_clicked();

private:
    Ui::Coordinator *ui;
};

#endif // COORDINATOR_H
