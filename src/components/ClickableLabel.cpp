//
// Created by Wiktor on 28.12.2022.
//

#include "ClickableLabel.h"

void ClickableLabel::mousePressEvent(QMouseEvent *event) {
    //qDebug() << "here i got clicked";
    emit clicked();
}

ClickableLabel::~ClickableLabel() {

}

ClickableLabel::ClickableLabel(QWidget *parent) {
    setStyling();
}

void ClickableLabel::setStyling() {
    setCursor(Qt::PointingHandCursor);
}

