//
// Created by Wiktor on 13.04.2022.
//

#pragma once

#include <QToolButton>
#include <QGridLayout>
#include <QAction>
#include <QMenu>
#include <QWidgetAction>
#include <QToolBar>
#include <QPushButton>
#include "Button.h"

class DropdownButton : public QWidget {
Q_OBJECT
public:
    explicit DropdownButton(QWidget *parent = nullptr);

    void setUsername(const QString& name);
    ~DropdownButton();
private:
    // methods
    void setStyling();
    void addActions();
    void addMenus();
    void addToolButtons();

    // objects
    QGridLayout *mainLayout_;
    Button *dropdownButton_;
    QMenu *userMenu_;
    QAction *logoutAction_;
    QAction *mySettingsAction_;

signals:
    void mySettingsOpened();
    void logedOut();
};



