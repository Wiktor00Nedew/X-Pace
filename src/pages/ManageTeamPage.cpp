//
// Created by Wiktor on 08.01.2023.
//

#include <QInputDialog>
#include "ManageTeamPage.h"
#include "../api/Api.h"
#include "../api/ApiMessage.h"
#include "../utilities/common.h"
#include "../components/MessageBoxManager.h"

ManageTeamPage::ManageTeamPage(QWidget *parent) {
    createComponents();
    setStyling();
    connectSignals();

    setLayout(mainLayout_);
}

ManageTeamPage::~ManageTeamPage() {

}

void ManageTeamPage::createComponents() {
    mainLayout_ = new QGridLayout();

    teamNameLabel_ = new QLabel();
    changeNameButton_ = new QPushButton();

    addNewUserTitle_ = new Title();

    accessLevelLabel_ = new QLabel();

    radioButtonsGroup_ = new QGroupBox();
    buttonGroupLogical_ = new QButtonGroup();
    groupLayout_ = new QVBoxLayout();

    radioMember_ = new QRadioButton();
    radioModerator_ = new QRadioButton();
    radioOwner_ = new QRadioButton();

    addNewUserButton_ = new QPushButton();

    codeBox_ = new QLineEdit();

    groupLayout_->addWidget(radioMember_);
    groupLayout_->addWidget(radioModerator_);
    groupLayout_->addWidget(radioOwner_);
    groupLayout_->addStretch();

    radioButtonsGroup_->setLayout(groupLayout_);

    buttonGroupLogical_->addButton(radioMember_, 0);
    buttonGroupLogical_->addButton(radioModerator_, 1);
    buttonGroupLogical_->addButton(radioOwner_, 2);

    backButton_ = new QPushButton();

    mainLayout_->addWidget(teamNameLabel_, 0, 0);
    mainLayout_->addWidget(changeNameButton_, 0, 1);
    mainLayout_->addWidget(addNewUserTitle_, 2, 0, 1, 3);
    mainLayout_->addWidget(accessLevelLabel_, 3, 0);
    mainLayout_->addWidget(radioButtonsGroup_, 4, 0);
    mainLayout_->addWidget(addNewUserButton_, 5, 0, 1, 2);
    mainLayout_->addWidget(codeBox_, 5, 2);
    mainLayout_->addWidget(backButton_, 6, 0, 1, 3);
}

void ManageTeamPage::setStyling() {
    changeNameButton_->setText("Zmień");

    accessLevelLabel_->setText("Poziom dostępu:");

    radioMember_->setText("Członek");
    radioModerator_->setText("Moderator");
    radioOwner_->setText("Właściciel");

    addNewUserTitle_->setText("Wygeneruj kod dla nowego członka");
    addNewUserButton_->setText("Wygeneruj");

    radioMember_->setChecked(true);

    backButton_->setText("Wróć");
}

void ManageTeamPage::connectSignals() {
    connect(changeNameButton_, &QPushButton::clicked, this, &ManageTeamPage::changeTeamName);
    connect(addNewUserButton_, &QPushButton::clicked, this, &ManageTeamPage::generateAccessCode);
    connect(backButton_, &QPushButton::clicked, this, [=](){
        emit setMyTeamsPage();
    });
}

void ManageTeamPage::loadTeamInfo(const std::string &teamId) {
    //qDebug() << QString::fromStdString(teamId);

    auto apiResponse = Api::get().apiGetTeamById(teamId);

    if (apiResponse.type == ApiMessage::Error){
        MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
        emit setMyTeamsPage();
        return;
    }

    teamId_ = teamId;

    teamNameLabel_->setText("Nazwa zespołu: " + QString::fromStdString(apiResponse.data["name"]));
}

void ManageTeamPage::generateAccessCode() {
    int checkButtonId = buttonGroupLogical_->checkedId();

    ApiMessage apiResponse;

    switch (checkButtonId){
        case 0:
            apiResponse = Api::get().apiGenerateMemberCode(teamId_);

            if (apiResponse.type == ApiMessage::Error){
                MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
                return;
            }

            codeBox_->setText(QString::fromStdString(apiResponse.data["id"]));
        case 1:
            apiResponse = Api::get().apiGenerateModeratorCode(teamId_);

            if (apiResponse.type == ApiMessage::Error){
                MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
                return;
            }

            codeBox_->setText(QString::fromStdString(apiResponse.data["id"]));
        case 2:
            apiResponse = Api::get().apiGenerateOwnerCode(teamId_);

            if (apiResponse.type == ApiMessage::Error){
                MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
                return;
            }

            codeBox_->setText(QString::fromStdString(apiResponse.data["id"]));
    }
}

void ManageTeamPage::changeTeamName() {
    auto apiResponse = Api::get().apiGetTeamById(teamId_);

    if (apiResponse.type == ApiMessage::Error){
        MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
        return;
    }

    bool isOwner = false;

    for (auto owner : apiResponse.data["owners"])
        if (owner == Api::get().getUser()["id"])
            isOwner = true;

    if (!isOwner){
        MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors["UNAUTHORIZED"]));
        return;
    }

    // TODO copy where needed

    bool ok;

    QString name = QInputDialog::getText(0, "Zmień nazwę zespołu",
                                         "Nazwa zespołu:", QLineEdit::Normal,
                                         QString::fromStdString(apiResponse.data["name"]), &ok);

    if (!ok)
        return;

    auto apiMessage = Api::get().apiRenameTeam(teamId_, name.toStdString());

    if (apiMessage.type == ApiMessage::Error){
        MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiMessage.data["key"]]));
        return;
    }

    teamNameLabel_->setText("Nazwa zespołu: " + name);

    emit teamNameChanged();
}
