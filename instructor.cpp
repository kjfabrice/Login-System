#include "instructor.h"
#include "ui_instructor.h"

instructor::instructor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::instructor)
{
    ui->setupUi(this);
}

instructor::~instructor()
{
    delete ui;
}

void instructor::on_aboutMeButton_clicked()
{
    //***********Only show the About me page***********//
    ui->aboutMePage->show();
    ui->coursesDetailsPage->hide();
    ui->registerStudentsPage->hide();
    ui->emptyPage->hide();
    //***********Filling personal details about the instructor***********//
    //query
    instructorLogin instCon;
    QSqlQueryModel *model = new QSqlQueryModel();
    instCon.connOpen();
    QSqlQuery *qry = new QSqlQuery(instCon.mydb);
    qry->prepare("SELECT * FROM instructor WHERE ID = '"+userID+"'");
    qry->exec();
    qry->next();
    model->setQuery(std::move(*qry));
    //filling info
    ui->idField->setText(model->record(0).value("ID").toString());
    ui->nameField->setText(model->record(0).value("name").toString());
    ui->departmentField->setText(model->record(0).value("dept_name").toString());
    ui->salaryField->setText(model->record(0).value("salary").toString());
    instCon.connClose();
}


void instructor::on_updateButton_clicked()
{
    instructorLogin instConn;
    QString name, pwd;
    name = ui->inputNameField->text();
    pwd = ui->inputNewPasswordField->text();

    if(!instConn.connOpen()){
        qDebug() << "Failed to open the database";
        return;
    }

    //***********update button clicked while fields are empty***********//
    if(name.isEmpty()){
        instConn.connOpen();
        QSqlQuery qr1;
        qr1.prepare("select name from instructor where ID = '"+userID+"' ");
        qr1.exec();
        qr1.first();
        name = qr1.value(0).toString();
        instConn.connClose();
    }
    if (pwd.isEmpty()) {
        instConn.connOpen();
        QSqlQuery qr3;
        qr3.prepare("select password from instructor where ID = '"+userID+"'");
        qr3.exec();
        qr3.first();
        pwd = qr3.value(0).toString();
        instConn.connClose();
    }

    //update query
    instConn.connOpen();
    QSqlQuery qry1;
    qry1.prepare("update instructor set name = '"+name+"', password = '"+pwd+"' where ID = '"+userID+"' ");

    if(qry1.exec()){
        QMessageBox::information(this, tr("Edit"), tr("Updated"));
    }
    else{
        QMessageBox::critical(this, tr("error::"), qry1.lastError().text());
    }
    instConn.connClose();
    //***********update button clicked while fields are empty***********//
    QSqlQueryModel *model = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry2 = new QSqlQuery(instConn.mydb);
    qry2->prepare("SELECT * FROM instructor WHERE ID = '"+userID+"'");
    qry2->exec();
    qry2->next();
    model->setQuery(std::move(*qry2));
    //filling info
    ui->idField->setText(model->record(0).value("ID").toString());
    ui->nameField->setText(model->record(0).value("name").toString());
    ui->departmentField->setText(model->record(0).value("dept_name").toString());
    ui->salaryField->setText(model->record(0).value("salary").toString());
    instConn.connClose();
}





void instructor::on_courseDetailsButton_clicked()
{
    //************************//
    //*show page*//
    ui->coursesDetailsPage->show();
    ui->aboutMePage->hide();
    ui->registerStudentsPage->hide();
    ui->emptyPage->hide();
}


