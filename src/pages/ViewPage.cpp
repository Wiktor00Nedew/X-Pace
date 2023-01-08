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
}
