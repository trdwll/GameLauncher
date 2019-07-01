#ifndef USER_H
#define USER_H

#include <QObject>

struct SUserData
{
    QString Username;
    QString Password;
};

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr/*, const QString& Username = "", const QString& Password = ""*/);
    ~User();

    /**
     * @brief Login the user
     * @param UserData The data ie the user data that you want to supply
     */
    void Login(const SUserData& UserData);

	inline QString GetUsername() const { return m_Username; }

	inline bool IsLoggedin() const { return m_bIsLoggedIn; }
	inline bool LoginFileExists() const { return false; }

private:

	const QString m_LoginAPIRequestTokenURL = "http://localhost:8000/api/login/request-token/"; // Requires username and password
	const QString m_LoginAPIURL = "http://localhost:8000/api/login/"; // Requires the token from the url above

    QString m_Username;
	QString m_AuthToken;

    bool m_bIsLoggedIn = false;

	void RequestToken(const QString& Username, const QString& Password);
	void LoginUser(const QString& AuthToken);
signals:

public slots:
};

#endif // USER_H