void instructor::on_fallButton_clicked()
{
    ui->selectionStatusText->setText("Fall");
    QString semesterID = ui->selectionStatusText->text();
    instructorLogin instConn;
    //*Fill the year comboBox*//
    QSqlQueryModel *model2 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry2 = new QSqlQuery(instConn.mydb);
    qry2->prepare("SELECT DISTINCT year FROM teaches WHERE ID = '"+userID+"' AND semester = '"+semesterID+"'");
    qry2->exec();
    qry2->next();
    model2->setQuery(std::move(*qry2));
    instConn.connClose();
    ui->yearComboBox->setModel(model2);

    //*Fill course comboBox*//
    QString yearID = ui->yearComboBox->currentText();
    QSqlQueryModel *model3 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry3 = new QSqlQuery(instConn.mydb);
    qry3->prepare("SELECT course_id FROM teaches WHERE ID = '"+userID+"' AND year = '"+yearID+"' AND semester = '"+semesterID+"'");
    qry3->exec();
    qry3->next();
    model3->setQuery(std::move(*qry3));
    instConn.connClose();
    ui->coursesComboBox->setModel(model3);

    //*Fill course information*//
    QString courseID = ui->coursesComboBox->currentText();
    QSqlQueryModel *model4 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry4 = new QSqlQuery(instConn.mydb);
    qry4->prepare("SELECT title, dept_name, credits FROM course WHERE course_id = '"+courseID+"'");
    qry4->exec();
    qry4->next();
    model4->setQuery(std::move(*qry4));

    //filling course information
    ui->titleField->setText(model4->record(0).value("title").toString());
    ui->departmentField_2->setText(model4->record(0).value("dept_name").toString());
    ui->creditsField->setText(model4->record(0).value("credits").toString());
    instConn.connClose();

    //information about the students registered in the course
    QSqlQueryModel *model6 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry6 = new QSqlQuery(instConn.mydb);
    qry6->prepare("SELECT takes.ID, name FROM takes, student WHERE takes.ID = student.ID AND course_id = '"+courseID+"' AND semester = '"+semesterID+"' AND year = '"+yearID+"'");
    qry6->exec();
    qry6->next();
    model6->setQuery(std::move(*qry6));
    instConn.connClose();
    ui->studentsRegistered->setModel(model6);
}


void instructor::on_springButton_clicked()
{
    ui->selectionStatusText->setText("Spring");
    QString semesterID = ui->selectionStatusText->text();
    instructorLogin instConn;
    //*Fill the year comboBox*//
    QSqlQueryModel *model2 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry2 = new QSqlQuery(instConn.mydb);
    qry2->prepare("SELECT DISTINCT year FROM teaches WHERE ID = '"+userID+"' AND semester = '"+semesterID+"'");
    qry2->exec();
    qry2->next();
    model2->setQuery(std::move(*qry2));
    instConn.connClose();
    ui->yearComboBox->setModel(model2);

    //*Fill course comboBox*//
    QString yearID = ui->yearComboBox->currentText();
    QSqlQueryModel *model3 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry3 = new QSqlQuery(instConn.mydb);
    qry3->prepare("SELECT course_id FROM teaches WHERE ID = '"+userID+"' AND year = '"+yearID+"' AND semester = '"+semesterID+"'");
    qry3->exec();
    qry3->next();
    model3->setQuery(std::move(*qry3));
    instConn.connClose();
    ui->coursesComboBox->setModel(model3);

    //*Fill course information*//
    QString courseID = ui->coursesComboBox->currentText();
    QSqlQueryModel *model4 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry4 = new QSqlQuery(instConn.mydb);
    qry4->prepare("SELECT title, dept_name, credits FROM course WHERE course_id = '"+courseID+"'");
    qry4->exec();
    qry4->next();
    model4->setQuery(std::move(*qry4));

    //filling course information
    ui->titleField->setText(model4->record(0).value("title").toString());
    ui->departmentField_2->setText(model4->record(0).value("dept_name").toString());
    ui->creditsField->setText(model4->record(0).value("credits").toString());
    instConn.connClose();

    //information about the students registered in the course
    QSqlQueryModel *model6 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry6 = new QSqlQuery(instConn.mydb);
    qry6->prepare("SELECT takes.ID, name FROM takes, student WHERE takes.ID = student.ID AND course_id = '"+courseID+"' AND semester = '"+semesterID+"' AND year = '"+yearID+"'");
    qry6->exec();
    qry6->next();
    model6->setQuery(std::move(*qry6));
    instConn.connClose();
    ui->studentsRegistered->setModel(model6);
}


