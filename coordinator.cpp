#include "coordinator.h"
#include "ui_coordinator.h"

Coordinator::Coordinator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Coordinator)
{
    ui->setupUi(this);
}

Coordinator::~Coordinator()
{
    delete ui;
}

void Coordinator::on_addCourseButton_clicked()
{
    ui->addTeacherPage->hide();
    ui->addStudentPage->hide();
    ui->addCourseSectionPage->hide();
    ui->assignCoursePage->hide();
    ui->assignAdvisorPage->hide();
    ui->addCoursePage->show();

    LoginCoordinator conn;

    //Filling deptComboBox
    QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select dept_name from department");
    qry->exec();
    qry->next();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->deptComboBox->setModel(model);

    //Filling selectDeptComboBox
    QSqlQueryModel *model2 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr2 = new QSqlQuery(conn.uni_db);
    qr2->prepare("select dept_name from department");
    qr2->exec();
    qr2->next();
    model2->setQuery(std::move(*qr2));
    conn.connClose();
    ui->selectDeptComboBox->setModel(model2);

    QString dpt;
    dpt = ui->selectDeptComboBox->currentText();

    //Displaying list of courses by department
    QSqlQueryModel *model3 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr3 = new QSqlQuery(conn.uni_db);
    qr3->prepare("select course_id, title from course where dept_name = '"+dpt+"'");
    qr3->exec();
    qr3->next();
    model3->setQuery(std::move(*qr3));
    conn.connClose();
    ui->listOfCourses->setModel(model3);
    ui->listOfCourses->resizeColumnsToContents();
}


void Coordinator::on_addNewCourseButton_clicked()
{
    LoginCoordinator conn;

    QString course_id, title, dept, credits;

    course_id = ui->courseIdLineEdit->text();
    title = ui->titleLineEdit->text();
    dept = ui->deptComboBox->currentText();
    credits = ui->creditsLineEdit->text();

    //Making insertion into different fields mandatory
    if(course_id.isEmpty()){
        ui->courseID_label->setText("<font color='red'>Course ID*</font>");
    }
    else{
        ui->courseID_label->setText("<font color='black'>Course ID</font>");
    }
    if(title.isEmpty()){
        ui->title_label->setText("<font color='red'>Title*</font>");
    }
    else{
        ui->title_label->setText("<font color='black'>Title</font>");
    }
    if(dept.isEmpty()){
        ui->dept_label->setText("<font color='red'>Department*</font>");
    }
    else{
        ui->dept_label->setText("<font color='black'>Department</font>");
    }
    if(credits.isEmpty()){
        ui->credits_label->setText("<font color='red'>Credits*</font>");
    }
    else{
        ui->credits_label->setText("<font color='black'>Credits</font>");
    }

    //Inserting a new course to the database
    if( !(course_id.isEmpty()) && !(title.isEmpty()) && !(dept.isEmpty()) && !(credits.isEmpty()) ){
        conn.connOpen();
        QSqlQuery qry;
        qry.prepare("insert into course values( '"+course_id+"', '"+title+"', '"+dept+"', '"+credits+"' )");
        if(qry.exec()){
            QMessageBox::information(this, tr("Add Course"), tr("Course added successfully"));
            conn.connClose();
        }
        else{
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        }
    }

    ui->courseIdLineEdit->clear();
    ui->titleLineEdit->clear();
    ui->creditsLineEdit->clear();

    QString currentDept = ui->selectDeptComboBox->currentText();

    //Displaying list of courses by department
    QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select course_id, title from course where dept_name = '"+currentDept+"'");
    qry->exec();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->listOfCourses->setModel(model);
    ui->listOfCourses->resizeColumnsToContents();
}


void Coordinator::on_selectDeptComboBox_currentTextChanged(const QString &arg1)
{
    LoginCoordinator conn;

    //Displaying list of courses by department
    QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select course_id, title from course where dept_name = '"+arg1+"'");
    qry->exec();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->listOfCourses->setModel(model);
    ui->listOfCourses->resizeColumnsToContents();
}


