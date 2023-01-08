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
#include "../components/ClickableLabel.h"

class JoinTeamPage : public QWidget{
    Q_OBJECT
public:
    explicit JoinTeamPage(QWidget *parent = nullptr);
    ~JoinTeamPage();

    void createComponents();
    void setStyling();
    void connectSignals();


private:
    QVBoxLayout *mainLayout_;

    Title *title_;
    QLabel *tokenLabel_;
    QLineEdit *tokenBox_;
    QPushButton *joinTeamButton_;
    ErrorLabel *errorLabel_;
    LoadingIndicator *loadingIndicator_;
    ClickableLabel *addTeamRedirect_;

public slots:
    void joinTeam();

signals:
    void joinedTeam();
    void changingToAddTeam();

};
