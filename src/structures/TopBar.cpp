//
// Created by Wiktor on 29.12.2022.
//

#include "TopBar.h"
#include "../api/ApiMessage.h"
#include "../api/Api.h"
#include "../components/MessageBoxManager.h"
#include "../utilities/common.h"

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
    connect(userMenu_, &DropdownButton::myTeamsOpened, this, [=](){
        emit myTeamsOpened();
    });
    connect(teamMenu_, &QComboBox::currentIndexChanged, this, [=](){
        emit teamChanged(teamMenu_->currentIndex());
    });
}

void TopBar::setStyling() {
    setFixedHeight(60);
    setAttribute(Qt::WA_StyledBackground);
    teamMenu_->setFocusPolicy(Qt::NoFocus);
    teamMenu_->setMinimumWidth(150);
    //userMenu_->setMinimumHeight(50);
}

void TopBar::setUsername(const QString &name) {
    userMenu_->setUsername(name);
}

void TopBar::loadTeams(const nlohmann::json& teamsById) {
    teamMenu_->clear();
    //qDebug() << "here";
    for (auto team : teamsById){
        bool active = true;
        ApiMessage apiResponse;
        //qDebug() << "here3";

        while(active){
            //qDebug() << QString::fromStdString(team);
            apiResponse = Api::get().apiGetTeamById(team);
            //qDebug() << QString::fromStdString(to_string(apiResponse.data));
            //qDebug() << "here2";

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
        teamMenu_->addItem(QString::fromStdString(apiResponse.data["name"]));
    }

}
