#include "control.h"
#include "./ui_control.h"

#include <QDebug>

Control::Control(QWidget *parent):QMainWindow(parent), ui(new Ui::Control){
    ui->setupUi(this);

    if(this->settings->contains("lastUser")){
        this->ui->lineUser->setText(settings->value("lastUser").toString());
        this->ui->linePassword->setFocus();
    }

    if(this->settings->contains("serverUrl")){
        this->ui->labelServer->setText(settings->value("serverUrl").toString());
        this->authManager->setBaseUrl(settings->value("serverUrl").toString());
    }

    connect(this->authManager, &AuthManager::loginFinished, this, &Control::onLoginFinished);

    this->ui->stackedWidget->setCurrentIndex(0);
    this->ui->labelLoginMessage->hide();
}

Control::~Control(){
    delete ui;
}

void Control::onLoginFinished(const bool success, const QString error){
    this->ui->btnLogin->setDisabled(false);
    this->ui->btnLogin->setText("Entrar");

    if(success){
        this->settings->setValue("lastUser", this->authManager->getUser().user);

        qInfo() << "token: " << this->authManager->getUser().token;
        qInfo() << "user: " << this->authManager->getUser().user;
        qInfo() << "name: " << this->authManager->getUser().name;
        qInfo() << "email: " << this->authManager->getUser().email;
        qInfo() << "type: " << this->authManager->getUser().type;

        this->ui->labelTopNameUser->setText(this->authManager->getUser().name);
        this->ui->stackedWidget->setCurrentIndex(2);
        this->ui->linePassword->clear();
        this->ui->labelLoginMessage->hide();
        return;
    }

    this->settings->remove("lastUser");
    this->ui->labelLoginMessage->setText(error);
    this->ui->labelLoginMessage->show();
    return;
}

void Control::on_btnLogin_clicked(){
    this->ui->btnLogin->setDisabled(true);
    this->ui->btnLogin->setText("Entrando...");
    this->authManager->login(this->ui->lineUser->text(), this->ui->linePassword->text());
}


void Control::on_btnLogout_clicked(){
    this->authManager->logout();
    this->ui->stackedWidget->setCurrentIndex(0);
}

void Control::on_lineUser_returnPressed(){
    this->ui->linePassword->setFocus();
}

void Control::on_linePassword_returnPressed(){
    this->on_btnLogin_clicked();
}

void Control::on_btnConfigServer_clicked(){
    this->ui->stackedWidget->setCurrentIndex(1);
}


void Control::on_btnConfigBack_clicked(){
    this->ui->stackedWidget->setCurrentIndex(0);
}