void Coordinator::on_addTeacherButton_clicked()
{
    ui->addCoursePage->hide();
    ui->addStudentPage->hide();
    ui->addCourseSectionPage->hide();
    ui->assignCoursePage->hide();
    ui->assignAdvisorPage->hide();
    ui->addTeacherPage->show();

    LoginCoordinator conn;

    //Filling instDeptComboBox
    QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select dept_name from department");
    qry->exec();
    qry->next();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->instDeptComboBox->setModel(model);

    //Filling selectInstDeptComboBox
    QSqlQueryModel *model2 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr2 = new QSqlQuery(conn.uni_db);
    qr2->prepare("select dept_name from department");
    qr2->exec();
    qr2->next();
    model2->setQuery(std::move(*qr2));
    conn.connClose();
    ui->selectInstDeptComboBox->setModel(model2);

    QString dpt;
    dpt = ui->selectInstDeptComboBox->currentText();

    //Displaying list of teachers by department
    QSqlQueryModel *model3 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr3 = new QSqlQuery(conn.uni_db);
    qr3->prepare("select ID, name, salary from instructor where dept_name = '"+dpt+"'");
    qr3->exec();
    qr3->next();
    model3->setQuery(std::move(*qr3));
    conn.connClose();
    ui->listOfTeachers->setModel(model3);
    ui->listOfTeachers->resizeColumnsToContents();
}


void Coordinator::on_addNewInstrButton_clicked()
{
    LoginCoordinator conn;

    QString i_id, name, dept, salary;

    i_id = ui->i_idLineEdit->text();
    name = ui->i_nameLineEdit->text();
    dept = ui->instDeptComboBox->currentText();
    salary = ui->salaryLineEdit->text();

    //Making insertion into different fields mandatory
    if(i_id.isEmpty()){
        ui->i_idLabel->setText("<font color='red'>ID*</font>");
    }
    else{
        ui->i_idLabel->setText("<font color='black'>ID</font>");
    }
    if(name.isEmpty()){
        ui->i_nameLabel->setText("<font color='red'>Name*</font>");
    }
    else{
        ui->i_nameLabel->setText("<font color='black'>Name</font>");
    }
    if(dept.isEmpty()){
        ui->i_deptLabel->setText("<font color='red'>Department*</font>");
    }
    else{
        ui->i_deptLabel->setText("<font color='black'>Department</font>");
    }
    if(salary.isEmpty()){
        ui->salaryLabel->setText("<font color='red'>Salary*</font>");
    }
    else{
        ui->salaryLabel->setText("<font color='black'>Salary</font>");
    }

    //Inserting a new teacher to the database
    if( !(i_id.isEmpty()) && !(name.isEmpty()) && !(dept.isEmpty()) && !(salary.isEmpty()) ){
        conn.connOpen();
        QSqlQuery qry;
        qry.prepare("insert into instructor values( '"+i_id+"', '"+name+"', '"+dept+"', '"+salary+"', '"+i_id+"' )");
        if(qry.exec()){
            QMessageBox::information(this, tr("Add Teacher"), tr("Teacher added successfully"));
            conn.connClose();
        }
        else{
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        }
    }

    ui->i_idLineEdit->clear();
    ui->i_nameLineEdit->clear();
    ui->salaryLineEdit->clear();

    QString currentDept = ui->selectInstDeptComboBox->currentText();
    //Displaying list of courses by department
    QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select ID, name, salary from instructor where dept_name = '"+currentDept+"'");
    qry->exec();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->listOfTeachers->setModel(model);
    ui->listOfTeachers->resizeColumnsToContents();
}


void Coordinator::on_selectInstDeptComboBox_currentTextChanged(const QString &arg1)
{
    LoginCoordinator conn;

    //Displaying list of courses by department
    QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select ID, name, salary from instructor where dept_name = '"+arg1+"'");
    qry->exec();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->listOfTeachers->setModel(model);
    ui->listOfTeachers->resizeColumnsToContents();
}


