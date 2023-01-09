//
// Created by Wiktor on 09.01.2023.
//

#include "ManagePermissionsPage.h"
#include "../api/Api.h"
#include "../components/MessageBoxManager.h"
#include "../utilities/common.h"
#include "../structures/PermissionsListItem.h"

ManagePermissionsPage::ManagePermissionsPage(QWidget *parent) {
    createComponents();
    setStyling();
    connectSignals();

    setLayout(mainLayout_);
}

ManagePermissionsPage::~ManagePermissionsPage() {

}

void ManagePermissionsPage::createComponents() {
    mainLayout_ = new QGridLayout();

    addPermissionTitle_ = new Title();
    userToAddComboBox_ = new QComboBox();
    accessLevelAddComboBox_ = new QComboBox();
    addPermissionButton_ = new QPushButton();

    removePermissionTitle_ = new Title();
    permissionsView_ = new QListWidget();

    mainLayout_->addWidget(addPermissionTitle_, 0, 0, 1, 3);
    mainLayout_->addWidget(userToAddComboBox_, 1, 0);
    mainLayout_->addWidget(accessLevelAddComboBox_, 1, 1);
    mainLayout_->addWidget(addPermissionButton_, 1, 2);
    mainLayout_->addWidget(removePermissionTitle_, 4, 0, 1, 3);
    mainLayout_->addWidget(permissionsView_, 5, 0, 1, 3);
}

void ManagePermissionsPage::setStyling() {
    addPermissionTitle_->setText("Dodaj nowe uprawnienie");
    removePermissionTitle_->setText("Usuń uprawnienie");
    addPermissionButton_->setText("Dodaj uprawnienie");
}

void ManagePermissionsPage::connectSignals() {
    connect(addPermissionButton_, &QPushButton::clicked, this, &ManagePermissionsPage::addPermission);
}

void ManagePermissionsPage::loadPermissionForItem(QTreeWidgetItem *item) {


    permissionsView_->clear();
    userToAddComboBox_->clear();
    accessLevelAddComboBox_->clear();
    userIds_.clear();

    nlohmann::json permissions;
    std::string teamId;
    ApiMessage apiResponse;
    if (item->text(3) == "true"){ //page
        apiResponse = Api::get().apiGetPageById(item->text(1).toStdString());

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            emit settingDefaultPage();
            return;
        }

        permissions = apiResponse.data["permissions"];
        teamId = apiResponse.data["team"];
    }
    else if (item->text(3) == "false") { //directory
        apiResponse = Api::get().apiGetDirectoryById(item->text(1).toStdString());

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            emit settingDefaultPage();
            return;
        }

        permissions = apiResponse.data["permissions"];
        teamId = apiResponse.data["team"];
    }

    bool hasPrivilege = false;

    if (apiResponse.data["owner"] == Api::get().getUser()["id"])
        hasPrivilege = true;

    auto teamPerm = Api::get().apiGetTeamById(apiResponse.data["team"]);

    for (auto owner : teamPerm.data["owners"])
        if (owner == Api::get().getUser()["id"])
            hasPrivilege = true;

    for (auto moderator : teamPerm.data["moderators"])
        if (moderator == Api::get().getUser()["id"])
            hasPrivilege = true;

    if (!hasPrivilege){
        MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors["UNAUTHORIZED"]));
        emit settingDefaultPage();
        return;
    }

    for (auto perm : permissions){
        auto widget = new PermissionsListItem(QString::fromStdString(perm["entityId"]), perm["key"]);

        connect(widget, &PermissionsListItem::deletedPermission, this, &ManagePermissionsPage::onDeletedPermission);

        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(widget->sizeHint());

        permissionsView_->addItem(item);
        permissionsView_->setItemWidget(item, widget);
    }

    auto team = Api::get().apiGetTeamById(teamId);

    if (team.type == ApiMessage::Error){
        MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[team.data["key"]]));
        emit settingDefaultPage();
        return;
    }

    for (auto user : team.data["members"]){
        userIds_.push_back(user);
        auto apiMessage = Api::get().apiGetNameForUserById(user);

        if (apiMessage.type == ApiMessage::Error)
            userToAddComboBox_->addItem(QString::fromStdString(user));
        else
            userToAddComboBox_->addItem(QString::fromStdString(apiMessage.data["name"]));
    }

    accessLevelAddComboBox_->addItems({"Odczyt", "Wykonanie", "Edycja"});

    if (item->text(3) == "true")
        isPage_ = true;
    else if (item->text(3) == "false")
        isPage_ = false;

    objectId_ = item->text(1).toStdString();

    item_ = item;
}

void ManagePermissionsPage::onDeletedPermission(const std::string &entityId, const int accessLevel) {
    if (isPage_){
        auto apiResponse = Api::get().apiDeletePagePermission(objectId_, entityId, accessLevel);

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            return;
        }
    }
    else{
        auto apiResponse = Api::get().apiDeleteDirectoryPermission(objectId_, entityId, accessLevel);

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            return;
        }
    }

    loadPermissionForItem(item_);
}

void ManagePermissionsPage::addPermission() {
    int entityIdIndex = userToAddComboBox_->currentIndex();
    int accessLevelIndex = accessLevelAddComboBox_->currentIndex();
    int accessLevel;

    std::string entityId = userIds_[entityIdIndex];

    switch(accessLevelIndex){
        case 0:
            accessLevel = 1;
            break;
        case 1:
            accessLevel = 3;
            break;
        case 2:
            accessLevel = 7;
            break;
    }

    if (isPage_){
        auto apiResponse = Api::get().apiAddPagePermission(objectId_, entityId, accessLevel);

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            return;
        }
    }
    else{
        auto apiResponse = Api::get().apiAddDirectoryPermission(objectId_, entityId, accessLevel);

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            return;
        }
    }

    loadPermissionForItem(item_);
}
