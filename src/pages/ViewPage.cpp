//
// Created by Wiktor on 07.01.2023.
//

#include "ViewPage.h"

ViewPage::ViewPage(QWidget *parent) {

}

ViewPage::~ViewPage() {

}

void ViewPage::createComponents() {
    mainLayout_ = new QVBoxLayout();

    markdownView_ = new QTextEdit();
    saveButton_ = new QPushButton();
}

void ViewPage::setStyling() {

}

void ViewPage::connectSignals() {

}