void Coordinator::on_addStudentButton_clicked()
{
    ui->addCoursePage->hide();
    ui->addTeacherPage->hide();
    ui->addCourseSectionPage->hide();
    ui->assignCoursePage->hide();
    ui->assignAdvisorPage->hide();
    ui->addStudentPage->show();

    LoginCoordinator conn;

    //Filling s_deptComboBox
    QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select dept_name from department");
    qry->exec();
    qry->next();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->s_deptComboBox->setModel(model);

    //Filling s_selectDeptComboBox
    QSqlQueryModel *model2 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr2 = new QSqlQuery(conn.uni_db);
    qr2->prepare("select dept_name from department");
    qr2->exec();
    qr2->next();
    model2->setQuery(std::move(*qr2));
    conn.connClose();
    ui->s_selectDeptComboBox->setModel(model2);

    QString dpt;
    dpt = ui->s_selectDeptComboBox->currentText();

    //Displaying list of students by department
    QSqlQueryModel *model3 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr3 = new QSqlQuery(conn.uni_db);
    qr3->prepare("select ID, name, tot_cred, CGPA from student where dept_name = '"+dpt+"'");
    qr3->exec();
    qr3->next();
    model3->setQuery(std::move(*qr3));
    conn.connClose();
    ui->listOfStudents->setModel(model3);
    ui->listOfStudents->resizeColumnsToContents();
}


void Coordinator::on_addNewStudentButton_clicked()
{
    LoginCoordinator conn;

    QString id, name, dept;

    id = ui->s_idLineEdit->text();
    name = ui->s_nameLineEdit->text();
    dept = ui->s_deptComboBox->currentText();

    //Making insertion into different fields mandatory
    if(id.isEmpty()){
        ui->s_idLabel->setText("<font color='red'>ID*</font>");
    }
    else{
        ui->s_idLabel->setText("<font color='black'>ID</font>");
    }
    if(name.isEmpty()){
        ui->s_nameLabel->setText("<font color='red'>Name*</font>");
    }
    else{
        ui->s_nameLabel->setText("<font color='black'>Name</font>");
    }
    if(dept.isEmpty()){
        ui->s_deptLabel->setText("<font color='red'>Department*</font>");
    }
    else{
        ui->s_deptLabel->setText("<font color='black'>Department</font>");
    }

    QString totCred = 0, cgpa = 0;

    //Inserting a new student to the database
    if( !(id.isEmpty()) && !(name.isEmpty()) && !(dept.isEmpty()) ){
        conn.connOpen();
        QSqlQuery qry;
        qry.prepare("insert into student values( '"+id+"', '"+name+"', '"+dept+"', '"+totCred+"', '"+cgpa+"', '"+id+"' )");
        if(qry.exec()){
            QMessageBox::information(this, tr("Add Student"), tr("Student added successfully"));
            conn.connClose();
            ui->s_idLineEdit->clear();
            ui->s_nameLineEdit->clear();
        }
        else{
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        }
    }

    QString currentDpt = ui->s_selectDeptComboBox->currentText();
    //Displaying list of students by department
    QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select ID, name, tot_cred, CGPA from student where dept_name = '"+currentDpt+"'");
    qry->exec();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->listOfStudents->setModel(model);
    ui->listOfStudents->resizeColumnsToContents();

}


void Coordinator::on_s_selectDeptComboBox_currentTextChanged(const QString &arg1)
{
    LoginCoordinator conn;

    //Displaying list of students by department
    QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select ID, name, tot_cred, CGPA from student where dept_name = '"+arg1+"'");
    qry->exec();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->listOfStudents->setModel(model);
    ui->listOfStudents->resizeColumnsToContents();
}


