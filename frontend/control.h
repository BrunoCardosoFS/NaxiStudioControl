#ifndef CONTROL_H
#define CONTROL_H

#include <QMainWindow>
#include <QSettings>
#include "../backend/authmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Control;
}
QT_END_NAMESPACE

class Control : public QMainWindow
{
    Q_OBJECT

public:
    Control(QWidget *parent = nullptr);
    ~Control();

private slots:
    void on_btnLogin_clicked();
    void on_btnLogout_clicked();

private:
    Ui::Control *ui;

    AuthManager *authManager = new AuthManager(this);
    QSettings *settings = new QSettings("NaxiStudio", "NaxiStudio Control");

private slots:
    void onLoginFinished(const bool success, const QString error);
    void on_linePassword_returnPressed();
    void on_lineUser_returnPressed();
    void on_btnConfigServer_clicked();
    void on_btnConfigBack_clicked();
};
#endif // CONTROL_H