void instructor::on_yearComboBox_currentTextChanged(const QString &arg1)
{
    instructorLogin instConn;
    QString semesterID = ui->selectionStatusText->text();
    //*Fill course comboBox*//
    QSqlQueryModel *model3 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry3 = new QSqlQuery(instConn.mydb);
    qry3->prepare("SELECT course_id FROM teaches WHERE ID = '"+userID+"' AND year = '"+arg1+"' AND semester = '"+semesterID+"'");
    qry3->exec();
    qry3->next();
    model3->setQuery(std::move(*qry3));
    instConn.connClose();
    ui->coursesComboBox->setModel(model3);

    //*Fill course information*//
    QString courseID = ui->coursesComboBox->currentText();
    QSqlQueryModel *model4 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry4 = new QSqlQuery(instConn.mydb);
    qry4->prepare("SELECT title, dept_name, credits FROM course WHERE course_id = '"+courseID+"'");
    qry4->exec();
    qry4->next();
    model4->setQuery(std::move(*qry4));

    //filling course information
    ui->titleField->setText(model4->record(0).value("title").toString());
    ui->departmentField_2->setText(model4->record(0).value("dept_name").toString());
    ui->creditsField->setText(model4->record(0).value("credits").toString());
    instConn.connClose();

    //information about the students registered in the course
    QSqlQueryModel *model6 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry6 = new QSqlQuery(instConn.mydb);
    qry6->prepare("SELECT takes.ID, name FROM takes, student WHERE takes.ID = student.ID AND course_id = '"+courseID+"' AND semester = '"+semesterID+"' AND year = '"+arg1+"'");
    qry6->exec();
    qry6->next();
    model6->setQuery(std::move(*qry6));
    instConn.connClose();
    ui->studentsRegistered->setModel(model6);

}


void instructor::on_coursesComboBox_currentTextChanged(const QString &arg1)
{
    instructorLogin instConn;
    QString semesterID = ui->selectionStatusText->text();
    QString yearID = ui->yearComboBox->currentText();
    //*Fill course information*//
    QSqlQueryModel *model4 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry4 = new QSqlQuery(instConn.mydb);
    qry4->prepare("SELECT title, dept_name, credits FROM course WHERE course_id = '"+arg1+"'");
    qry4->exec();
    qry4->next();
    model4->setQuery(std::move(*qry4));

    //filling course information
    ui->titleField->setText(model4->record(0).value("title").toString());
    ui->departmentField_2->setText(model4->record(0).value("dept_name").toString());
    ui->creditsField->setText(model4->record(0).value("credits").toString());
    instConn.connClose();

    //information about the students registered in the course
    QSqlQueryModel *model6 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry6 = new QSqlQuery(instConn.mydb);
    qry6->prepare("SELECT takes.ID, name FROM takes, student WHERE takes.ID = student.ID AND course_id = '"+arg1+"' AND semester = '"+semesterID+"' AND year = '"+yearID+"'");
    qry6->exec();
    qry6->next();
    model6->setQuery(std::move(*qry6));
    instConn.connClose();
    ui->studentsRegistered->setModel(model6);
}


void instructor::on_registerStudentsButton_clicked()
{
    ui->registerStudentsPage->show();
    ui->coursesDetailsPage->hide();
    ui->aboutMePage->hide();
    ui->emptyPage->hide();

    //*Fill coursesComboBox2*//
    instructorLogin instConn;
    //*Fill course comboBox*//
    QSqlQueryModel *model3 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry3 = new QSqlQuery(instConn.mydb);
    qry3->prepare("SELECT DISTINCT course_id FROM teaches WHERE ID = '"+userID+"'");
    qry3->exec();
    qry3->next();
    model3->setQuery(std::move(*qry3));
    instConn.connClose();
    ui->coursesComboBox2->setModel(model3);

    QString courseID = ui->coursesComboBox2->currentText();
    qDebug() << userID << " " << courseID;
    //*Fill yearComboBox2*//
    QSqlQueryModel *model2 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry2 = new QSqlQuery(instConn.mydb);
    qry2->prepare("SELECT DISTINCT year FROM teaches WHERE ID = '"+userID+"' AND course_id = '"+courseID+"'");
    qry2->exec();
    qry2->next();
    model2->setQuery(std::move(*qry2));
    instConn.connClose();
     ui->yearComboBox2->setModel(model2);

    //**********************************************************//
    QString yearID = ui->yearComboBox2->currentText();
    //*Fill semester*//
    QSqlQueryModel *model1 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry1 = new QSqlQuery(instConn.mydb);
    qry1->prepare("SELECT DISTINCT semester FROM teaches WHERE ID = '"+userID+"' AND course_id = '"+courseID+"' AND year = '"+yearID+"'");
    qry1->exec();
    qry1->next();
    model1->setQuery(std::move(*qry1));
    instConn.connClose();
     ui->semesterComboBox2->setModel(model1);

    //*Fill studentInfo*//
    QString semesterID = ui->semesterComboBox2->currentText();
    //get course department
    QSqlQueryModel *model4 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry4 = new QSqlQuery(instConn.mydb);
    qry4->prepare("SELECT dept_name FROM course WHERE course_id = '"+courseID+"'");
    qry4->exec();
    qry4->next();
    model4->setQuery(std::move(*qry4));
    instConn.connClose();
    QString deptID = model4->record(0).value("dept_name").toString();
    qDebug() << deptID;

    //find students in the department that are no registered to the course
    QSqlQueryModel *model5 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry5 = new QSqlQuery(instConn.mydb);
    qry5->prepare("SELECT ID FROM student WHERE dept_name = '"+deptID+"' AND ID not in (SELECT DISTINCT ID FROM takes WHERE course_id = '"+courseID+"' AND semester = '"+semesterID+"' AND year = '"+yearID+"')");
    qry5->exec();
    qry5->next();
    model5->setQuery(std::move(*qry5));
    instConn.connClose();
    ui->studentIdComboBox->setModel(model5);

    //fill student name
    QString stdID = ui->studentIdComboBox->currentText();
    QSqlQueryModel *model6 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry6 = new QSqlQuery(instConn.mydb);
    qry6->prepare("SELECT name FROM student WHERE ID = '"+stdID+"'");
    qry6->exec();
    qry6->next();
    model6->setQuery(std::move(*qry6));
    instConn.connClose();
    QString nameID = model6->record(0).value("name").toString();
    ui->stdName->setText(nameID);

    //*Fill secID*//
    QSqlQueryModel *model7 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry7 = new QSqlQuery(instConn.mydb);
    qry7->prepare("SELECT sec_id FROM teaches WHERE ID = '"+userID+"' AND course_id = '"+courseID+"' AND semester = '"+semesterID+"' AND year = '"+yearID+"'");
    qry7->exec();
    qry7->next();
    model7->setQuery(std::move(*qry7));
    instConn.connClose();
    ui->secIdComboBox->setModel(model7);
}

