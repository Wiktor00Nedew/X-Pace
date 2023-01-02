//
// Created by Wiktor on 01.01.2023.
//

#pragma once


#include <QTreeWidgetItem>
#include <QLabel>
#include <QHBoxLayout>
#include "Permission.h"

class ItemWidget : public QWidget{
public:
    explicit ItemWidget(const std::string& id, const std::string& name, const std::string& owner, const std::vector<Permission>& permissions, bool isPage, QWidget *parent = nullptr);
    ~ItemWidget();

    std::string id;
    std::string name;
    std::string owner;
    std::vector<Permission> permissions;
    bool isPage;

    void createComponents();
    void setStyling();
    void connectSignals();

    void setText(const QString& text);

private:
    QLabel *text_;
    QHBoxLayout *mainLayout_;
};
