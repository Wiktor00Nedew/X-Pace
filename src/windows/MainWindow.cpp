//
// Created by wiktor on 9/21/22.
//

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) {
    mainLayout_ = new QGridLayout();

    createComponents();

    setLayout(mainLayout_);
    resize(800, 600);
}

MainWindow::~MainWindow() {
    delete testButton_;
    delete mainLayout_;
}

void MainWindow::createComponents() {
    testButton_ = new QPushButton();
    mainLayout_->addWidget(testButton_, 0, 0);
}
