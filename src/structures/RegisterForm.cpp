//
// Created by Wiktor on 27.12.2022.
//

#include "RegisterForm.h"

RegisterForm::RegisterForm(QWidget *parent) {
    createComponents();
    connectSignals();
    setStyling();
    setLayout(mainLayout_);
}

RegisterForm::~RegisterForm() {
    delete usernameLabel_;
    delete emailBox_;
    delete emailLabel_;
    delete registerButton_;
    delete usernameBox_;
    delete passwordBox_;
    delete passwordLabel_;
    delete loadingIndicator_;
    delete mainLayout_;
}

void RegisterForm::setStyling() {
    title_->setText("Zarejestruj się");
    usernameLabel_->setText("Nazwa użytkownika");
    emailLabel_->setText("Email");
    passwordLabel_->setText("Hasło");
    registerButton_->setText("Zarejestruj się");
    loginRedirect_->setText("Lub zaloguj się");

    title_->setAlignment(Qt::AlignHCenter);
    loadingIndicator_->setAlignment(Qt::AlignHCenter);
    loginRedirect_->setAlignment(Qt::AlignHCenter);
}

void RegisterForm::createComponents() {
    title_ = new Title();
    usernameLabel_ = new QLabel();
    usernameBox_ = new QLineEdit();

    emailLabel_ = new QLabel();
    emailBox_ = new QLineEdit();

    passwordLabel_ = new QLabel();
    passwordBox_ = new PasswordBox();

    registerButton_ = new QPushButton();
    loginRedirect_ = new ClickableLabel();

    loadingIndicator_ = new LoadingIndicator();
    errorLabel_ = new ErrorLabel();

    mainLayout_ = new QVBoxLayout();

    mainLayout_->addStretch();
    mainLayout_->addWidget(title_);
    mainLayout_->addWidget(usernameLabel_);
    mainLayout_->addWidget(usernameBox_);
    mainLayout_->addWidget(emailLabel_);
    mainLayout_->addWidget(emailBox_);
    mainLayout_->addWidget(passwordLabel_);
    mainLayout_->addWidget(passwordBox_);
    mainLayout_->addWidget(registerButton_);
    mainLayout_->addWidget(loginRedirect_);
    mainLayout_->addWidget(loadingIndicator_);
    mainLayout_->addWidget(errorLabel_);
    mainLayout_->addStretch();

}

void RegisterForm::connectSignals() {
    connect(registerButton_, &QPushButton::clicked, this, [=](){
        emit registering(usernameBox_->text().toStdString(), emailBox_->text().toStdString(), passwordBox_->text().toStdString());
    });
    connect(usernameBox_, &QLineEdit::returnPressed, registerButton_, &QPushButton::click);
    connect(emailBox_, &QLineEdit::returnPressed, registerButton_, &QPushButton::click);
    connect(passwordBox_, &QLineEdit::returnPressed, registerButton_, &QPushButton::click);
    connect(loginRedirect_, &ClickableLabel::clicked, this, [=](){
        emit changingToLogin();
    });
}

void RegisterForm::startLoading() {
    loadingIndicator_->show();
}

void RegisterForm::stopLoading() {
    loadingIndicator_->hide();
}

void RegisterForm::setError(const std::string &key) {
    errorLabel_->setError(key);
}

void RegisterForm::clearBoxes() {
    usernameBox_->clear();
    passwordBox_->clear();
    emailBox_->clear();
}
