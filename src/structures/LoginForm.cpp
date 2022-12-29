//
// Created by Wiktor on 07.12.2022.
//

#include "LoginForm.h"

LoginForm::LoginForm(QWidget *parent) {
    createComponents();
    connectSignals();
    setStyling();
    setLayout(mainLayout_);
}

LoginForm::~LoginForm() {
    delete loginLabel_;
    delete loginButton_;
    delete loginBox_;
    delete passwordBox_;
    delete passwordLabel_;
    delete loadingIndicator_;
    delete mainLayout_;
}

void LoginForm::setStyling() {
    title_->setText("Zaloguj się");
    loginLabel_->setText("Email");
    passwordLabel_->setText("Hasło");
    loginButton_->setText("Zaloguj");
    registerRedirect_->setText("lub zarejestruj się");

    title_->setAlignment(Qt::AlignHCenter);
    loadingIndicator_->setAlignment(Qt::AlignHCenter);
    registerRedirect_->setAlignment(Qt::AlignHCenter);
}

void LoginForm::createComponents() {
    title_ = new Title();
    loginLabel_ = new QLabel();
    loginBox_ = new QLineEdit();
    passwordLabel_ = new QLabel();
    passwordBox_ = new PasswordBox();

    loginButton_ = new QPushButton();
    registerRedirect_ = new ClickableLabel();

    loadingIndicator_ = new LoadingIndicator();
    errorLabel_ = new ErrorLabel();

    mainLayout_ = new QVBoxLayout();

    mainLayout_->addStretch();
    mainLayout_->addWidget(title_);
    mainLayout_->addWidget(loginLabel_);
    mainLayout_->addWidget(loginBox_);
    mainLayout_->addWidget(passwordLabel_);
    mainLayout_->addWidget(passwordBox_);
    mainLayout_->addWidget(loginButton_);
    mainLayout_->addWidget(registerRedirect_);
    mainLayout_->addWidget(loadingIndicator_);
    mainLayout_->addWidget(errorLabel_);
    mainLayout_->addStretch();

}

void LoginForm::connectSignals() {
    connect(loginButton_, &QPushButton::clicked, this, [=](){
        emit loggingIn(loginBox_->text().toStdString(), passwordBox_->text().toStdString());
    });
    connect(loginBox_, &QLineEdit::returnPressed, loginButton_, &QPushButton::click);
    connect(passwordBox_, &QLineEdit::returnPressed, loginButton_, &QPushButton::click);
    connect(registerRedirect_, &ClickableLabel::clicked, this, [=](){
        //qDebug() << "caught by connect 1";
        emit changingToRegister();
    });
}

void LoginForm::startLoading() {
    loadingIndicator_->show();
}

void LoginForm::stopLoading() {
    loadingIndicator_->hide();
}

void LoginForm::setError(const std::string &key) {
    errorLabel_->setError(key);
}
