//
// Created by Wiktor on 28.12.2022.
//

#include "ApplicationPage.h"
#include "../utilities/Singleton.h"
#include "../api/ApiMessage.h"
#include "../api/Api.h"
#include "../components/MessageBoxManager.h"
#include "../utilities/common.h"

ApplicationPage::ApplicationPage(QWidget *parent) {
    createComponents();
    connectSignals();
    setStyling();

    setLayout(mainLayout_);
}

ApplicationPage::~ApplicationPage() {

}

void ApplicationPage::createComponents() {
    mainLayout_ = new QVBoxLayout();
    mainStack_ = new QStackedWidget();
    topBar_ = new TopBar();
    pagesList_ = new QTreeWidget();

    mainSplitter_ = new QSplitter(Qt::Horizontal);
    mainSplitter_->addWidget(pagesList_);
    mainSplitter_->addWidget(mainStack_);

    mainLayout_->addWidget(topBar_);
    mainLayout_->addWidget(mainSplitter_);
}

void ApplicationPage::setStyling() {
    mainLayout_->setSpacing(0);
    mainLayout_->setContentsMargins(0, 0, 0, 0);

    mainSplitter_->setHandleWidth(1);
    mainSplitter_->setSizes({(int)(0.3 * width()), (int)(0.7 * width())});
}

void ApplicationPage::connectSignals() {
    connect(topBar_, &TopBar::logedOut, this, &ApplicationPage::onLogout);
}

void ApplicationPage::onLogout() {
    bool active = true;

    while(active){
        ApiMessage apiResponse = Api::get().apiRevokeToken();


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

    emit logedOut();
}

void ApplicationPage::onLogin() {
    bool active = true;
    ApiMessage apiResponse;

    while(active){
        apiResponse = Api::get().apiGetUserByToken();
        qDebug() << QString::fromStdString(to_string(apiResponse.data));

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
    topBar_->setUsername(QString::fromStdString(apiResponse.data["username"]));
}

