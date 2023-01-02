//
// Created by Wiktor on 01.01.2023.
//

#pragma once


#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

class TeamListItemButtons : public QWidget{
Q_OBJECT
public:
    explicit TeamListItemButtons(QWidget *parent = nullptr);
    ~TeamListItemButtons();

    void createComponents();
    void setStyling();
    void connectSignals();

    void setDisableManage(bool disabled);
    void setDisableDelete(bool disabled);

private:
    QHBoxLayout *mainLayout_;

    // buttons
    QPushButton *manageTeamButton_;
    QPushButton *deleteTeamButton_;

signals:
    void manageTeamButtonClicked();
    void teamDeleted();

};
