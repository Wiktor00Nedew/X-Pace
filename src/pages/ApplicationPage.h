//
// Created by Wiktor on 28.12.2022.
//

#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QTreeWidget>
#include <QStackedWidget>
#include <QSplitter>
#include "../structures/TopBar.h"
#include "MyTeamsPage.h"
#include "AddTeamPage.h"
#include "../structures/ItemsList.h"
#include "PageReaderPage.h"

class ApplicationPage : public QWidget{
    Q_OBJECT
public:
    explicit ApplicationPage(QWidget *parent = nullptr);
    ~ApplicationPage();

    void createComponents();
    void setStyling();
    void connectSignals();

private:
    bool isAllSaved;

    QVBoxLayout *mainLayout_;

    QSplitter *mainSplitter_;
    TopBar *topBar_;
    ItemsList *itemsList_;
    QStackedWidget *mainStack_;

    // pages

    MyTeamsPage *myTeamsPage_;
    AddTeamPage *addTeamPage_;
    PageReaderPage *pageReaderPage_;
    QWidget *defaultPage_;

public slots:
    void onLogout();
    void onLogin();
    void onMyTeamsOpened();
    void onCreateTeamOpened();
    void onAddedTeam();
    void onTeamDeleted();
    void onTeamChanged(int currentIndex);
    void onSettingDefaultPage();

signals:
    void logedOut();
    void myTeamsOpened();
    void createTeamOpened();
};