void Coordinator::on_addCourseSection_2_clicked()
{
    ui->addCoursePage->hide();
    ui->addStudentPage->hide();
    ui->addTeacherPage->hide();
    ui->assignCoursePage->hide();
    ui->assignAdvisorPage->hide();
    ui->addCourseSectionPage->show();

    LoginCoordinator conn;

    //Filling sec_idComboBox
    QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select course_id from course");
    qry->exec();
    qry->next();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->sec_idComboBox->setModel(model);

    //Filling sec_buidingComboBox
    QSqlQueryModel *model2 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr2 = new QSqlQuery(conn.uni_db);
    qr2->prepare("select distinct building from classroom");
    qr2->exec();
    qr2->next();
    model2->setQuery(std::move(*qr2));
    conn.connClose();
    ui->sec_buidingComboBox->setModel(model2);

    //Filling sec_roomComboBox
    QSqlQueryModel *model3 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr3 = new QSqlQuery(conn.uni_db);
    qr3->prepare("select distinct room_number from classroom");
    qr3->exec();
    qr3->next();
    model3->setQuery(std::move(*qr3));
    conn.connClose();
    ui->sec_roomComboBox->setModel(model3);

    //Filling sec_timeSlotComboBox
    QSqlQueryModel *model4 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr4 = new QSqlQuery(conn.uni_db);
    qr4->prepare("select time_slot_id from time_slot");
    qr4->exec();
    qr4->next();
    model4->setQuery(std::move(*qr4));
    conn.connClose();
    ui->sec_timeSlotComboBox->setModel(model4);

    //Filling yearComboBox
    QSqlQueryModel *model5 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr5 = new QSqlQuery(conn.uni_db);
    qr5->prepare("select distinct year from section");
    qr5->exec();
    qr5->next();
    model5->setQuery(std::move(*qr5));
    conn.connClose();
    ui->yearComboBox->setModel(model5);

    QString year;
    year = ui->yearComboBox->currentText();

    //Displaying listOfSections
    QSqlQueryModel *model6 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr6 = new QSqlQuery(conn.uni_db);
    qr6->prepare("select * from section where year = '"+year+"'");
    qr6->exec();
    model6->setQuery(std::move(*qr6));
    conn.connClose();
    ui->listOfSections->setModel(model6);
    ui->listOfSections->resizeColumnsToContents();
}


void Coordinator::on_addNewCourseSectionButton_clicked()
{
    LoginCoordinator conn;

    QString secID, year, course, semester, building, roomNo, timeSlot;

    secID = ui->sec_secIdLineEdit->text();
    year = ui->sec_yearLineEdit->text();
    course = ui->sec_idComboBox->currentText();
    semester = ui->sec_semesterComboBox->currentText();
    building = ui->sec_buidingComboBox->currentText();
    roomNo = ui->sec_roomComboBox->currentText();
    timeSlot = ui->sec_timeSlotComboBox->currentText();

    //Making insertion into different fields mandatory
    if(secID.isEmpty()){
        ui->sec_secIdLabel->setText("<font color='red'>SecID*</font>");
    }
    else{
        ui->sec_secIdLabel->setText("<font color='black'>SecID</font>");
    }
    if(year.isEmpty()){
        ui->sec_yearLabel->setText("<font color='red'>Year*</font>");
    }
    else{
        ui->sec_yearLabel->setText("<font color='black'>Year</font>");
    }

    //Inserting a new course section to the database
    if( !(secID.isEmpty()) && !(year.isEmpty()) ){
        conn.connOpen();
        QSqlQuery qry;
        qry.prepare("insert into section values( '"+course+"', '"+secID+"', '"+semester+"', '"+year+"', '"+building+"', '"+roomNo+"', '"+timeSlot+"' )");
        if(qry.exec()){
            QMessageBox::information(this, tr("Add Course Section"), tr("New Course Section added successfully"));
            conn.connClose();
        }
        else{
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        }
    }

    ui->sec_secIdLineEdit->clear();
    ui->sec_yearLineEdit->clear();

    QString currentYear;
    currentYear = ui->yearComboBox->currentText();

    QSqlQueryModel *model6 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr6 = new QSqlQuery(conn.uni_db);
    qr6->prepare("select * from section where year = '"+currentYear+"'");
    qr6->exec();
    model6->setQuery(std::move(*qr6));
    conn.connClose();
    ui->listOfSections->setModel(model6);
    ui->listOfSections->resizeColumnsToContents();
}


void Coordinator::on_yearComboBox_currentTextChanged(const QString &arg1)
{
    LoginCoordinator conn;

    QSqlQueryModel *model6 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr6 = new QSqlQuery(conn.uni_db);
    qr6->prepare("select * from section where year = '"+arg1+"'");
    qr6->exec();
    model6->setQuery(std::move(*qr6));
    conn.connClose();
    ui->listOfSections->setModel(model6);
    ui->listOfSections->resizeColumnsToContents();
}




