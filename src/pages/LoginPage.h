//
// Created by Wiktor on 23.11.2022.
//

#pragma once
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include "../components/PasswordBox.h"
#include "../structures/LoginForm.h"

class LoginPage : public QWidget{
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

    void createComponents();
    void setStyling();
    void connectSignals();
    void onResize();

private:
    QGridLayout *mainLayout_;
    LoginForm *loginForm_;


public slots:
    void onLogin(std::string login, std::string password);

signals:
    void logedIn();

};
