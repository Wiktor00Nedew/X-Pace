//
// Created by Wiktor on 07.01.2023.
//

#include "ViewPage.h"
#include "../api/ApiMessage.h"
#include "../api/Api.h"
#include "../utilities/common.h"
#include "../components/MessageBoxManager.h"

ViewPage::ViewPage(QWidget *parent) {
    createComponents();
    setStyling();
    connectSignals();

    setLayout(mainLayout_);
}

ViewPage::~ViewPage() {

}

void ViewPage::createComponents() {
    mainLayout_ = new QVBoxLayout();

    markdownView_ = new QTextBrowser();
    editButton_ = new QPushButton();

    mainLayout_->addWidget(markdownView_);
    mainLayout_->addWidget(editButton_);
}

void ViewPage::setStyling() {
    editButton_->setText("Edytuj stronę");
    markdownView_->setReadOnly(true);

    markdownView_->setOpenExternalLinks(true);
    markdownView_->setOpenLinks(true);
}

void ViewPage::connectSignals() {
    connect(editButton_, &QPushButton::clicked, this, [=](){
        emit editingPage(pageId_);
    });
}

void ViewPage::loadPage(const std::string &pageId) {
    editButton_->setDisabled(false);
    ApiMessage apiResponse = Api::get().apiGetPageById(pageId);

    if (apiResponse.type == ApiMessage::Error){
        MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
        emit settingDefaultPage();
        return;
    }

    pageId_ = pageId;

    std::string textBeforeFormat = apiResponse.data["content"];
    textBeforeFormat.erase(textBeforeFormat.begin());
    auto text = QString::fromStdString(textBeforeFormat);

    markdownView_->setMarkdown(text);

    bool hasPrivilege = false;

    if (apiResponse.data["owner"] == Api::get().getUser()["id"])
        hasPrivilege = true;

    for (auto permission : apiResponse.data["permissions"])
        if ((permission["entityId"] == Api::get().getUser()["id"] && permission["key"] == 7) || (permission["entityId"] == "others" && permission["key"] == 7))
            hasPrivilege = true;

    auto team = Api::get().apiGetTeamById(apiResponse.data["team"]);

    for (auto owner : team.data["owners"])
        if (owner == Api::get().getUser()["id"])
            hasPrivilege = true;

    for (auto moderator : team.data["moderators"])
        if (moderator == Api::get().getUser()["id"])
            hasPrivilege = true;

    if (!hasPrivilege){
        editButton_->setDisabled(true);
    }
}
