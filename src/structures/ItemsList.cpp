//
// Created by Wiktor on 01.01.2023.
//

#include <queue>
#include <QInputDialog>
#include "ItemsList.h"
#include "../api/ApiMessage.h"
#include "../api/Api.h"
#include "../components/MessageBoxManager.h"
#include "../utilities/common.h"
#include <QStringList>
#include <QAction>
#include <QMenu>

void ItemsList::createComponents() {
    mainLayout_ = new QVBoxLayout();
    pagesList_ = new QTreeWidget();
    treeWidgetButtons_ = new TreeWidgetButtons();

    treeHeader_ = pagesList_->header();

    mainLayout_->addWidget(pagesList_);
    mainLayout_->addWidget(treeWidgetButtons_);
}

ItemsList::ItemsList(QWidget *parent) {
    createComponents();
    setStyling();
    connectSignals();

    setLayout(mainLayout_);
}

ItemsList::~ItemsList() {

}

void ItemsList::loadItems(const std::string &teamId) {
    pagesList_->clear();
    //std::queue<std::tuple<std::string, std::string>> itemsToAdd;

    bool active = true;
    ApiMessage apiResponse;

    while(active){
        apiResponse = Api::get().apiGetTeamById(teamId);

        if(apiResponse.type == ApiMessage::Error){
            bool chosenOption = MessageBoxManager::get().question("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]) + "\n"
                                                                                                                                        "Spróbować ponownie?");
            if(!chosenOption){
                return;
            }
            continue;
        }
        active = false;
    }

    for (auto mainItem : apiResponse.data["items"]){
        if (mainItem["isPage"]){
            qDebug() << "if";
            ApiMessage apiResponse2 = Api::get().apiGetPageById(mainItem["id"]);

            if (apiResponse2.type == ApiMessage::NoError){
                QString page;

                if(mainItem["isPage"])
                    page = "true";
                else
                    page = "false";

                QTreeWidgetItem *item = new QTreeWidgetItem();
                item->setText(0, QString::fromStdString(apiResponse2.data["name"]));
                item->setText(1, QString::fromStdString(apiResponse2.data["id"]));
                item->setText(2, QString::fromStdString(apiResponse2.data["owner"]));
                item->setText(3, page);
                item->setIcon(0, fileIcon);

                pagesList_->addTopLevelItem(item);
            }
        }
        else{
            //qDebug() << "else";
            ApiMessage apiResponse2 = Api::get().apiGetDirectoryById(mainItem["id"]);
            //qDebug() << "else2";
            if (apiResponse2.type == ApiMessage::NoError){
                QString page;

                if(mainItem["isPage"])
                    page = "true";
                else
                    page = "false";
                //qDebug() << "else3";
                QTreeWidgetItem *item = new QTreeWidgetItem();
                item->setText(0, QString::fromStdString(apiResponse2.data["name"]));
                //qDebug() << "else4";
                item->setText(1, QString::fromStdString(apiResponse2.data["id"]));
                //qDebug() << "else5";
                item->setText(2, QString::fromStdString(apiResponse2.data["owner"]));
                //qDebug() << "else6";
                item->setText(3, page);
                //qDebug() << "else7";
                item->setIcon(0, folderIcon);

                pagesList_->addTopLevelItem(item);
            }
        }
    }
}

void ItemsList::setStyling() {
    pagesList_->setColumnCount(4);

    QStringList namesList = {"ROOT", "Id", "Właściciel", "Is Page"};

    treeHeader_->setSectionResizeMode(0,QHeaderView::Stretch);
    treeHeader_->setSectionHidden(1,true);
    treeHeader_->setSectionHidden(2,true);
    treeHeader_->setSectionHidden(3,true);
    treeHeader_->setVisible(true);
    treeHeader_->setSectionsClickable(true);
    pagesList_->setHeaderLabels(namesList);

    pagesList_->setContextMenuPolicy(Qt::CustomContextMenu);
    pagesList_->setFocusPolicy(Qt::NoFocus);


}

void ItemsList::connectSignals() {
    connect(pagesList_, &QTreeWidget::itemClicked, this, &ItemsList::onItemClicked);
    connect(treeWidgetButtons_, &TreeWidgetButtons::addPageButtonClicked, this, &ItemsList::addPage);
    connect(treeWidgetButtons_, &TreeWidgetButtons::addDirectoryButtonClicked, this, &ItemsList::addDirectory);
    connect(treeHeader_, &QHeaderView::sectionClicked, this, &ItemsList::clearSelection);

    connect(pagesList_, &QTreeWidget::customContextMenuRequested, this, &ItemsList::prepareMenu);
}

