//
// Created by Wiktor on 23.11.2022.
//

#include "LoginPage.h"
#include "../api/Api.h"
#include "../utilities/StringManager.h"

LoginPage::LoginPage(QWidget *parent) {
    createComponents();
    connectSignals();
    setStyling();
    setLayout(mainLayout_);
}

LoginPage::~LoginPage() {

}

void LoginPage::createComponents() {
    mainLayout_ = new QGridLayout();
    loginForm_ = new LoginForm();
    mainLayout_->addWidget(loginForm_, 0, 0);
}

void LoginPage::setStyling() {
    mainLayout_->setContentsMargins((int)(0.3 * width()), (int)(0.3 * height()), (int)(0.3 * width()), (int)(0.3 * height()));
}

void LoginPage::connectSignals() {
    connect(loginForm_, &LoginForm::loggingIn, this, &LoginPage::onLogin);
    connect(loginForm_, &LoginForm::changingToRegister, this, [=](){
        //qDebug() << "caught by connect 2";
        emit changingToRegister();
    });
}

void LoginPage::onLogin(std::string login, std::string password) {
    loginForm_->startLoading();
    StringManager::get().trim(login);

    if (login.empty()){
        loginForm_->stopLoading();
        loginForm_->setError("NO_EMAIL");
        return;
    }
    if (password.empty()){
        loginForm_->stopLoading();
        loginForm_->setError("NO_PASSWORD");
        return;
    }

    auto apiResponse = Api::get().apiUserLogin(login, password);
    //qDebug() << "test1";
    if (apiResponse.type == ApiMessage::Error){
        loginForm_->stopLoading();
        loginForm_->setError(apiResponse.data["key"]);
        return;
    }
    //qDebug() << "here";
    Api::get().setApiToken(apiResponse.data["token"]["id"]);

    loginForm_->setError("NO_ERROR");

    emit changingToApplication();
    emit logedIn();

    loginForm_->clearBoxes();
    loginForm_->stopLoading();
}

void LoginPage::onResize() {
    mainLayout_->setContentsMargins((int)(0.3 * width()), (int)(0.3 * height()), (int)(0.3 * width()), (int)(0.3 * height()));
}

