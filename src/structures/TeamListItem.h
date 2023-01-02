//
// Created by Wiktor on 01.01.2023.
//

#pragma once


#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include "../components/TeamListItemButtons.h"
#include "../pages/MyTeamsPage.h"

class TeamListItem : public QWidget {
    Q_OBJECT
public:
    explicit TeamListItem(const QString& id, const QString& name, const QString& createdAt, const QString& members, const QString& moderators, const QString& owners, bool isModerator, bool isOwner, QWidget *parent = nullptr);
    ~TeamListItem();

    void createComponents();
    void setStyling(const QString &id, const QString &name, const QString &createdAt, const QString &members,
                    const QString &moderators, const QString &owners);
    void connectSignals();

private:
    QVBoxLayout *mainLayout_;

    std::string teamId;
    // labels
    QLabel *idLabel_;
    QLabel *nameLabel_;
    QLabel *createdAtLabel_;
    QLabel *membersLabel_;
    QLabel *moderatorsLabel_;
    QLabel *ownersLabel_;

    TeamListItemButtons *buttons_;

signals:
    void manageTeamButtonClicked(const QString &id);
    void deletedTeam();

public slots:
    void deleteTeam();
};
