//
// Created by Wiktor on 16.11.2022.
//

#include "TitleBar.h"

void TitleBar::mousePressEvent(QMouseEvent *event) {
    if(event->button() == Qt::LeftButton){
        cursor_ = event->globalPos() - parent_->geometry().topLeft();
        event->accept();
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent *event) {
    if(event->buttons() & Qt::LeftButton){
        parent_->move(event->globalPos() - cursor_);
        event->accept();
    }
}

TitleBar::TitleBar(QWidget *parent) : parent_(parent){
    mainLayout = new QHBoxLayout();

    createComponents();
    setStyling();

    setLayout(mainLayout);
}

TitleBar::~TitleBar() {

}

void TitleBar::setStyling() {
    setAttribute(Qt::WA_StyledBackground);
    setFixedHeight(30);

    mainLayout->setContentsMargins(3, 3, 3, 3);
}

void TitleBar::createComponents() {
    testButton = new QPushButton();
    mainLayout->addWidget(testButton);
    mainLayout->addStretch();

}
