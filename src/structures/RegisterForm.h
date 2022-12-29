//
// Created by Wiktor on 27.12.2022.
//

#pragma once
#include <QLabel>
#include "../components/PasswordBox.h"
#include "../components/LoadingIndicator.h"
#include "../components/ErrorLabel.h"
#include "../components/Title.h"
#include "../components/ClickableLabel.h"
#include <QVBoxLayout>
#include <QPushButton>

class RegisterForm : public QWidget {
Q_OBJECT
public:
    explicit RegisterForm(QWidget *parent = nullptr);
    ~RegisterForm();

    void startLoading();
    void stopLoading();
    void setError(const std::string& key);



private:
    // layouts
    QVBoxLayout *mainLayout_;

    Title *title_;
    QLabel *usernameLabel_;
    QLineEdit *usernameBox_;
    QLabel *emailLabel_;
    QLineEdit *emailBox_;
    QLabel *passwordLabel_;
    PasswordBox *passwordBox_;
    QPushButton *registerButton_;
    ClickableLabel *loginRedirect_;
    LoadingIndicator *loadingIndicator_;
    ErrorLabel *errorLabel_;

    // methods

    void createComponents();
    void setStyling();
    void connectSignals();

signals:
    void registering(std::string username, std::string email, std::string password);
    void changingToLogin();
};
