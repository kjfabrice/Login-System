#include "student.h"
#include "ui_student.h"

Student::Student(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Student)
{
    ui->setupUi(this);
}

Student::~Student()
{
    delete ui;
}

void Student::on_aboutMeButton_clicked()
{
    ui->coursesRegisterdPage->hide();
    ui->aboutMePage->show();

    QString name, dept, credits, cgpa;

    LoginStudent conn;

    conn.connOpen();
    QSqlQuery qry, qr2, qr3, qr4;

    //Queries to fetch student records
    qry.prepare("select name from student where ID = '"+user+"' ");
    qry.exec();
    qry.first();
    //Gets the value at index 0 returned by the query in form of string
    name = qry.value(0).toString();

    qr2.prepare("select dept_name from student where ID = '"+user+"' ");
    qr2.exec();
    qr2.first();
    dept = qr2.value(0).toString();

    qr3.prepare("select tot_cred from student where ID = '"+user+"' ");
    qr3.exec();
    qr3.first();
    credits = qr3.value(0).toString();

    qr4.prepare("select CGPA from student where ID = '"+user+"' ");
    qr4.exec();
    qr4.first();
    cgpa = qr4.value(0).toString();

    //Filling the fields
    ui->id_label->setText(user);
    ui->name_label->setText(name);
    ui->dept_label->setText(dept);
    ui->credits_label->setText(credits);
    ui->cgpa_label->setText(cgpa);

    conn.connClose();
}


void Student::on_updateButton_clicked()
{
    LoginStudent conn;
    QString name, pwd;
    name = ui->updateNameLineEdit->text();
    pwd = ui->updatePwdLineEdit->text();

    if(!conn.connOpen()){
        qDebug() << "Failed to open the database";
        return;
    }

    if(name.isEmpty()){
        conn.connOpen();
        QSqlQuery qr1;
        qr1.prepare("select name from student where ID = '"+user+"' ");
        qr1.exec();
        qr1.first();
        name = qr1.value(0).toString();
        conn.connClose();
    }

    if (pwd.isEmpty()) {
        conn.connOpen();
        QSqlQuery qr2;
        qr2.prepare("select password from student where ID = '"+user+"'");
        qr2.exec();
        qr2.first();
        pwd = qr2.value(0).toString();
        conn.connClose();
    }

    conn.connOpen();
    QSqlQuery qry;
    qry.prepare("update student set name = '"+name+"', password = '"+pwd+"' where ID = '"+user+"' ");

    if(qry.exec()){
        QMessageBox::information(this, tr("Edit"), tr("Updated"));
        conn.connClose();
    }
    else{
        QMessageBox::critical(this, tr("error::"), qry.lastError().text());
    }
    ui->name_label->setText(name);
    ui->updateNameLineEdit->clear();
    ui->updatePwdLineEdit->clear();
}


void Student::on_coursesButton_clicked()
{
    ui->aboutMePage->hide();
    ui->coursesRegisterdPage->show();
    ui->semesterLabel->setText("Fall");

    //Filling semesterComboBox
    LoginStudent conn;
   /* QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select distinct semester from takes where ID = '"+user+"'");
    qry->exec();
    qry->next();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->semesterComboBox->setModel(model);
*/
    //Filling yearComboBox
    QSqlQueryModel *model2 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr2 = new QSqlQuery(conn.uni_db);
    qr2->prepare("select distinct year from takes where ID = '"+user+"'");
    qr2->exec();
    qr2->next();
    model2->setQuery(std::move(*qr2));
    conn.connClose();
    ui->yearComboBox->setModel(model2);

    //Filling courseIdComboBox
    QString smster, year;
    smster = ui->semesterLabel->text();
    year = ui->yearComboBox->currentText();

    QSqlQueryModel *model3 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr3 = new QSqlQuery(conn.uni_db);
    qr3->prepare("select course_id from takes where ID = '"+user+"' and semester = '"+smster+"' and year = '"+year+"'");
    qr3->exec();
    qr3->next();
    model3->setQuery(std::move(*qr3));
    conn.connClose();
    ui->courseIdComboBox->setModel(model3);

    //Filling course information fields
    QString courseID, title, credits;
    courseID = ui->courseIdComboBox->currentText();
    conn.connOpen();
    QSqlQuery qr4, qr5;
    qr4.prepare("select title from course where course_id = '"+courseID+"'");
    qr4.exec();
    qr4.first();
    title = qr4.value(0).toString();

    ui->title_label->setText(title);

    qr5.prepare("select credits from course where course_id = '"+courseID+"'");
    qr5.exec();
    qr5.first();
    credits = qr5.value(0).toString();
    conn.connClose();
    ui->courseCredit_label->setText(credits);

    //Display the list of other students registered
    QSqlQueryModel *model4 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr6 = new QSqlQuery(conn.uni_db);
    qr6->prepare("select takes.ID, name, semester, year from takes, student where course_id = '"+courseID+"' and takes.ID = student.ID and semester = '"+smster+"' and year = '"+year+"'");
    qr6->exec();
    qr6->next();
    model4->setQuery(std::move(*qr6));
    conn.connClose();
    ui->listOfStudents->setModel(model4);

}

