//
// Created by Wiktor on 01.01.2023.
//

#include "MyTeamsPage.h"
#include "../api/Api.h"
#include "../components/MessageBoxManager.h"
#include "../utilities/common.h"
#include "../structures/TeamListItem.h"

MyTeamsPage::MyTeamsPage(QWidget *parent) {
    createComponents();
    setStyling();
    connectSignals();

    setLayout(mainLayout_);
}

MyTeamsPage::~MyTeamsPage() {

}

void MyTeamsPage::createComponents() {
    mainLayout_ = new QVBoxLayout();
    teamsList_ = new QListWidget();
    addTeamButton_ = new QPushButton();

    mainLayout_->addWidget(teamsList_);
    mainLayout_->addWidget(addTeamButton_);
}

void MyTeamsPage::setStyling() {
    addTeamButton_->setText("Dodaj nowy zespół");
}

void MyTeamsPage::connectSignals() {
    connect(addTeamButton_, &QPushButton::clicked, this, [=](){
        emit createTeamOpened();
    });
}

void MyTeamsPage::loadTeams() {
    teamsList_->clear();
    //qDebug() << "testing";
    auto teamsById = Api::get().getUser()["teams"];

    for (auto team : teamsById){
        bool active = true;
        ApiMessage apiResponse;
        //qDebug() << "more testing";
        while(active){
            apiResponse = Api::get().apiGetTeamById(team);

            if(apiResponse.type == ApiMessage::Error){
                bool chosenOption = MessageBoxManager::get().question("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]) + "\n"
                                                                                                                                            "Spróbować ponownie?");
                if(!chosenOption){
                    return;
                }
                continue;
            }
            active = false;
        }
        QString membersString = "";
        QString moderatorsString = "";
        QString ownersString = "";

        bool isModerator = false;
        bool isOwner = false;

        for (auto member : apiResponse.data["members"]){
            auto apiMessage = Api::get().apiGetNameForUserById(member);

            if (apiMessage.type == ApiMessage::Error)
                continue;

            membersString += QString::fromStdString(apiMessage.data["name"]);
            membersString += ", ";
        }

        for (auto moderator : apiResponse.data["moderators"]){
            auto apiMessage = Api::get().apiGetNameForUserById(moderator);

            if (apiMessage.type == ApiMessage::Error)
                continue;

            moderatorsString += QString::fromStdString(apiMessage.data["name"]);
            moderatorsString += ", ";
            if (moderator == Api::get().getUser()["id"])
                isModerator = true;
        }

        for (auto owner : apiResponse.data["owners"]){
            auto apiMessage = Api::get().apiGetNameForUserById(owner);

            if (apiMessage.type == ApiMessage::Error)
                continue;

            ownersString += QString::fromStdString(apiMessage.data["name"]);
            ownersString += ", ";
            if (owner == Api::get().getUser()["id"])
                isOwner = true;
        }

        //qDebug() << isModerator << " " << isOwner;

        auto widget = new TeamListItem(QString::fromStdString(apiResponse.data["id"]), QString::fromStdString(apiResponse.data["name"]), QString::fromStdString(apiResponse.data["createdAt"]), membersString, moderatorsString, ownersString, isModerator, isOwner, this);

        connect(widget, &TeamListItem::deletedTeam, this, [=](){
            emit teamDeleted();
        });

        connect(widget, &TeamListItem::manageTeamButtonClicked, this, &MyTeamsPage::onManageTeamButtonClicked);

        QListWidgetItem *item = new QListWidgetItem();
        item->setSizeHint(widget->sizeHint());

        teamsList_->addItem(item);
        teamsList_->setItemWidget(item, widget);

    }
}

void MyTeamsPage::onManageTeamButtonClicked(const QString &teamId) {
    std::string modifiedTeamId = teamId.toStdString();
    emit manageTeamOpened(modifiedTeamId.erase(0, 4));
}

