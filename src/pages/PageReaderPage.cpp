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

}
