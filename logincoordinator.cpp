#include "logincoordinator.h"
#include "ui_logincoordinator.h"

LoginCoordinator::LoginCoordinator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginCoordinator)
{
    ui->setupUi(this);

    if(!connOpen()){
        ui->connectionStatus->setText("Failed to open the database");
    }
    else{
        ui->connectionStatus->setText("Connected...");
    }
}

LoginCoordinator::~LoginCoordinator()
{
    delete ui;
}

bool LoginCoordinator::connOpen(){
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

void LoginCoordinator::connClose(){
    uni_db.close();
    uni_db.removeDatabase(QSqlDatabase::defaultConnection);
}
void LoginCoordinator::on_signInButton_clicked()
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
    qry.prepare("select * from coordinator where ID = '"+username+"' and password = '"+pwd+"' ");
    if(qry.exec()){
        int count = 0;
        while(qry.next()){
            count++;
        }
        if(count == 1){
            ui->connectionStatus->setText("Acces Granted..");
            connClose();
            this->hide();
            Coordinator crd;
            crd.setModal(true);
            crd.setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint);
            crd.exec();
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


void LoginCoordinator::on_homeButton_clicked()
{
    MainWindow *mainwin = new MainWindow();
    this->hide();
    mainwin->show();
}
