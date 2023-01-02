//
// Created by Wiktor on 13.04.2022.
//

#include "DropdownButton.h"

DropdownButton::DropdownButton(QWidget *parent){
    mainLayout_ = new QGridLayout();
    addActions();
    addMenus();
    addToolButtons();
    setStyling();

    setLayout(mainLayout_);
}

void DropdownButton::addActions() {
    myTeamsAction_ = new QAction("Moje zespoły", this);
    mySettingsAction_ = new QAction("Ustawienia", this);
    logoutAction_ = new QAction("Wyloguj", this);


    connect(myTeamsAction_, &QAction::triggered, this, [=](){
        emit myTeamsOpened();
    });
    connect(mySettingsAction_, &QAction::triggered, this, [=](){
        emit mySettingsOpened();
    });
    connect(logoutAction_, &QAction::triggered, this, [=](){
        emit logedOut();
    });
}

void DropdownButton::setStyling() {

}

void DropdownButton::addMenus() {
    userMenu_ = new QMenu();
    userMenu_->addAction(myTeamsAction_);
    userMenu_->addAction(mySettingsAction_);
    userMenu_->addAction(logoutAction_);
}

void DropdownButton::addToolButtons() {
    dropdownButton_ = new Button();
    dropdownButton_->setMenu(userMenu_);

    mainLayout_->addWidget(dropdownButton_, 0, 0);
}

void DropdownButton::setUsername(const QString &name) {
    dropdownButton_->setText(name);
}

DropdownButton::~DropdownButton() {
    delete mainLayout_;
    delete dropdownButton_;
    delete userMenu_;
    delete logoutAction_;
    delete mySettingsAction_;
}