void Student::on_yearComboBox_currentTextChanged(const QString &arg1)
{
    LoginStudent conn;

    QString smster;
    smster = ui->semesterLabel->text();

    //Change courseIdComboBox value
    QSqlQueryModel *model2 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr2 = new QSqlQuery(conn.uni_db);
    qr2->prepare("select course_id from takes where ID = '"+user+"' and semester = '"+smster+"' and year = '"+arg1+"'");
    qr2->exec();
    qr2->next();
    model2->setQuery(std::move(*qr2));
    conn.connClose();
    ui->courseIdComboBox->setModel(model2);

    //Filling course information fields
    QString courseID, title, credits;
    courseID = ui->courseIdComboBox->currentText();
    conn.connOpen();
    QSqlQuery qr3, qr4;
    qr3.prepare("select title from course where course_id = '"+courseID+"'");
    qr3.exec();
    qr3.first();
    title = qr3.value(0).toString();

    ui->title_label->setText(title);

    qr4.prepare("select credits from course where course_id = '"+courseID+"'");
    qr4.exec();
    qr4.first();
    credits = qr4.value(0).toString();
    conn.connClose();
    ui->courseCredit_label->setText(credits);

    //Display the list of other students registered
    QSqlQueryModel *model3 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr5 = new QSqlQuery(conn.uni_db);
    qr5->prepare("select takes.ID, name, semester, year from takes, student where course_id = '"+courseID+"' and takes.ID = student.ID and semester = '"+smster+"' and year = '"+arg1+"'");
    qr5->exec();
    qr5->next();
    model3->setQuery(std::move(*qr5));
    conn.connClose();
    ui->listOfStudents->setModel(model3);
}


void Student::on_fallButton_clicked()
{
    LoginStudent conn;

    ui->semesterLabel->setText("Fall");

    QString smster, year;
    smster = ui->semesterLabel->text();
    year = ui->yearComboBox->currentText();


    //Filling yearComboBox
    QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select distinct year from takes where ID = '"+user+"' and semester = '"+smster+"'");
    qry->exec();
    qry->next();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->yearComboBox->setModel(model);

    //Change courseIdComboBox value
    QSqlQueryModel *model2 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr2 = new QSqlQuery(conn.uni_db);
    qr2->prepare("select course_id from takes where ID = '"+user+"' and semester = '"+smster+"' and year = '"+year+"'");
    qr2->exec();
    qr2->next();
    model2->setQuery(std::move(*qr2));
    conn.connClose();
    ui->courseIdComboBox->setModel(model2);

    //Filling course information fields
    QString courseID, title, credits;
    courseID = ui->courseIdComboBox->currentText();
    conn.connOpen();
    QSqlQuery qr3, qr4;
    qr3.prepare("select title from course where course_id = '"+courseID+"'");
    qr3.exec();
    qr3.first();
    title = qr3.value(0).toString();

    ui->title_label->setText(title);

    qr4.prepare("select credits from course where course_id = '"+courseID+"'");
    qr4.exec();
    qr4.first();
    credits = qr4.value(0).toString();
    conn.connClose();
    ui->courseCredit_label->setText(credits);

    //Display the list of other students registered
    QSqlQueryModel *model3 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr5 = new QSqlQuery(conn.uni_db);
    qr5->prepare("select takes.ID, name, semester, year from takes, student where course_id = '"+courseID+"' and takes.ID = student.ID and semester = '"+smster+"' and year = '"+year+"'");
    qr5->exec();
    qr5->next();
    model3->setQuery(std::move(*qr5));
    conn.connClose();
    ui->listOfStudents->setModel(model3);

}


