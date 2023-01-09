//
// Created by Wiktor on 09.01.2023.
//

#include "PermissionsListItem.h"
#include "../api/ApiMessage.h"
#include "../api/Api.h"

PermissionsListItem::PermissionsListItem(const QString &entityId, const int accessLevel, QWidget *parent) {
    createComponents();
    setStyling(entityId, accessLevel);
    connectSignals();

    entityId_ = entityId.toStdString();
    accessLevel_ = accessLevel;

    setLayout(mainLayout_);
}

PermissionsListItem::~PermissionsListItem() {

}

void PermissionsListItem::createComponents() {
    mainLayout_ = new QVBoxLayout();

    userNameLabel_ = new QLabel();
    accessLevelLabel_ = new QLabel();

    deleteButton_ = new QPushButton();

    mainLayout_->addWidget(userNameLabel_);
    mainLayout_->addWidget(accessLevelLabel_);
    mainLayout_->addWidget(deleteButton_);
}

void PermissionsListItem::setStyling(const QString &entityId, int accessLevel) {
    mainLayout_->setSizeConstraint(QLayout::SetFixedSize);

    auto apiMessage = Api::get().apiGetNameForUserById(entityId.toStdString());

    if (apiMessage.type == ApiMessage::Error)
        userNameLabel_->setText("Id użytkownika: " + entityId);
    else
        userNameLabel_->setText("Nazwa użytkownika: " + QString::fromStdString(apiMessage.data["name"]));

    accessLevelLabel_->setText(QString::number(accessLevel));

    deleteButton_->setText("Usuń");
}

void PermissionsListItem::connectSignals() {
    connect(deleteButton_, &QPushButton::clicked, this, [=](){
        emit deletedPermission(entityId_, accessLevel_);
    });
}
