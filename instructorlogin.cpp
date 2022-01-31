#include "instructorlogin.h"
#include "ui_instructorlogin.h"

instructorLogin::instructorLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::instructorLogin)
{
    ui->setupUi(this);
    if(!connOpen())
        ui->connectionStatus->setText("Failed to open database!!!");
    else
        ui->connectionStatus->setText("Connected to university database...");
}

instructorLogin::~instructorLogin()
{
    delete ui;
}




void instructorLogin::on_homeButton_clicked()
{
    //*******Go to home page**********//
    MainWindow *homepage = new MainWindow();
    this->hide();
    homepage->show();
}


void instructorLogin::on_signInButton_clicked()
{
    QString ID, password;
    //store user inputs
    ID = ui->idText->text();
    password = ui->passwordText->text();
    // ******************************* //
    if(!mydb.isOpen()) {
        qDebug() << "Failed to open the database";
        return;
    }

    connOpen();
    QSqlQuery qry;
    qry.prepare("select * from instructor where ID = '"+ID+"' and password = '"+password+"'");
    if(qry.exec()) {
        int count = 0;
        while(qry.next()) {
            count++;
        }
        if(count == 1) {

            ui->connectionStatus->setText("username and password correct");
            connClose(); //close connection
            this->hide(); //hide login window

            //*********start instructor window and hide login window**********//
            instructor *inst = new instructor;
            inst->userID = ID; //set userID to Id entered
            this->hide();
            inst->show();
        }

        if(count > 1)
            ui->connectionStatus->setText("username and password duplicated");
        if(count < 1)
            ui->connectionStatus->setText("username and password incorrect");
    }
}

