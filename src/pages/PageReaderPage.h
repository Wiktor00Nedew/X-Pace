//
// Created by Wiktor on 07.01.2023.
//

#pragma once


#include <QWidget>
#include <QVBoxLayout>
#include <QTextBrowser>
#include <QStackedWidget>
#include <QPushButton>
#include "ViewPage.h"
#include "EditPage.h"

class PageReaderPage : public QWidget{
    Q_OBJECT
public:
    explicit PageReaderPage(QWidget *parent = nullptr);
    ~PageReaderPage();

private:
    void createComponents();
    void setStyling();
    void connectSignals();

    QVBoxLayout *mainLayout_;
    QStackedWidget *mainStack_;

    ViewPage *viewPage_;
    EditPage *editPage_;

};
