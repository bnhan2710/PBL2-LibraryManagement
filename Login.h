#ifndef LOGIN_H
#define LOGIN_H
#include <QMainWindow>
#include <QApplication>
#include <QMessageBox>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QFile>
#include <QTextStream>
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
    void getMainScreen(void);
signals:
public slots:
    void loginRedirect( void );
    void registerRedirect( void );
    void validate( void );
    void addTab( void );
    void registerToApp( void );
    void loginToApp( void );
private:
    Ui::Login *ui;
    QScreen *mainScreen;

};

#endif // LOGIN_H
