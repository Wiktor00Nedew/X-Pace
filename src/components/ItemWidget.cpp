//
// Created by Wiktor on 01.01.2023.
//

#include "ItemWidget.h"

ItemWidget::ItemWidget(const std::string &id, const std::string &name, const std::string &owner,
                       const std::vector<Permission> &permissions, bool isPage, QWidget *parent) {
    this->id = id;
    this->name = name;
    this->owner = owner;
    this->permissions = permissions;
    this->isPage = isPage;

    createComponents();
    setStyling();
    connectSignals();

    setLayout(mainLayout_);
}

ItemWidget::~ItemWidget() {

}

void ItemWidget::createComponents() {
    mainLayout_ = new QHBoxLayout();
    text_ = new QLabel();
}

void ItemWidget::setStyling() {

}

void ItemWidget::connectSignals() {

}

void ItemWidget::setText(const QString &text) {
    text_->setText(text);
}


