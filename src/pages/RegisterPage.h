//
// Created by Wiktor on 27.12.2022.
//

#pragma once
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QBoxLayout>
#include "../components/PasswordBox.h"
#include "../structures/RegisterForm.h"

class RegisterPage : public QWidget{
Q_OBJECT
public:
    explicit RegisterPage(QWidget *parent = nullptr);
    ~RegisterPage();

    void createComponents();
    void setStyling();
    void connectSignals();
    void onResize();

private:
    QGridLayout *mainLayout_;
    RegisterForm *registerForm_;


public slots:
    void onRegister(std::string username, std::string email, std::string password);

signals:
    void changingToLogin();

};
