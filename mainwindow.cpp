#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginstudent.h"
#include"logincoordinator.h"
#include "instructorlogin.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_studentButton_clicked()
{
    LoginStudent *loginPage = new LoginStudent();
    this-> hide();
    loginPage->show();
}


void MainWindow::on_coordinatorButton_clicked()
{
    LoginCoordinator *loginPage = new LoginCoordinator();
    this->hide();
    loginPage->show();
}


void MainWindow::on_pushButton_6_clicked()
{
    instructorLogin *loginPage = new instructorLogin();
    this->hide();
    loginPage->show();
}

