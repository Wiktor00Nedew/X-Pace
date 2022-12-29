//
// Created by Wiktor on 07.12.2022.
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


class LoginForm : public QWidget{
Q_OBJECT
public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

    void startLoading();
    void stopLoading();
    void setError(const std::string& key);



private:
    // layouts
    QVBoxLayout *mainLayout_;

    Title *title_;
    QLabel *loginLabel_;
    QLineEdit *loginBox_;
    QLabel *passwordLabel_;
    PasswordBox *passwordBox_;
    QPushButton *loginButton_;
    ClickableLabel *registerRedirect_;
    LoadingIndicator *loadingIndicator_;
    ErrorLabel *errorLabel_;

    // methods

    void createComponents();
    void setStyling();
    void connectSignals();

signals:
    void loggingIn(std::string login, std::string password);
    void changingToRegister();
};
