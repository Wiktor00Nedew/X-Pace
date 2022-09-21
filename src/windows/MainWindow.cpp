//
// Created by wiktor on 9/21/22.
//

#include "windows/MainWindow.h"

MainWindow::MainWindow(QWidget *parent) {
    mainLayout_ = new QGridLayout();

    setLayout(mainLayout_);
    resize(800, 600);
}

MainWindow::~MainWindow() {
   delete mainLayout_;
}
