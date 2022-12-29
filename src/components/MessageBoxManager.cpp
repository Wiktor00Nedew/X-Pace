//
// Created by Wiktor on 06.05.2022.
//

#include "MessageBoxManager.h"
#include <QPushButton>

MessageBoxManager::MessageBoxManager(QWidget *parent){

}

MessageBoxManager::~MessageBoxManager() {

}

bool MessageBoxManager::question(const QString &title, const QString &body) {
    QMessageBox msBox;
    msBox.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    msBox.setWindowTitle(title);
    msBox.setText(body);

    QPixmap icon("../assets/question-mark.png");

    msBox.setIconPixmap(icon.scaled(75, 75));

    QPushButton *yesButton = new QPushButton();
    yesButton->setText("Tak");
    yesButton->setMinimumWidth(50);
    msBox.addButton(yesButton, QMessageBox::YesRole);

    QPushButton *noButton = new QPushButton();
    noButton->setText("Nie");
    noButton->setMinimumWidth(50);
    msBox.addButton(noButton, QMessageBox::NoRole);
    msBox.exec();
    if(msBox.clickedButton() == yesButton){
        delete yesButton;
        delete noButton;
        return true;
    }
    else {
        delete yesButton;
        delete noButton;
        return false;
    }
}

bool MessageBoxManager::warning(const QString &title, const QString &body) {
    //for now empty, maybe will be used in the future
    return false;
}

bool MessageBoxManager::critical(const QString &title, const QString &body) {
    //for now empty, maybe will be used in the future
    return false;
}

bool MessageBoxManager::about(const QString &title, const QString &body) {
    //for now empty, maybe will be used in the future
    return false;
}


