//
// Created by Wiktor on 07.01.2023.
//

#include "PageReaderPage.h"

PageReaderPage::PageReaderPage(QWidget *parent) {
    createComponents();
    setStyling();
    connectSignals();
}

PageReaderPage::~PageReaderPage() {

}

void PageReaderPage::createComponents() {
    mainLayout_ = new QVBoxLayout();
    mainStack_ = new QStackedWidget();

    editPage_ = new EditPage();
    viewPage_ = new ViewPage();

    mainStack_->addWidget(editPage_);
    mainStack_->addWidget(viewPage_);

    mainLayout_->addWidget(mainStack_);
}

void PageReaderPage::setStyling() {
    mainStack_->setCurrentIndex(mainStack_->indexOf(viewPage_));
}

void PageReaderPage::connectSignals() {
    connect(viewPage_, &ViewPage::editingPage, this, &PageReaderPage::onEditingPage);
    connect(editPage_, &EditPage::finishingEditing, this, &PageReaderPage::onFinishingEditing);
    connect(viewPage_, &ViewPage::settingDefaultPage, this, [=](){
        emit settingDefaultPage();
    });
    connect(editPage_, &EditPage::settingDefaultPage, this, [=](){
        emit settingDefaultPage();
    });
}

void PageReaderPage::onEditingPage(const std::string& pageId) {
    mainStack_->setCurrentIndex(mainStack_->indexOf(editPage_));
    editPage_->loadPage(pageId);
}

void PageReaderPage::onFinishingEditing(const std::string& pageId) {
    mainStack_->setCurrentIndex(mainStack_->indexOf(viewPage_));
    viewPage_->loadPage(pageId);
}