void Coordinator::on_assignCourseButton_clicked()
{
    ui->addCoursePage->hide();
    ui->addStudentPage->hide();
    ui->addTeacherPage->hide();
    ui->addCourseSectionPage->hide();
    ui->assignAdvisorPage->hide();
    ui->assignCoursePage->show();

    LoginCoordinator conn;

    //Filling assign_idComboBox
    QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select ID from instructor");
    qry->exec();
    qry->next();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->assign_idComboBox->setModel(model);

    //Filling assign_courseComboBox
    QSqlQueryModel *model2 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr2 = new QSqlQuery(conn.uni_db);
    qr2->prepare("select course_id from course");
    qr2->exec();
    qr2->next();
    model2->setQuery(std::move(*qr2));
    conn.connClose();
    ui->assign_courseComboBox->setModel(model2);

    //Filling assign_secIdComboBox
    QSqlQueryModel *model3 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr3 = new QSqlQuery(conn.uni_db);
    qr3->prepare("select distinct sec_id from section");
    qr3->exec();
    qr3->next();
    model3->setQuery(std::move(*qr3));
    conn.connClose();
    ui->assign_secIdComboBox->setModel(model3);

    //Filling assign_semesterComboBox
    QSqlQueryModel *model4 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr4 = new QSqlQuery(conn.uni_db);
    qr4->prepare("select distinct semester from section");
    qr4->exec();
    qr4->next();
    model4->setQuery(std::move(*qr4));
    conn.connClose();
    ui->assign_semesterComboBox->setModel(model4);

    //Filling assign_yearComboBox
    QSqlQueryModel *model5 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr5 = new QSqlQuery(conn.uni_db);
    qr5->prepare("select distinct year from section");
    qr5->exec();
    qr5->next();
    model5->setQuery(std::move(*qr5));
    conn.connClose();
    ui->assign_yearComboBox->setModel(model5);

    //Filling select_yearComboBox
    QSqlQueryModel *model6 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr6 = new QSqlQuery(conn.uni_db);
    qr6->prepare("select distinct year from section");
    qr6->exec();
    qr6->next();
    model6->setQuery(std::move(*qr6));
    conn.connClose();
    ui->select_yearComboBox->setModel(model6);

    QString year;
    year = ui->select_yearComboBox->currentText();
    //Displaying listOfCourseAssigned
    QSqlQueryModel *model7 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr7 = new QSqlQuery(conn.uni_db);
    qr7->prepare("select * from teaches where year = '"+year+"'");
    qr7->exec();
    model7->setQuery(std::move(*qr7));
    conn.connClose();
    ui->listOfCourseAssigned->setModel(model7);
    ui->listOfCourseAssigned->resizeColumnsToContents();

}


void Coordinator::on_assignPushButton_clicked()
{
    QString i_id, courseID, sec_id, semester, year;

    i_id = ui->assign_idComboBox->currentText();
    courseID = ui->assign_courseComboBox->currentText();
    sec_id = ui->assign_secIdComboBox->currentText();
    semester = ui->assign_semesterComboBox->currentText();
    year = ui->assign_yearComboBox->currentText();

    LoginCoordinator conn;

    //Inserting a new course section to the database
        conn.connOpen();
        QSqlQuery qry;
        qry.prepare("insert into teaches values( '"+i_id+"', '"+courseID+"', '"+sec_id+"', '"+semester+"', '"+year+"' )");
        if(qry.exec()){
            QMessageBox::information(this, tr("Assign Course"), tr("New Course Assigned successfully"));
            conn.connClose();
        }
        else{
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        }

        //Displaying listOfCourseAssigned
        QSqlQueryModel *model7 = new QSqlQueryModel();
        conn.connOpen();
        QSqlQuery *qr7 = new QSqlQuery(conn.uni_db);
        qr7->prepare("select * from teaches where year = '"+year+"'");
        qr7->exec();
        model7->setQuery(std::move(*qr7));
        conn.connClose();
        ui->listOfCourseAssigned->setModel(model7);
        ui->listOfCourseAssigned->resizeColumnsToContents();
}


