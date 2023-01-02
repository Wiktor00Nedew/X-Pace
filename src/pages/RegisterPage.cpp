//
// Created by Wiktor on 27.12.2022.
//

#include "RegisterPage.h"
#include "../api/Api.h"
#include "../utilities/StringManager.h"

void RegisterPage::onResize() {
    mainLayout_->setContentsMargins((int)(0.3 * width()), (int)(0.3 * height()), (int)(0.3 * width()), (int)(0.3 * height()));
}

RegisterPage::RegisterPage(QWidget *parent) {
    createComponents();
    connectSignals();
    setStyling();
    setLayout(mainLayout_);
}

RegisterPage::~RegisterPage() {

}

void RegisterPage::createComponents() {
    mainLayout_ = new QGridLayout();
    registerForm_ = new RegisterForm();
    mainLayout_->addWidget(registerForm_, 0, 0);
}

void RegisterPage::setStyling() {
    mainLayout_->setContentsMargins((int)(0.3 * width()), (int)(0.3 * height()), (int)(0.3 * width()), (int)(0.3 * height()));
}

void RegisterPage::connectSignals() {
    connect(registerForm_, &RegisterForm::registering, this, &RegisterPage::onRegister);
    connect(registerForm_, &RegisterForm::changingToLogin, this, [=](){
        emit changingToLogin();
    });
}

void RegisterPage::onRegister(std::string username, std::string email, std::string password) {
    registerForm_->startLoading();
    StringManager::get().trim(username);
    StringManager::get().trim(email);

    if (username.empty()){
        registerForm_->stopLoading();
        registerForm_->setError("NO_USERNAME");
        return;
    }
    if (email.empty()){
        registerForm_->stopLoading();
        registerForm_->setError("NO_EMAIL");
        return;
    }
    if (password.empty()){
        registerForm_->stopLoading();
        registerForm_->setError("NO_PASSWORD");
        return;
    }

    auto apiResponse = Api::get().apiUserRegister(username, email, password);

    if (apiResponse.type == ApiMessage::Error){
        registerForm_->stopLoading();
        registerForm_->setError(apiResponse.data["key"]);
        return;
    }
    //qDebug() << "ahoy";

    registerForm_->setError("NO_ERROR");

    emit changingToLogin();

    // TODO add popup, successful register
    registerForm_->clearBoxes();
    registerForm_->stopLoading();

}
