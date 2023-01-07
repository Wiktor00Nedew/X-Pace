//
// Created by Wiktor on 07.01.2023.
//

#pragma once


#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

class EditPage : public QWidget{
    Q_OBJECT
public:
    explicit EditPage(QWidget *parent = nullptr);
    ~EditPage();

private:
    void createComponents();
    void setStyling();
    void connectSignals();

    QVBoxLayout *mainLayout_;

    QTextEdit *markdownEdit_;
    QPushButton *editButton_;
};
