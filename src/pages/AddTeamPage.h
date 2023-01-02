//
// Created by Wiktor on 01.01.2023.
//

#pragma once


#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "../components/Title.h"
#include "../components/ErrorLabel.h"
#include "../components/LoadingIndicator.h"

class AddTeamPage : public QWidget{
    Q_OBJECT
public:
    explicit AddTeamPage(QWidget *parent = nullptr);
    ~AddTeamPage();

    void createComponents();
    void setStyling();
    void connectSignals();


private:
    QVBoxLayout *mainLayout_;

    Title *title_;
    QLabel *nameLabel_;
    QLineEdit *nameBox_;
    QPushButton *addTeamButton_;
    ErrorLabel *errorLabel_;
    LoadingIndicator *loadingIndicator_;

public slots:
    void addTeam();

signals:
    void addedTeam();

};