void Student::on_springButton_clicked()
{
    LoginStudent conn;

    ui->semesterLabel->setText("Spring");

    QString smster, year;
    smster = ui->semesterLabel->text();
    year = ui->yearComboBox->currentText();

    //Filling yearComboBox
    QSqlQueryModel *model = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qry = new QSqlQuery(conn.uni_db);
    qry->prepare("select distinct year from takes where ID = '"+user+"' and semester = '"+smster+"'");
    qry->exec();
    qry->next();
    model->setQuery(std::move(*qry));
    conn.connClose();
    ui->yearComboBox->setModel(model);

    //Change courseIdComboBox value
    QSqlQueryModel *model2 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr2 = new QSqlQuery(conn.uni_db);
    qr2->prepare("select course_id from takes where ID = '"+user+"' and semester = '"+smster+"' and year = '"+year+"'");
    qr2->exec();
    qr2->next();
    model2->setQuery(std::move(*qr2));
    conn.connClose();
    ui->courseIdComboBox->setModel(model2);

    //Filling course information fields
    QString courseID, title, credits;
    courseID = ui->courseIdComboBox->currentText();
    conn.connOpen();
    QSqlQuery qr3, qr4;
    qr3.prepare("select title from course where course_id = '"+courseID+"'");
    qr3.exec();
    qr3.first();
    title = qr3.value(0).toString();

    ui->title_label->setText(title);

    qr4.prepare("select credits from course where course_id = '"+courseID+"'");
    qr4.exec();
    qr4.first();
    credits = qr4.value(0).toString();
    conn.connClose();
    ui->courseCredit_label->setText(credits);

    //Display the list of other students registered
    QSqlQueryModel *model3 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr5 = new QSqlQuery(conn.uni_db);
    qr5->prepare("select takes.ID, name, semester, year from takes, student where course_id = '"+courseID+"' and takes.ID = student.ID and semester = '"+smster+"' and year = '"+year+"'");
    qr5->exec();
    qr5->next();
    model3->setQuery(std::move(*qr5));
    conn.connClose();
    ui->listOfStudents->setModel(model3);
}


void Student::on_courseIdComboBox_currentTextChanged(const QString &arg1)
{
    LoginStudent conn;

    QString smster, year;
    smster = ui->semesterLabel->text();
    year = ui->yearComboBox->currentText();

    //Filling course information fields
    QString title, credits;
    conn.connOpen();
    QSqlQuery qr3, qr4;
    qr3.prepare("select title from course where course_id = '"+arg1+"'");
    qr3.exec();
    qr3.first();
    title = qr3.value(0).toString();

    ui->title_label->setText(title);

    qr4.prepare("select credits from course where course_id = '"+arg1+"'");
    qr4.exec();
    qr4.first();
    credits = qr4.value(0).toString();
    conn.connClose();
    ui->courseCredit_label->setText(credits);

    //Display the list of other students registered
    QSqlQueryModel *model3 = new QSqlQueryModel();
    conn.connOpen();
    QSqlQuery *qr5 = new QSqlQuery(conn.uni_db);
    qr5->prepare("select takes.ID, name, semester, year from takes, student where course_id = '"+arg1+"' and takes.ID = student.ID and semester = '"+smster+"' and year = '"+year+"'");
    qr5->exec();
    qr5->next();
    model3->setQuery(std::move(*qr5));
    conn.connClose();
    ui->listOfStudents->setModel(model3);
}


void Student::on_logOutButton_clicked()
{
    int response = QMessageBox::question(this, "Log Out", "Do you want to continue ?");
    LoginStudent *loginPage = new LoginStudent();
    if(response == QMessageBox::Yes){
    this-> hide();
    loginPage->show();
    }
    else{
        delete loginPage;
    }
}
