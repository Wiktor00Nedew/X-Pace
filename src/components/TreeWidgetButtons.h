//
// Created by Wiktor on 01.01.2023.
//

#pragma once


#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

class TreeWidgetButtons : public QWidget{
Q_OBJECT
public:
    explicit TreeWidgetButtons(QWidget *parent = nullptr);
    ~TreeWidgetButtons();

    void createComponents();
    void setStyling();
    void connectSignals();

    void setDisableManage(bool disabled);
    void setDisableDelete(bool disabled);

private:
    QHBoxLayout *mainLayout_;

    // buttons
    QPushButton *addDirectoryButton_;
    QPushButton *addPageButton_;

signals:
    void addDirectoryButtonClicked();
    void addPageButtonClicked();

};
