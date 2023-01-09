//
// Created by Wiktor on 09.01.2023.
//

#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

class PermissionsListItem : public QWidget {
    Q_OBJECT
public:
    explicit PermissionsListItem(const QString& entityId, const int accessLevel, QWidget *parent = nullptr);
    ~PermissionsListItem();

    void createComponents();
    void setStyling(const QString &entityId, const int accessLevel);
    void connectSignals();

private:
    std::string entityId_;
    int accessLevel_;

    QVBoxLayout *mainLayout_;

    // labels
    QLabel *userNameLabel_;
    QLabel *accessLevelLabel_;

    QPushButton *deleteButton_;

signals:
    void deletedPermission(const std::string &entityId, const int accessLevel);

};
