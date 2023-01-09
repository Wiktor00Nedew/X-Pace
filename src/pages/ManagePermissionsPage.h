//
// Created by Wiktor on 09.01.2023.
//

#pragma once
#include <QWidget>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QTreeWidgetItem>
#include "../components/Title.h"

class ManagePermissionsPage : public QWidget{
Q_OBJECT
public:
    explicit ManagePermissionsPage(QWidget *parent = nullptr);
    ~ManagePermissionsPage();

private:
    QTreeWidgetItem* item_;
    bool isPage_;
    std::string objectId_;

    std::vector<std::string> userIds_;

    void createComponents();
    void setStyling();
    void connectSignals();

    QGridLayout *mainLayout_;
    Title *addPermissionTitle_;
    QComboBox *userToAddComboBox_;
    QComboBox *accessLevelAddComboBox_;
    QPushButton *addPermissionButton_;

    Title *removePermissionTitle_;
    QListWidget *permissionsView_;

signals:
    void settingDefaultPage();

public slots:
    void loadPermissionForItem(QTreeWidgetItem* item);
    void onDeletedPermission(const std::string &entityId, const int accessLevel);
    void addPermission();
};