void instructor::on_coursesComboBox2_currentTextChanged(const QString &arg1)
{
    instructorLogin instConn;

    //*Fill yearComboBox2*//
    QSqlQueryModel *model2 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry2 = new QSqlQuery(instConn.mydb);
    qry2->prepare("SELECT DISTINCT year FROM teaches WHERE ID = '"+userID+"' AND course_id = '"+arg1+"'");
    qry2->exec();
    qry2->next();
    model2->setQuery(std::move(*qry2));
    instConn.connClose();
     ui->yearComboBox2->setModel(model2);

    //**********************************************************//
    QString yearID = ui->yearComboBox2->currentText();
    //*Fill semester*//
    QSqlQueryModel *model1 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry1 = new QSqlQuery(instConn.mydb);
    qry1->prepare("SELECT DISTINCT semester FROM teaches WHERE ID = '"+userID+"' AND course_id = '"+arg1+"' AND year = '"+yearID+"'");
    qry1->exec();
    qry1->next();
    model1->setQuery(std::move(*qry1));
    instConn.connClose();
     ui->semesterComboBox2->setModel(model1);

    //*Fill studentInfo*//
    QString semesterID = ui->semesterComboBox2->currentText();
    //get course department
    QSqlQueryModel *model4 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry4 = new QSqlQuery(instConn.mydb);
    qry4->prepare("SELECT dept_name FROM course WHERE course_id = '"+arg1+"'");
    qry4->exec();
    qry4->next();
    model4->setQuery(std::move(*qry4));
    instConn.connClose();
    QString deptID = model4->record(0).value("dept_name").toString();
    qDebug() << deptID;

    //find students in the department that are no registered to the course
    QSqlQueryModel *model5 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry5 = new QSqlQuery(instConn.mydb);
    qry5->prepare("SELECT ID FROM student WHERE dept_name = '"+deptID+"' AND ID not in (SELECT DISTINCT ID FROM takes WHERE course_id = '"+arg1+"' AND semester = '"+semesterID+"' AND year = '"+yearID+"')");
    qry5->exec();
    qry5->next();
    model5->setQuery(std::move(*qry5));
    instConn.connClose();
    ui->studentIdComboBox->setModel(model5);

    //fill student name
    QString stdID = ui->studentIdComboBox->currentText();
    QSqlQueryModel *model6 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry6 = new QSqlQuery(instConn.mydb);
    qry6->prepare("SELECT name FROM student WHERE ID = '"+stdID+"'");
    qry6->exec();
    qry6->next();
    model6->setQuery(std::move(*qry6));
    instConn.connClose();
    QString nameID = model6->record(0).value("name").toString();
    ui->stdName->setText(nameID);

    //*Fill secID*//
    QSqlQueryModel *model7 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry7 = new QSqlQuery(instConn.mydb);
    qry7->prepare("SELECT sec_id FROM teaches WHERE ID = '"+userID+"' AND course_id = '"+arg1+"' AND semester = '"+semesterID+"' AND year = '"+yearID+"'");
    qry7->exec();
    qry7->next();
    model7->setQuery(std::move(*qry7));
    instConn.connClose();
    ui->secIdComboBox->setModel(model7);
}

