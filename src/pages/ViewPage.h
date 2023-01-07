//
// Created by Wiktor on 07.01.2023.
//

#pragma once


#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

class ViewPage : public QWidget{
    Q_OBJECT
public:
    explicit ViewPage(QWidget *parent = nullptr);
    ~ViewPage();

private:
    void createComponents();
    void setStyling();
    void connectSignals();

    QVBoxLayout *mainLayout_;

    QTextEdit *markdownView_;
    QPushButton *saveButton_;

};
