//
// Created by Wiktor on 01.01.2023.
//

#include "TreeWidgetButtons.h"

TreeWidgetButtons::TreeWidgetButtons(QWidget *parent) {
    createComponents();
    setStyling();
    connectSignals();

    setLayout(mainLayout_);
}

TreeWidgetButtons::~TreeWidgetButtons() {

}

void TreeWidgetButtons::createComponents() {
    mainLayout_ = new QHBoxLayout();

    // buttons
    addDirectoryButton_ = new QPushButton();
    addPageButton_ = new QPushButton();

    mainLayout_->addStretch();
    mainLayout_->addWidget(addDirectoryButton_);
    mainLayout_->addWidget(addPageButton_);
}

void TreeWidgetButtons::setStyling() {
    addDirectoryButton_->setText("Dodaj folder");
    addPageButton_->setText("Dodaj stronę");
}

void TreeWidgetButtons::connectSignals() {
    connect(addDirectoryButton_, &QPushButton::clicked, this, [=](){
        emit addDirectoryButtonClicked();
    });
    connect(addPageButton_, &QPushButton::clicked, this, [=](){
        emit addPageButtonClicked();
    });
}

void TreeWidgetButtons::setDisableAddDirectory(bool disabled) {
    addDirectoryButton_->setDisabled(disabled);
}

void TreeWidgetButtons::setDisableAddPage(bool disabled) {
    addPageButton_->setDisabled(disabled);
}
