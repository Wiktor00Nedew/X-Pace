//
// Created by wiktor on 9/21/22.
//

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) {
    mainLayout_ = new QGridLayout();

    createComponents();
    connectSignals();
    setStyling();

    setLayout(mainLayout_);
    resize(800, 600);
    setWindowFlags(Qt::Window | Qt::BypassWindowManagerHint); // think whether we use custom titlebar or not
}

MainWindow::~MainWindow() {
    delete testButton_;
    delete testLineEdit_;
    delete testPasswordBox_;
    delete titleBar_;
    delete mainStack_;
    delete mainLayout_;
}

void MainWindow::createComponents() {
    mainStack_ = new QStackedWidget();

    /*titleBar_ = new TitleBar(this);
    testButton_ = new QPushButton("Click me!");
    testPasswordBox_ = new PasswordBox();
    testLineEdit_ = new QLineEdit();
    testLabel_ = new QLabel("Hello world");
    mainLayout_->addWidget(titleBar_, 0, 0);
    mainLayout_->addWidget(testButton_, 1, 0);
    mainLayout_->addWidget(testLineEdit_, 2, 0);
    mainLayout_->addWidget(testPasswordBox_, 3, 0);
    mainLayout_->addWidget(testLabel_, 4, 0);
     */

    createPages();

    mainStack_->addWidget(applicationPage_);
    mainStack_->addWidget(loginPage_);
    mainStack_->addWidget(registerPage_);
    mainLayout_->addWidget(mainStack_);

    mainStack_->setCurrentIndex(mainStack_->indexOf(loginPage_));
}

void MainWindow::createPages() {
    loginPage_ = new LoginPage();
    registerPage_ = new RegisterPage();
    applicationPage_ = new ApplicationPage();
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    loginPage_->onResize();
}

void MainWindow::connectSignals() {
    connect(loginPage_, &LoginPage::changingToRegister, this, &MainWindow::changedToRegister);
    connect(registerPage_, &RegisterPage::changingToLogin, this, &MainWindow::changedToLogin);
    connect(applicationPage_, &ApplicationPage::logedOut, this, &MainWindow::changedToLogin);
    connect(loginPage_, &LoginPage::changingToApplication, this, &MainWindow::changedToApplication);
    connect(loginPage_, &LoginPage::logedIn, applicationPage_, &ApplicationPage::onLogin);

}

void MainWindow::changedToRegister() {
    //qDebug() << "caught by connect 3";
    //qDebug() << mainStack_->indexOf(registerPage_);
    mainStack_->setCurrentIndex(mainStack_->indexOf(registerPage_));
}

void MainWindow::changedToLogin() {
    mainStack_->setCurrentIndex(mainStack_->indexOf(loginPage_));
}

void MainWindow::setStyling() {
    mainLayout_->setSpacing(0);
    mainLayout_->setContentsMargins(0, 0, 0, 0);
}

void MainWindow::changedToApplication() {
    mainStack_->setCurrentIndex(mainStack_->indexOf(applicationPage_));
}

