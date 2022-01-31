#include "loginstudent.h"
#include "ui_loginstudent.h"

LoginStudent::LoginStudent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginStudent)
{
    ui->setupUi(this);

    if(!connOpen()){
        ui->connectionStatus->setText("Failed to open the database");
    }
    else{
        ui->connectionStatus->setText("Connected...");
    }
}

LoginStudent::~LoginStudent()
{
    delete ui;
}

bool LoginStudent::connOpen(){
    uni_db = QSqlDatabase::addDatabase("QSQLITE");
    uni_db.setDatabaseName("unidb.db");

    if(!uni_db.open()){
        qDebug() <<("Failed to open the database");
        return false;
    }
    else{
        qDebug() <<("Connected...");
        return true;
    }
}

void LoginStudent::connClose(){
    uni_db.close();
    uni_db.removeDatabase(QSqlDatabase::defaultConnection);
}
void LoginStudent::on_signInButton_clicked()
{
    QString username, pwd;
    username = ui->id_lineEdit->text();
    pwd = ui->pwd_lineEdit->text();

    if(!connOpen()){
        qDebug() << "Failed to open the database";
        return;
    }

    connOpen();
    QSqlQuery qry;
    qry.prepare("select * from student where ID = '"+username+"' and password = '"+pwd+"' ");
    if(qry.exec()){
        int count = 0;
        while(qry.next()){
            count++;
        }
        if(count == 1){
            ui->connectionStatus->setText("Acces Granted..");
            connClose();
            this->hide();
            Student std;
           // std.resize(this->size());
            std.user = username;
            std.setModal(true);
            std.setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint);
            std.exec();
        }
        if(count > 1){
            ui->connectionStatus->setText("Duplicated entry..");
        }
        if(count < 1){
            ui->connectionStatus->setText("Invalid username or password..");
            QMessageBox::critical(this, tr("Invalid"), tr("Try again"));
        }
    }
}


void LoginStudent::on_homeButton_clicked()
{
    MainWindow *mainwin = new MainWindow();
    this->hide();
    mainwin->show();
}

