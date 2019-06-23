#include "user.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QHttpPart>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>


User::User(QObject *parent/*, const QString& Username, const QString& Password*/) :
    QObject(parent)/*,
    m_Username(Username),
    m_Password(Password)*/
{

}

User::~User()
{

}

bool User::Login()
{
    return LoginUser(m_Username, m_Password);
}

bool User::Login(const SUserData &UserData)
{
    SetUserData(UserData);
    return LoginUser(UserData.Username, UserData.Password);
}

bool User::LoginUser(const QString &Username, const QString &Password)
{
    qDebug() << "1: " << m_bIsLoggedIn;

    QNetworkAccessManager* const manager = new QNetworkAccessManager(this);

    QUrl url(m_LoginAPIURL);
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // The current method of validation of the user is insecure and shouldn't be used in production
    // we're not hashing the password when we send it to the API
    QUrlQuery params;
    params.addQueryItem("username", Username);
    params.addQueryItem("password", Password);

    connect(manager, &QNetworkAccessManager::finished, this,
        [=](QNetworkReply* reply)
        {
            QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();
            m_bIsLoggedIn = jsonObject["loggedin"].toBool();


            qDebug() << "2:" << m_bIsLoggedIn;
        }
    );

    manager->post(request, params.query().toUtf8());

    if (m_bIsLoggedIn)
    {
        // TODO: Create a config file on the client's machine with whatever details to keep the client signed in
    }

    qDebug() << "3: " << m_bIsLoggedIn;
    return m_bIsLoggedIn;
}

QString User::HashPassword(const QString &Password)
{
    // https://stackoverflow.com/questions/37763396/getting-sha1-hash-from-qstring
    return QString("%1").arg(QString(QCryptographicHash::hash(Password.toUtf8(), QCryptographicHash::Sha1).toHex()));
}

