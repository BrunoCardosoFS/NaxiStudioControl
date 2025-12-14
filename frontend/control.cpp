#include "control.h"
#include "./ui_control.h"

Control::Control(QWidget *parent):QMainWindow(parent), ui(new Ui::Control){
    ui->setupUi(this);
    this->ui->stackedWidget->setCurrentIndex(0);
}

Control::~Control(){
    delete ui;
}

void Control::on_pushButton_clicked(){
    this->ui->stackedWidget->setCurrentIndex(1);
}


void Control::on_pushButton_5_clicked(){
    this->ui->stackedWidget->setCurrentIndex(0);
}

