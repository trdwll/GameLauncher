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
#include <QEventLoop>


User::User(QObject *parent) :
    QObject(parent)
{

}

User::~User()
{

}

void User::Login(const SUserData &UserData)
{
	qDebug() << "Login: User is logged in: " << m_bIsLoggedIn;
	// TODO: Check if the auth file exists and if so then don't request the token and just login the user, if the auth fails then we should get the new token and login
	RequestToken(UserData.Username, UserData.Password);
}

void User::RequestToken(const QString& Username, const QString& Password)
{
	QNetworkAccessManager* manager = new QNetworkAccessManager();

	QNetworkRequest request(m_LoginAPIRequestTokenURL);

	request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

	QUrlQuery params;
	params.addQueryItem("username", Username);
	params.addQueryItem("password", Password);

	connect(manager, &QNetworkAccessManager::finished, this,
	    [=](QNetworkReply* reply)
	    {
			if (reply->error())
			{
				qDebug() << "ERROR (RequestToken):" << reply->errorString();
				return;
			}

	        QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();

			m_AuthToken = jsonObject["token"].toString();

			LoginUser(m_AuthToken);
			m_Username = Username;
	    }
	);

	manager->post(request, params.query().toUtf8());
}

void User::LoginUser(const QString& AuthToken)
{
    QNetworkAccessManager* manager = new QNetworkAccessManager();

    QNetworkRequest request(m_LoginAPIURL);

    connect(manager, &QNetworkAccessManager::finished, this,
        [=](QNetworkReply* reply)
        {
			if (reply->error())
			{
				qDebug() << "ERROR (LoginUser):" << reply->errorString();
				return;
			}

            QJsonObject jsonObject = QJsonDocument::fromJson(reply->readAll()).object();
            m_bIsLoggedIn = jsonObject["loggedin"].toBool();

			qDebug() << "LoginUser: User is logged in: " << m_bIsLoggedIn << " with the token: " << AuthToken;
        }
    );

	request.setRawHeader("Authorization", ("Token " + AuthToken).toLocal8Bit());
    manager->get(request);
}

