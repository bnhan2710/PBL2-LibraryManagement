#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QApplication>
#include "learnqt.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QMainWindow
{
    Q_OBJECT
public:
    Login(QMainWindow *parent = nullptr);
    ~Login();

    void showAlert( const QString );
    void getMainScreen();
signals:
public slots:
    void loginRedirect( void );
    void registerRedirect( void );
    void validate( void );
    void addTab( void );

private:
    Ui::Login *ui;
    QScreen *mainScreen;
    LearnQt *learnqt;

};

#endif // LOGIN_H
