#ifndef USER_H
#define USER_H

#include <QObject>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QObject *parent = nullptr, const QString& Username = "", const QString& Password = "");
    ~User();

    /**
     * @brief Login the user
     * @return True if user was logged in else false
     */
    bool Login();

    QString GetUsername() const { return m_Username; }

    bool IsLoggedin() const { return m_bIsLoggedIn; }

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

signals:

public slots:
};

#endif // USER_H
