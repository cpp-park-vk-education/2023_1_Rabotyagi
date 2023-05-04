#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QSettings>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    registration_window = new RegistrationWindow(this);

    // Connect the showRegistrationWindow slot to the registerButton clicked signal
    connect(ui->registrationButton, &QPushButton::clicked, this, &LoginWindow::openRegistrationWindow);

    // Connect the goBack signal from the registration window to the show() slot of the login window
    connect(registration_window, &RegistrationWindow::goBack, this, &LoginWindow::show);

    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::login);
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete registration_window;
}


void LoginWindow::login()
{
//     QNetworkAccessManager *manager = new QNetworkAccessManager(this);
//     QUrl url("http://example.com/login");
//     QNetworkRequest request(url);
//     request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//     QJsonObject json;
//     json["username"] = ui->usernameEdit->text();
//     json["password"] = ui->passwordEdit->text();
//     QJsonDocument doc(json);
//     QByteArray data = doc.toJson();


// //    Этот код отправляет POST-запрос на сервер с использованием QNetworkAccessManager и блокирует выполнение программы до тех пор,
// //    пока ответ от сервера не будет получен. Закоментим его чтобы захардкодить ответ сервера для тестов.
//     QNetworkReply *reply = manager->post(request, data);
//     while (!reply->isFinished()) {
//         qApp->processEvents();
//     }

//     if (reply->error() == QNetworkReply::NoError) {
//         QByteArray response = reply->readAll();
//         QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
//         QString accessToken = jsonDoc["access_token"].toString();
//         QString refreshToken = jsonDoc["refresh_token"].toString();
//         saveTokens(accessToken, refreshToken);
//         accept();
//     } else {
//         QMessageBox::warning(this, tr("Login Failed"), tr("Invalid username or password."));
//     }

//     reply->deleteLater();
}

// // записываем токены в файл
void LoginWindow::saveTokens(const QString &accessToken, const QString &refreshToken)
{
//     QJsonObject json;
//     json["access_token"] = accessToken;
//     json["refresh_token"] = refreshToken;
//     QJsonDocument doc(json);

//     QFile file("tokens.json");
//     if (file.open(QIODevice::WriteOnly)) {
//         file.write(doc.toJson());
//         file.close();
//     }
}

void LoginWindow::openRegistrationWindow()
{
//     RegistrationWindow registrationWindow;
//     if (registrationWindow.exec() == QDialog::Accepted) {
//         accept();
//     }
}
