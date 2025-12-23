#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

struct UserData {
    QString token;
    QString user;
    QString name;
    QString email;
    int type;
};

class AuthManager : public QObject
{
    Q_OBJECT
public:
    explicit AuthManager(QObject *parent = nullptr);

    void setBaseUrl(QString baseUrl);
    void login(const QString &user, const QString &password);
    void logout();

    QString getToken() const;
    UserData getUser();

    bool isAuthenticated() const;

signals:
    void loginFinished(const bool success = true, const QString error = nullptr);

    void loginSuccess();
    void loginFailed(const QString &errorMessage);

private slots:
    void onLoginReplyFinished();

private:
    QNetworkAccessManager *m_manager = new QNetworkAccessManager(this);
    QString m_baseUrl = "";

    QString m_token = "";
    QString m_user = "";
    QString m_name = "";
    QString m_email = "";
    int m_type = -1;
};

#endif // AUTHMANAGER_H
