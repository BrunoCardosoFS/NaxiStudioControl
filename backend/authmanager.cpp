#include "authmanager.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QUrl>

AuthManager::AuthManager(QObject *parent):QObject{parent}{

}

void AuthManager::setBaseUrl(QString baseUrl){
    m_baseUrl = baseUrl+"/api/auth";
}

void AuthManager::login(const QString &user, const QString &password){
    if(user == "" || password == ""){
        emit loginFinished(false, "Os campos de usuário e senha são obrigatórios.");
        return;
    }

    if(m_baseUrl == ""){
        emit loginFinished(false, "Antes de fazer login, configure o servidor.");
        return;
    }

    QUrl url(m_baseUrl+"/login");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setHeader(QNetworkRequest::UserAgentHeader, "NaxiStudio Control (https://naxistudio.pages.dev/modulos/control)");

    QJsonObject json;
    json["user"] = user;
    json["password"] = password;

    QJsonDocument doc(json);
    QByteArray data = doc.toJson();

    QNetworkReply *loginReply = m_manager->post(request, data);

    connect(loginReply, &QNetworkReply::finished, this, &AuthManager::onLoginReplyFinished);
}

void AuthManager::onLoginReplyFinished(){
    QNetworkReply *loginReply = qobject_cast<QNetworkReply*>(sender());
    if (!loginReply) return;

    if(loginReply->error() == QNetworkReply::NoError){
        QByteArray responseData = loginReply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObj = jsonDoc.object();

        if (jsonObj.contains("token")) {
            m_token = jsonObj["token"].toString();
            m_user = jsonObj["user"].toString();
            m_name = jsonObj["name"].toString();
            m_email = jsonObj["email"].toString();
            m_type = jsonObj["type"].toInt();
            emit loginFinished();
            return;
        }

        emit loginFinished(false, "Resposta inválida do servidor: Token não encontrado.");
    }else if (loginReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 401) {
        emit loginFinished(false, "Usuário ou senha incorretos.");

    }else if(loginReply->error() == QNetworkReply::ConnectionRefusedError){
        emit loginFinished(false, "Erro de conexão com o servidor.");

    }else{
        emit loginFinished(false, loginReply->errorString());
    }

    loginReply->deleteLater();

}

UserData AuthManager::getUser(){
    return {this->m_token, this->m_user, this->m_name, this->m_email, this->m_type};
}

void AuthManager::logout(){
    this->m_token.fill('0');
    this->m_token.clear();

    this->m_user.fill('0');
    this->m_user.clear();

    this->m_name.fill('0');
    this->m_name.clear();

    this->m_email.fill('0');
    this->m_email.clear();

    this->m_type = -1;
}

QString AuthManager::getToken() const {
    return m_token;
}




