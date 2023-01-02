//
// Created by Wiktor on 01.01.2023.
//

#pragma once


#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QListWidget>

class MyTeamsPage : public QWidget{
    Q_OBJECT
public:
    explicit MyTeamsPage(QWidget *parent = nullptr);
    ~MyTeamsPage();

    void createComponents();
    void setStyling();
    void connectSignals();


private:
    QVBoxLayout *mainLayout_;
    QListWidget *teamsList_;
    QPushButton *addTeamButton_;

public slots:
    void loadTeams();

signals:
    void createTeamOpened();
    void teamDeleted();
};
