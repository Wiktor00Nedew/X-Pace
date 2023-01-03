//
// Created by Wiktor on 01.01.2023.
//

#pragma once


#include <QWidget>
#include <QVBoxLayout>
#include <QTreeWidget>
#include "../components/TreeWidgetButtons.h"
#include "../utilities/json.hpp"
#include "../components/ItemWidget.h"
#include <QHeaderView>

class ItemsList : public QWidget{
    Q_OBJECT
public:
    explicit ItemsList(QWidget *parent = nullptr);
    ~ItemsList();

    void createComponents();
    void setStyling();
    void connectSignals();

    void loadItems(const std::string& teamId);

private:
    std::vector<std::string> loadedItems_;

    QIcon fileIcon = QIcon("../assets/filename-title-amarok.png");
    QIcon folderIcon = QIcon("../assets/folder-yellow.png");

    QVBoxLayout *mainLayout_;
    QTreeWidget *pagesList_;
    TreeWidgetButtons *treeWidgetButtons_;
    QHeaderView *treeHeader_;

public slots:
    void onItemClicked(QTreeWidgetItem *item, int column);
    void addPage();
    void addDirectory();
    void clearSelection();
    void prepareMenu(const QPoint& pos);
    void deleteItem(QTreeWidgetItem* item);
};