void instructor::on_yearComboBox2_currentTextChanged(const QString &arg1)
{
    instructorLogin instConn;
    QString courseID = ui->coursesComboBox2->currentText();
    //*Fill semester*//
    QSqlQueryModel *model1 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry1 = new QSqlQuery(instConn.mydb);
    qry1->prepare("SELECT DISTINCT semester FROM teaches WHERE ID = '"+userID+"' AND course_id = '"+courseID+"' AND year = '"+arg1+"'");
    qry1->exec();
    qry1->next();
    model1->setQuery(std::move(*qry1));
    instConn.connClose();
     ui->semesterComboBox2->setModel(model1);

    //*Fill studentInfo*//
    QString semesterID = ui->semesterComboBox2->currentText();
    //get course department
    QSqlQueryModel *model4 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry4 = new QSqlQuery(instConn.mydb);
    qry4->prepare("SELECT dept_name FROM course WHERE course_id = '"+courseID+"'");
    qry4->exec();
    qry4->next();
    model4->setQuery(std::move(*qry4));
    instConn.connClose();
    QString deptID = model4->record(0).value("dept_name").toString();
    qDebug() << deptID;

    //find students in the department that are no registered to the course
    QSqlQueryModel *model5 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry5 = new QSqlQuery(instConn.mydb);
    qry5->prepare("SELECT ID FROM student WHERE dept_name = '"+deptID+"' AND ID not in (SELECT DISTINCT ID FROM takes WHERE course_id = '"+courseID+"' AND semester = '"+semesterID+"' AND year = '"+arg1+"')");
    qry5->exec();
    qry5->next();
    model5->setQuery(std::move(*qry5));
    instConn.connClose();
    ui->studentIdComboBox->setModel(model5);

    //fill student name
    QString stdID = ui->studentIdComboBox->currentText();
    QSqlQueryModel *model6 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry6 = new QSqlQuery(instConn.mydb);
    qry6->prepare("SELECT name FROM student WHERE ID = '"+stdID+"'");
    qry6->exec();
    qry6->next();
    model6->setQuery(std::move(*qry6));
    instConn.connClose();
    QString nameID = model6->record(0).value("name").toString();
    ui->stdName->setText(nameID);

    //*Fill secID*//
    QSqlQueryModel *model7 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry7 = new QSqlQuery(instConn.mydb);
    qry7->prepare("SELECT sec_id FROM teaches WHERE ID = '"+userID+"' AND course_id = '"+courseID+"' AND semester = '"+semesterID+"' AND year = '"+arg1+"'");
    qry7->exec();
    qry7->next();
    model7->setQuery(std::move(*qry7));
    instConn.connClose();
    ui->secIdComboBox->setModel(model7);
}





