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

class ApplicationPage : public QWidget{
    Q_OBJECT
public:
    explicit ApplicationPage(QWidget *parent = nullptr);
    ~ApplicationPage();

    void createComponents();
    void setStyling();
    void connectSignals();

private:
    QVBoxLayout *mainLayout_;

    QSplitter *mainSplitter_;
    TopBar *topBar_;
    QTreeWidget *pagesList_;
    QStackedWidget *mainStack_;

public slots:
    void onLogout();
    void onLogin();

signals:
    void logedOut();
};