void Coordinator::on_select_yearComboBox_currentTextChanged(const QString &arg1)
{
    LoginCoordinator conn;

    //Displaying listOfCourseAssigned
    QSqlQueryModel *model7 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr7 = new QSqlQuery(conn.uni_db);
    qr7->prepare("select * from teaches where year = '"+arg1+"'");
    qr7->exec();
    model7->setQuery(std::move(*qr7));
    conn.connClose();
    ui->listOfCourseAssigned->setModel(model7);
    ui->listOfCourseAssigned->resizeColumnsToContents();
}

void Coordinator::on_advisorButton_clicked()
{
    ui->addCoursePage->hide();
    ui->addStudentPage->hide();
    ui->addTeacherPage->hide();
    ui->addCourseSectionPage->hide();
    ui->assignCoursePage->hide();
    ui->assignAdvisorPage->show();

    LoginCoordinator conn;

    //Filling advisor_deptComboBox
    QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select dept_name from department");
    qry->exec();
    qry->next();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->advisor_deptComboBox->setModel(model);

    //Filling advisor_insIDComboBox
    QSqlQueryModel *model2 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr2 = new QSqlQuery(conn.uni_db);
    qr2->prepare("select ID from instructor");
    qr2->exec();
    qr2->next();
    model2->setQuery(std::move(*qr2));
    conn.connClose();
    ui->advisor_insIDComboBox->setModel(model2);

    //Filling advisor_sID_ComboBox
    QSqlQueryModel *model3 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr3 = new QSqlQuery(conn.uni_db);
    qr3->prepare("select ID from student");
    qr3->exec();
    qr3->next();
    model3->setQuery(std::move(*qr3));
    conn.connClose();
    ui->advisor_sID_ComboBox->setModel(model3);

    QString i_id = ui->advisor_insIDComboBox->currentText(), i_name;
    //Filling ins_idLabel
    conn.connOpen();
    QSqlQuery qr4;
    qr4.prepare("select name from instructor where ID = '"+i_id+"'");
    qr4.exec();
    qr4.first();
    i_name = qr4.value(0).toString();
    conn.connClose();
    ui->ins_idLabel->setText(i_name);


    QString s_id = ui->advisor_sID_ComboBox->currentText(), s_name;
    //Filling std_Label
    conn.connOpen();
    QSqlQuery qr5;
    qr5.prepare("select name from student where ID = '"+s_id+"'");
    qr5.exec();
    qr5.first();
    s_name = qr5.value(0).toString();
    conn.connClose();
    ui->std_Label->setText(s_name);

    //Displaying list of students advised by the instructor
    QSqlQueryModel *model7 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr7 = new QSqlQuery(conn.uni_db);
    qr7->prepare("select student.ID, name from student, advisor where i_id = '"+i_id+"' and s_id = student.ID");
    qr7->exec();
    model7->setQuery(std::move(*qr7));
    conn.connClose();
    ui->listOfStudentssAdvised->setModel(model7);
    ui->listOfStudentssAdvised->resizeColumnsToContents();

}


