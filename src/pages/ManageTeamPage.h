//
// Created by Wiktor on 08.01.2023.
//

#pragma once


#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QLineEdit>
#include "../components/Title.h"
#include <QButtonGroup>

class ManageTeamPage : public QWidget{
    Q_OBJECT

public:
    explicit ManageTeamPage(QWidget *parent = nullptr);
    ~ManageTeamPage();

private:
    std::string teamId_;

    void createComponents();
    void setStyling();
    void connectSignals();

    QGridLayout *mainLayout_;

    QLabel *teamNameLabel_;
    QPushButton *changeNameButton_;

    Title *addNewUserTitle_;

    QLabel *accessLevelLabel_;

    QGroupBox *radioButtonsGroup_;
    QButtonGroup *buttonGroupLogical_;
    QVBoxLayout *groupLayout_;

    QRadioButton *radioMember_;
    QRadioButton *radioModerator_;
    QRadioButton *radioOwner_;

    QPushButton *addNewUserButton_;

    QLineEdit *codeBox_;

    QPushButton *backButton_;

public slots:
    void loadTeamInfo(const std::string& teamId);
    void generateAccessCode();
    void changeTeamName();

signals:
    void setMyTeamsPage();
    void teamNameChanged();
};
