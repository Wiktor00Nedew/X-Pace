//
// Created by Wiktor on 07.01.2023.
//

#pragma once


#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QTextBrowser>

class ViewPage : public QWidget{
    Q_OBJECT
public:
    explicit ViewPage(QWidget *parent = nullptr);
    ~ViewPage();

private:
    std::string pageId_;

    void createComponents();
    void setStyling();
    void connectSignals();

    QVBoxLayout *mainLayout_;

    QTextBrowser *markdownView_;
    QPushButton *editButton_;

public slots:
    void loadPage(const std::string& pageId);

signals:
    void editingPage(const std::string& pageId);
    void settingDefaultPage();
};