void Coordinator::on_advisor_deptComboBox_currentTextChanged(const QString &arg1)
{
    LoginCoordinator conn;

    //Filling advisor_insIDComboBox
    QSqlQueryModel *model2 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr2 = new QSqlQuery(conn.uni_db);
    qr2->prepare("select ID from instructor where dept_name = '"+arg1+"'");
    qr2->exec();
    qr2->next();
    model2->setQuery(std::move(*qr2));
    conn.connClose();
    ui->advisor_insIDComboBox->setModel(model2);

    //Filling advisor_sID_ComboBox
    QSqlQueryModel *model3 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr3 = new QSqlQuery(conn.uni_db);
    qr3->prepare("select ID from student where dept_name = '"+arg1+"'");
    qr3->exec();
    qr3->next();
    model3->setQuery(std::move(*qr3));
    conn.connClose();
    ui->advisor_sID_ComboBox->setModel(model3);

    QString i_id = ui->advisor_insIDComboBox->currentText(), i_name;
    //Filling ins_idLabel
    conn.connOpen();
    QSqlQuery qr4;
    qr4.prepare("select name from instructor where ID = '"+i_id+"'");
    qr4.exec();
    qr4.first();
    i_name = qr4.value(0).toString();
    conn.connClose();
    ui->ins_idLabel->setText(i_name);


    QString s_id = ui->advisor_sID_ComboBox->currentText(), s_name;
    //Filling std_Label
    conn.connOpen();
    QSqlQuery qr5;
    qr5.prepare("select name from student where ID = '"+s_id+"'");
    qr5.exec();
    qr5.first();
    s_name = qr5.value(0).toString();
    conn.connClose();
    ui->std_Label->setText(s_name);

    //Displaying list of students advised by the instructor
    QSqlQueryModel *model7 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr7 = new QSqlQuery(conn.uni_db);
    qr7->prepare("select student.ID, name from student, advisor where i_id = '"+i_id+"' and s_id = student.ID");
    qr7->exec();
    model7->setQuery(std::move(*qr7));
    conn.connClose();
    ui->listOfStudentssAdvised->setModel(model7);
    ui->listOfStudentssAdvised->resizeColumnsToContents();

}


void Coordinator::on_advisor_insIDComboBox_currentTextChanged(const QString &arg1)
{
    LoginCoordinator conn;

    QString i_name;
    //Filling ins_idLabel
    conn.connOpen();
    QSqlQuery qr4;
    qr4.prepare("select name from instructor where ID = '"+arg1+"'");
    qr4.exec();
    qr4.first();
    i_name = qr4.value(0).toString();
    conn.connClose();
    ui->ins_idLabel->setText(i_name);

    //Displaying list of students advised by the instructor
    QSqlQueryModel *model7 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr7 = new QSqlQuery(conn.uni_db);
    qr7->prepare("select student.ID, name from student, advisor where i_id = '"+arg1+"' and s_id = student.ID");
    qr7->exec();
    model7->setQuery(std::move(*qr7));
    conn.connClose();
    ui->listOfStudentssAdvised->setModel(model7);
    ui->listOfStudentssAdvised->resizeColumnsToContents();
}


void Coordinator::on_advisor_sID_ComboBox_currentTextChanged(const QString &arg1)
{
    LoginCoordinator conn;

    //Filling std_Label
    conn.connOpen();
    QSqlQuery qr5;
    qr5.prepare("select name from student where ID = '"+arg1+"'");
    qr5.exec();
    qr5.first();
    QString s_name = qr5.value(0).toString();
    conn.connClose();
    ui->std_Label->setText(s_name);
}


void Coordinator::on_advisorpushButton_clicked()
{
    LoginCoordinator conn;

    QString i_id, s_id;
    i_id = ui->advisor_insIDComboBox->currentText();
    s_id = ui->advisor_sID_ComboBox->currentText();

    //Assigning an advisor to a student
        conn.connOpen();
        QSqlQuery qry;
        qry.prepare("insert into advisor values( '"+s_id+"', '"+i_id+"' )");
        if(qry.exec()){
            QMessageBox::information(this, tr("Assign advisor"), tr("Assigned successfully"));
            conn.connClose();
        }
        else{
            QMessageBox::critical(this, tr("error::"), qry.lastError().text());
        }

        //Displaying list of students advised by the instructor
        QSqlQueryModel *model7 = new QSqlQueryModel();
        conn.connOpen();
        QSqlQuery *qr7 = new QSqlQuery(conn.uni_db);
        qr7->prepare("select student.ID, name from student, advisor where i_id = '"+i_id+"' and s_id = student.ID");
        qr7->exec();
        model7->setQuery(std::move(*qr7));
        conn.connClose();
        ui->listOfStudentssAdvised->setModel(model7);
        ui->listOfStudentssAdvised->resizeColumnsToContents();
}


void Coordinator::on_logOutButton_clicked()
{
    int response = QMessageBox::question(this, "Log Out", "Do you want to continue ?");
    LoginCoordinator *loginPage = new LoginCoordinator();
    if(response == QMessageBox::Yes){
    this-> hide();
    loginPage->show();
    }
    else{
        delete loginPage;
    }
}

