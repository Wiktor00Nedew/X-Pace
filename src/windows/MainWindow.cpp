//
// Created by wiktor on 9/21/22.
//

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) {
    mainLayout_ = new QGridLayout();

    createComponents();

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


    loginPage_ = new LoginPage();

    mainStack_->addWidget(loginPage_);
    mainLayout_->addWidget(mainStack_);
}

void MainWindow::createPages() {

}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    loginPage_->onResize();
}

