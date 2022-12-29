//
// Created by Wiktor on 29.12.2022.
//

#include "TopBar.h"

TopBar::TopBar(QWidget *parent) {
    createComponents();
    setStyling();
    connectSignals();

    setLayout(mainLayout_);
}

TopBar::~TopBar() {

}

void TopBar::createComponents() {
    mainLayout_ = new QHBoxLayout();

    userMenu_ = new DropdownButton();
    teamMenu_ = new QComboBox();

    mainLayout_->addStretch();
    mainLayout_->addWidget(teamMenu_);
    mainLayout_->addSpacing(20);
    mainLayout_->addWidget(userMenu_);
    mainLayout_->addSpacing(10);
}

void TopBar::connectSignals() {
    connect(userMenu_, &DropdownButton::logedOut, this, [=](){
        emit logedOut();
    });
}

void TopBar::setStyling() {
    setFixedHeight(60);
    setAttribute(Qt::WA_StyledBackground);
}

void TopBar::setUsername(const QString &name) {
    userMenu_->setUsername(name);
}
