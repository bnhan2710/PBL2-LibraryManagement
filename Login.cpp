#include "Login.h"
#include "ui_login.h"
#include <QMessageBox>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>

Login::Login(QMainWindow *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    getMainScreen();

    QPixmap usernameLogo(":/resources/img/user.png");
    QPixmap passwordLogo(":/resources/img/password.png");
    QPixmap confirmPassLogo(":/resources/img/confirmPasword.png");
    QPixmap emailLogo(":/resources/img/mail.png");
    QPixmap LogoLogin(":/resources/img/book.png");
    QPixmap BgBelow(":/resources/img/Background_1.jpg");
    ui->username_1->setPixmap( usernameLogo.scaled( ui->username_1->width(), ui->username_1->height(),
                                                Qt::KeepAspectRatio, Qt::SmoothTransformation ));
    ui->password_1->setPixmap( passwordLogo.scaled( ui->password_1->width(), ui->password_1->height(),
                                                Qt::KeepAspectRatio, Qt::SmoothTransformation ));
    ui->Logo_1->setPixmap( LogoLogin.scaled( ui->Logo_1->width(), ui->Logo_1->height(),
                                                Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
    ui->BgBelow_1->setPixmap( BgBelow.scaled( ui->BgBelow_1->width(), ui->BgBelow_1->height(),
                                                Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
    ui->userLine_1->setPlaceholderText("Enter username");
    ui->passLine_1->setPlaceholderText("Enter password");
    ui->passLine_1->setEchoMode(QLineEdit::Password);

    ui->email->setPixmap( emailLogo.scaled( ui->email->width(), ui->email->height(),
                                                  Qt::KeepAspectRatio, Qt::SmoothTransformation ));
    ui->username_2->setPixmap( usernameLogo.scaled( ui->username_2->width(), ui->username_2->height(),
                                                  Qt::KeepAspectRatio, Qt::SmoothTransformation ));
    ui->password_2->setPixmap( passwordLogo.scaled( ui->password_2->width(), ui->password_2->height(),
                                                  Qt::KeepAspectRatio, Qt::SmoothTransformation ));
    ui->confirmPass->setPixmap( confirmPassLogo.scaled( ui->confirmPass->width(), ui->confirmPass->height(),
                                                  Qt::KeepAspectRatio, Qt::SmoothTransformation ));
    ui->Logo_2->setPixmap( LogoLogin.scaled( ui->Logo_2->width(), ui->Logo_2->height(),
                                           Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
    ui->BgBelow_2->setPixmap( BgBelow.scaled( ui->BgBelow_2->width(), ui->BgBelow_2->height(),
                                            Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
    ui->emailLine->setPlaceholderText("Enter email");
    ui->userLine_2->setPlaceholderText("Enter username");
    ui->passLine_2->setPlaceholderText("Enter password");
    ui->confimPassLine->setPlaceholderText("Re-Enter password");
    ui->passLine_2->setEchoMode(QLineEdit::Password);
    ui->confimPassLine->setEchoMode(QLineEdit::Password);

    QObject::connect( ui->LoginButton_1, &QPushButton::clicked, this, &Login::validate );
    QObject::connect( ui->RegisterButton_1, &QPushButton::clicked, this, &Login::registerRedirect );
    QObject::connect( ui->LoginButton_2, &QPushButton::clicked, this, &Login::loginRedirect );
}

void Login::registerRedirect() {
    ui->stackedWidget->setCurrentIndex(1);
}

void Login::loginRedirect() {
    ui->stackedWidget->setCurrentIndex(0);
}

void Login::getMainScreen() {

    mainScreen = QApplication::primaryScreen();
}

void Login::addTab() {
    hide();
}

void Login::showAlert( const QString AlertInformation ) {
    QMessageBox::information( this, "Login Alert", AlertInformation );
}

void Login::validate() {
    QString username = ui->userLine_1->text();
    QString password = ui->passLine_1->text();

    if ( username == "ADMIN" && password == "ADMIN" ) {
        showAlert("Login successful" );
    } else {
        showAlert("Login Fail");
    }

}

Login::~Login()
{
    delete ui;
}


