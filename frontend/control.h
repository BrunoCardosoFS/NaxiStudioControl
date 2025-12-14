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

private:
    Ui::Control *ui;
};
#endif // CONTROL_H
