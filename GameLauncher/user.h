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
     * @return True if user was logged in else false
     */
    bool Login();

    /**
     * @brief Login the user
     * @param UserData The data ie the user data that you want to supply
     * @return True if user was logged in else false
     */
    bool Login(const SUserData& UserData);

    QString GetUsername() const { return m_Username; }

    inline void SetUserData(const SUserData& UserData)
    {
        m_Username = UserData.Username;
        m_Password = UserData.Password;
    }

    bool IsLoggedin() const { return m_bIsLoggedIn; }
    bool LoginFileExists() const { return false; }

private:

    const QString m_LoginAPIURL = "http://localhost:8000/api/login/";

    QString m_Username;
    QString m_Password;

    bool m_bIsLoggedIn;

    /**
     * @brief Login the user with the specified details
     * @param Username  The username of the user
     * @param Password  The password for the user's account
     * @return True if user was logged in else false
     */
    bool LoginUser(const QString& Username, const QString& Password);

    /**
     * @brief Hash a string (password)
     * @param Password  The string that you want to hash
     * @return A hashed string
     */
    QString HashPassword(const QString& Password);
public:
    void Login2(const QString &Username, const QString &Password);
    void handleReply(class QNetworkReply *reply);
signals:

public slots:
};

#endif // USER_H
