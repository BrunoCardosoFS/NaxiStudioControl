#ifndef CONTROL_H
#define CONTROL_H

#include <QMainWindow>

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
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Control *ui;
};
#endif // CONTROL_H