void ItemsList::onItemClicked(QTreeWidgetItem *item, int column) {
    if (item->text(3) == "true"){ // is page
        emit pageOpened(item->text(1).toStdString());
    }
    else if (item->text(3) == "false"){ // is not page
        if (std::find(loadedItems_.begin(), loadedItems_.end(), item->text(1).toStdString()) != loadedItems_.end())
            return;

        ApiMessage apiResponse = Api::get().apiGetDirectoryById(item->text(1).toStdString());

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            return;
        }

        qDebug() << "before for";

        for (auto directoryItem : apiResponse.data["items"]){
            qDebug() << "in for";
            if (directoryItem["isPage"]){
                ApiMessage apiResponse2 = Api::get().apiGetPageById(directoryItem["id"]);

                if (apiResponse2.type == ApiMessage::NoError){
                    QString page;

                    if(directoryItem["isPage"])
                        page = "true";
                    else
                        page = "false";

                    QTreeWidgetItem *itemToAdd = new QTreeWidgetItem();
                    itemToAdd->setText(0, QString::fromStdString(apiResponse2.data["name"]));
                    itemToAdd->setText(1, QString::fromStdString(apiResponse2.data["id"]));
                    itemToAdd->setText(2, QString::fromStdString(apiResponse2.data["owner"]));
                    itemToAdd->setText(3, page);
                    itemToAdd->setIcon(0, fileIcon);

                    item->addChild(itemToAdd);
                }
            }
            else{
                //qDebug() << "else";
                ApiMessage apiResponse2 = Api::get().apiGetDirectoryById(directoryItem["id"]);
                //qDebug() << "else2";
                if (apiResponse2.type == ApiMessage::NoError){
                    QString page;

                    if(directoryItem["isPage"])
                        page = "true";
                    else
                        page = "false";
                    //qDebug() << "else3";
                    QTreeWidgetItem *itemToAdd = new QTreeWidgetItem();
                    itemToAdd->setText(0, QString::fromStdString(apiResponse2.data["name"]));
                    //qDebug() << "else4";
                    itemToAdd->setText(1, QString::fromStdString(apiResponse2.data["id"]));
                    //qDebug() << "else5";
                    itemToAdd->setText(2, QString::fromStdString(apiResponse2.data["owner"]));
                    //qDebug() << "else6";
                    itemToAdd->setText(3, page);
                    //qDebug() << "else7";
                    itemToAdd->setIcon(0, folderIcon);

                    item->addChild(itemToAdd);
                }
            }
        }
        loadedItems_.push_back(item->text(1).toStdString());
        pagesList_->expandItem(item);
    }

}

void ItemsList::addPage() {
    QTreeWidgetItem *selectedItem = nullptr;
    if (!pagesList_->selectedItems().empty())
        selectedItem = pagesList_->selectedItems()[0];

    bool ok;

    QString name = QInputDialog::getText(0, "Podaj nazwę strony",
                                         "Nazwa strony:", QLineEdit::Normal,
                                         "", &ok);

    if (!ok)
        return;

    QTreeWidgetItem* chosenItem;

    if (selectedItem == nullptr)
        chosenItem = nullptr;
    else if (selectedItem->text(3) == "false")
        chosenItem = selectedItem;
    else if (!selectedItem->parent()){
        chosenItem = nullptr;
    }
    else
        chosenItem = selectedItem->parent();

    if (chosenItem != nullptr)
        qDebug() << chosenItem->text(0);

    if (chosenItem == nullptr){
        ApiMessage apiResponse = Api::get().apiAddPage(name.toStdString(), Api::get().getCurrentTeam(), "root");

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            return;
        }

        QTreeWidgetItem *itemToAdd = new QTreeWidgetItem();
        itemToAdd->setText(0, QString::fromStdString(apiResponse.data["name"]));
        itemToAdd->setText(1, QString::fromStdString(apiResponse.data["id"]));
        itemToAdd->setText(2, QString::fromStdString(apiResponse.data["owner"]));
        itemToAdd->setText(3, "true");
        itemToAdd->setIcon(0, fileIcon);

        pagesList_->addTopLevelItem(itemToAdd);
    }
    else {
        ApiMessage apiResponse = Api::get().apiAddPage(name.toStdString(), Api::get().getCurrentTeam(), chosenItem->text(1).toStdString());

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            return;
        }

        QTreeWidgetItem *itemToAdd = new QTreeWidgetItem();
        itemToAdd->setText(0, QString::fromStdString(apiResponse.data["name"]));
        itemToAdd->setText(1, QString::fromStdString(apiResponse.data["id"]));
        itemToAdd->setText(2, QString::fromStdString(apiResponse.data["owner"]));
        itemToAdd->setText(3, "true");
        itemToAdd->setIcon(0, fileIcon);

        chosenItem->addChild(itemToAdd);
    }
}

