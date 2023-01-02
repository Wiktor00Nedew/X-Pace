//
// Created by Wiktor on 01.01.2023.
//

#include "TeamListItemButtons.h"

TeamListItemButtons::TeamListItemButtons(QWidget *parent) {
    createComponents();
    setStyling();
    connectSignals();

    setLayout(mainLayout_);
}

TeamListItemButtons::~TeamListItemButtons() {

}

void TeamListItemButtons::createComponents() {
    mainLayout_ = new QHBoxLayout();

    // buttons
    manageTeamButton_ = new QPushButton();
    deleteTeamButton_ = new QPushButton();

    mainLayout_->addStretch();
    mainLayout_->addWidget(manageTeamButton_);
    mainLayout_->addWidget(deleteTeamButton_);
}

void TeamListItemButtons::setStyling() {
    manageTeamButton_->setText("Zarządzaj zespołem");
    deleteTeamButton_->setText("Usuń zespół");
}

void TeamListItemButtons::connectSignals() {
    connect(manageTeamButton_, &QPushButton::clicked, this, [=](){
        emit manageTeamButtonClicked();
    });
    connect(deleteTeamButton_, &QPushButton::clicked, this, [=](){
        emit teamDeleted();
    });
}

void TeamListItemButtons::setDisableManage(bool disabled) {
    manageTeamButton_->setDisabled(disabled);
}

void TeamListItemButtons::setDisableDelete(bool disabled) {
    deleteTeamButton_->setDisabled(disabled);
}