void instructor::on_semesterComboBox2_currentTextChanged(const QString &arg1)
{
    QString courseID, yearID;
    courseID = ui->coursesComboBox2->currentText();
    yearID = ui->yearComboBox2->currentText();
    instructorLogin instConn;
    //*Fill studentInfo*//
    //get course department
    QSqlQueryModel *model4 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry4 = new QSqlQuery(instConn.mydb);
    qry4->prepare("SELECT dept_name FROM course WHERE course_id = '"+courseID+"'");
    qry4->exec();
    qry4->next();
    model4->setQuery(std::move(*qry4));
    instConn.connClose();
    QString deptID = model4->record(0).value("dept_name").toString();
    qDebug() << deptID;

    //find students in the department that are no registered to the course
    QSqlQueryModel *model5 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry5 = new QSqlQuery(instConn.mydb);
    qry5->prepare("SELECT ID FROM student WHERE dept_name = '"+deptID+"' AND ID not in (SELECT DISTINCT ID FROM takes WHERE course_id = '"+courseID+"' AND semester = '"+arg1+"' AND year = '"+yearID+"')");
    qry5->exec();
    qry5->next();
    model5->setQuery(std::move(*qry5));
    instConn.connClose();
    ui->studentIdComboBox->setModel(model5);

    //fill student name
    QString stdID = ui->studentIdComboBox->currentText();
    QSqlQueryModel *model6 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry6 = new QSqlQuery(instConn.mydb);
    qry6->prepare("SELECT name FROM student WHERE ID = '"+stdID+"'");
    qry6->exec();
    qry6->next();
    model6->setQuery(std::move(*qry6));
    instConn.connClose();
    QString nameID = model6->record(0).value("name").toString();
    ui->stdName->setText(nameID);

    //*Fill secID*//
    QSqlQueryModel *model7 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry7 = new QSqlQuery(instConn.mydb);
    qry7->prepare("SELECT sec_id FROM teaches WHERE ID = '"+userID+"' AND course_id = '"+courseID+"' AND semester = '"+arg1+"' AND year = '"+yearID+"'");
    qry7->exec();
    qry7->next();
    model7->setQuery(std::move(*qry7));
    instConn.connClose();
    ui->secIdComboBox->setModel(model7);
}


void instructor::on_studentIdComboBox_currentTextChanged(const QString &arg1)
{
    instructorLogin instConn;

    //fill student name
    QSqlQueryModel *model6 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry6 = new QSqlQuery(instConn.mydb);
    qry6->prepare("SELECT name FROM student WHERE ID = '"+arg1+"'");
    qry6->exec();
    qry6->next();
    model6->setQuery(std::move(*qry6));
    instConn.connClose();
    QString nameID = model6->record(0).value("name").toString();
    ui->stdName->setText(nameID);
}


void instructor::on_registerButton_clicked()
{
    QString courseID, secID, semesterID, yearID, stdID;
    courseID = ui->coursesComboBox2->currentText();
    secID = ui->secIdComboBox->currentText();
    semesterID = ui->semesterComboBox2->currentText();
    yearID = ui->yearComboBox2->currentText();
    stdID = ui->studentIdComboBox->currentText();
    instructorLogin instConn;
    //update query
    instConn.connOpen();
    QSqlQuery qry1;
    qry1.prepare("INSERT INTO takes(ID, course_id, sec_id, semester, year) VALUES ('"+stdID+"', '"+courseID+"', '"+secID+"', '"+semesterID+"', '"+yearID+"')");

    if(qry1.exec()){
        QMessageBox::information(this, tr("Edit"), tr("Updated"));
    }
    else{
        QMessageBox::critical(this, tr("error::"), qry1.lastError().text());
    }
    instConn.connClose();
    //*Fill studentInfo*//
    //get course department
    QSqlQueryModel *model4 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry4 = new QSqlQuery(instConn.mydb);
    qry4->prepare("SELECT dept_name FROM course WHERE course_id = '"+courseID+"'");
    qry4->exec();
    qry4->next();
    model4->setQuery(std::move(*qry4));
    instConn.connClose();
    QString deptID = model4->record(0).value("dept_name").toString();
    qDebug() << deptID;

    //find students in the department that are no registered to the course
    QSqlQueryModel *model5 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry5 = new QSqlQuery(instConn.mydb);
    qry5->prepare("SELECT ID FROM student WHERE dept_name = '"+deptID+"' AND ID not in (SELECT DISTINCT ID FROM takes WHERE course_id = '"+courseID+"' AND semester = '"+semesterID+"' AND year = '"+yearID+"')");
    qry5->exec();
    qry5->next();
    model5->setQuery(std::move(*qry5));
    instConn.connClose();
    ui->studentIdComboBox->setModel(model5);

    //fill student name
    QSqlQueryModel *model6 = new QSqlQueryModel();
    instConn.connOpen();
    QSqlQuery *qry6 = new QSqlQuery(instConn.mydb);
    qry6->prepare("SELECT name FROM student WHERE ID = '"+stdID+"'");
    qry6->exec();
    qry6->next();
    model6->setQuery(std::move(*qry6));
    instConn.connClose();
    QString nameID = model6->record(0).value("name").toString();
    ui->stdName->setText(nameID);
}


void instructor::on_logOutButton_clicked()
{
    MainWindow *main = new MainWindow;
    this->hide();
    main->show();
}

