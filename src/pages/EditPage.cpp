//
// Created by Wiktor on 07.01.2023.
//

#include <QInputDialog>
#include "EditPage.h"
#include "../api/ApiMessage.h"
#include "../api/Api.h"
#include "../utilities/common.h"
#include "../components/MessageBoxManager.h"

void EditPage::createComponents() {
    mainLayout_ = new QGridLayout();

    markdownEdit_ = new QTextEdit();
    saveButton_ = new QPushButton();
    cancelButton_ = new QPushButton();

    mainLayout_->addWidget(markdownEdit_, 0, 0, 1, 2);
    mainLayout_->addWidget(cancelButton_, 1, 0);
    mainLayout_->addWidget(saveButton_, 1, 1);
}

void EditPage::setStyling() {
    saveButton_->setText("Zapisz");
    cancelButton_->setText("Anuluj");
}

void EditPage::connectSignals() {
    connect(cancelButton_, &QPushButton::clicked, this, [=](){
        emit changesSaved();
        emit finishingEditing(pageId_);
    });
    connect(saveButton_, &QPushButton::clicked, this, &EditPage::onSaveButtonClicked);
    connect(markdownEdit_, &QTextEdit::textChanged, this, [=](){
        emit unsavedChanges();
    });
}

EditPage::EditPage(QWidget *parent) {
    createComponents();
    setStyling();
    connectSignals();

    setLayout(mainLayout_);
}

EditPage::~EditPage() {

}

void EditPage::loadPage(const std::string &pageId) {
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

    markdownEdit_->setPlainText(text);
}

void EditPage::onSaveButtonClicked() {
    std::string text = "." + markdownEdit_->toPlainText().toStdString();

    ApiMessage apiResponse = Api::get().apiEditPage(pageId_, text);

    if (apiResponse.type == ApiMessage::Error){
        MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
        return;
    }

    emit changesSaved();
    emit finishingEditing(pageId_);
}

void EditPage::onSaveRequest() {
    bool chosenOption = MessageBoxManager::get().question("Pytanie", "Czy chcesz zapisać zmiany?");

    if (!chosenOption){
        emit changesSaved();
        emit finishingEditing(pageId_);
        return;
    }

    std::string text = "." + markdownEdit_->toPlainText().toStdString();

    ApiMessage apiResponse = Api::get().apiEditPage(pageId_, text);

    if (apiResponse.type == ApiMessage::Error){
        MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
        return;
    }

    emit changesSaved();
    emit finishingEditing(pageId_);
}
