//
// Created by Wiktor on 01.01.2023.
//

#include "TeamListItem.h"
#include "../api/Api.h"
#include "../components/MessageBoxManager.h"
#include "../utilities/common.h"

void TeamListItem::connectSignals() {
    connect(buttons_, &TeamListItemButtons::manageTeamButtonClicked, this, [=](){
        emit manageTeamButtonClicked(idLabel_->text());
    });
    connect(buttons_, &TeamListItemButtons::teamDeleted, this, &TeamListItem::deleteTeam);
}

TeamListItem::~TeamListItem() {

}

void TeamListItem::createComponents() {
    mainLayout_ = new QVBoxLayout();

    // labels
    idLabel_ = new QLabel();
    nameLabel_ = new QLabel();
    createdAtLabel_ = new QLabel();
    membersLabel_ = new QLabel();
    moderatorsLabel_ = new QLabel();
    ownersLabel_ = new QLabel();

    buttons_ = new TeamListItemButtons();

    mainLayout_->addWidget(idLabel_);
    mainLayout_->addWidget(nameLabel_);
    mainLayout_->addWidget(createdAtLabel_);
    mainLayout_->addWidget(membersLabel_);
    mainLayout_->addWidget(moderatorsLabel_);
    mainLayout_->addWidget(ownersLabel_);
    mainLayout_->addWidget(buttons_);
}

void TeamListItem::setStyling(const QString &id, const QString &name, const QString &createdAt, const QString &members,
                              const QString &moderators, const QString &owners) {
    idLabel_->setText("Id: " + id);
    nameLabel_->setText("Nazwa: " + name);
    createdAtLabel_->setText("Utworzono: " + createdAt);
    membersLabel_->setText("Członkowie: " + members);
    moderatorsLabel_->setText("Moderatorzy: " + moderators);
    ownersLabel_->setText("Właściciele: " + owners);

    mainLayout_->setSizeConstraint(QLayout::SetFixedSize);

    teamId = id.toStdString();
}

TeamListItem::TeamListItem(const QString &id, const QString &name, const QString &createdAt, const QString &members,
                           const QString &moderators, const QString &owners, bool isModerator, bool isOwner, QWidget *parent) {
    createComponents();
    setStyling(id, name, createdAt, members, moderators, owners);
    connectSignals();

    if (!isModerator && !isOwner)
        buttons_->setDisableManage(true);

    if (!isOwner)
        buttons_->setDisableDelete(true);

    setLayout(mainLayout_);
}

void TeamListItem::deleteTeam() {
    bool chosenOption = MessageBoxManager::get().question("Pytanie", "Czy na pewno chcesz usunąć zespół?");
    if(!chosenOption){
        return;
    }

    bool active = true;
    ApiMessage apiResponse;

    while(active){
        apiResponse = Api::get().apiDeleteTeam(teamId);
        //qDebug() << QString::fromStdString(to_string(apiResponse.data));

        if(apiResponse.type == ApiMessage::Error){
            bool chosenOption2 = MessageBoxManager::get().question("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]) + "\n"
                                                                                                                                          "Spróbować ponownie?");
            if(!chosenOption2){
                return;
            }
            continue;
        }
        active = false;
    }

    bool active2 = true;
    ApiMessage apiResponse2;

    while(active2){
        apiResponse2 = Api::get().apiFetchUser();
        //qDebug() << QString::fromStdString(to_string(apiResponse2.data));

        if(apiResponse2.type == ApiMessage::Error){
            bool chosenOption2 = MessageBoxManager::get().question("Error", QString::fromStdString(APIErrors[apiResponse2.data["key"]]) + "\n"
                                                                                                                                         "Spróbować ponownie?");
            if(!chosenOption2){
                return;
            }
            continue;
        }
        active2 = false;
    }

    emit deletedTeam();
}