void ItemsList::addDirectory() {
    QTreeWidgetItem *selectedItem = nullptr;
    if (!pagesList_->selectedItems().empty())
        selectedItem = pagesList_->selectedItems()[0];

    bool ok;

    QString name = QInputDialog::getText(0, "Podaj nazwę folderu",
                                         "Nazwa folderu:", QLineEdit::Normal,
                                         "", &ok);

    if (!ok)
        return;

    QTreeWidgetItem* chosenItem;

    if (selectedItem == nullptr)
        chosenItem = nullptr;
    else if (selectedItem->text(3) == "false")
        chosenItem = selectedItem;
    else if (!selectedItem->parent()){
        chosenItem = nullptr;
    }
    else
        chosenItem = selectedItem->parent();

    if (chosenItem != nullptr)
        qDebug() << chosenItem->text(0);

    if (chosenItem == nullptr){
        ApiMessage apiResponse = Api::get().apiAddDirectory(name.toStdString(), Api::get().getCurrentTeam(), "root");

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            return;
        }

        QTreeWidgetItem *itemToAdd = new QTreeWidgetItem();
        itemToAdd->setText(0, QString::fromStdString(apiResponse.data["name"]));
        itemToAdd->setText(1, QString::fromStdString(apiResponse.data["id"]));
        itemToAdd->setText(2, QString::fromStdString(apiResponse.data["owner"]));
        itemToAdd->setText(3, "false");
        itemToAdd->setIcon(0, folderIcon);

        pagesList_->addTopLevelItem(itemToAdd);
    }
    else {
        ApiMessage apiResponse = Api::get().apiAddDirectory(name.toStdString(), Api::get().getCurrentTeam(), chosenItem->text(1).toStdString());

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            return;
        }

        QTreeWidgetItem *itemToAdd = new QTreeWidgetItem();
        itemToAdd->setText(0, QString::fromStdString(apiResponse.data["name"]));
        itemToAdd->setText(1, QString::fromStdString(apiResponse.data["id"]));
        itemToAdd->setText(2, QString::fromStdString(apiResponse.data["owner"]));
        itemToAdd->setText(3, "false");
        itemToAdd->setIcon(0, folderIcon);

        chosenItem->addChild(itemToAdd);
    }
}

void ItemsList::clearSelection() {
    qDebug() << "clear, magical clear";
    pagesList_->clearSelection();
}

void ItemsList::prepareMenu(const QPoint &pos) {
    QTreeWidget *tree = pagesList_;

    QTreeWidgetItem *nd = tree->itemAt( pos );

    qDebug()<<pos<<nd->text(0);

    QAction *delAct = new QAction(nd->text(3) == "false" ? "Usuń folder" : "Usuń plik", this);
    QAction *renameAct = new QAction("Zmień nazwę", this);
    delAct->setStatusTip(tr("Usuń"));
    renameAct->setStatusTip(tr("Zmień nazwę"));
    connect(delAct, &QAction::triggered, this, [=](){
        deleteItem(nd);
    });
    connect(renameAct, &QAction::triggered, this, [=](){
        renameItem(nd);
    });


    QMenu menu(this);
    menu.addAction(renameAct);
    menu.addAction(delAct);

    QPoint pt(pos);
    menu.exec( tree->mapToGlobal(pos) );
}

void ItemsList::deleteItem(QTreeWidgetItem* item) {
    if (item->text(3) == "false"){ // directory
        ApiMessage apiResponse = Api::get().apiDeleteDirectory(item->text(1).toStdString());

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            return;
        }

        delete item;
    }
    else if (item->text(3) == "true"){ // page
        ApiMessage apiResponse = Api::get().apiDeletePage(item->text(1).toStdString());

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            return;
        }

        delete item;
    }
}

void ItemsList::renameItem(QTreeWidgetItem *item) {
    if (item->text(3) == "false"){ // directory
        bool ok;

        QString name = QInputDialog::getText(0, "Zmień nazwę folderu",
                                             "Nazwa folder:", QLineEdit::Normal,
                                             item->text(0), &ok);

        if (!ok)
            return;

        ApiMessage apiResponse = Api::get().apiRenameDirectory(item->text(1).toStdString(), name.toStdString());

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            return;
        }

        item->setText(0, QString::fromStdString(apiResponse.data["name"]));
    }
    else if (item->text(3) == "true"){ // page
        bool ok;

        QString name = QInputDialog::getText(0, "Zmień nazwę strony",
                                             "Nazwa strony:", QLineEdit::Normal,
                                             item->text(0), &ok);

        if (!ok)
            return;
        ApiMessage apiResponse = Api::get().apiRenamePage(item->text(1).toStdString(), name.toStdString());

        if (apiResponse.type == ApiMessage::Error){
            MessageBoxManager::get().about("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]));
            return;
        }

        item->setText(0, QString::fromStdString(apiResponse.data["name"]));
    }
}

/*
 * column 1 -> name
 * column 2 -> id
 * column 3 -> owner
 * column 4 -> isPage
 */

