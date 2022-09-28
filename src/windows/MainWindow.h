//
// Created by wiktor on 9/21/22.
//

#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

class MainWindow : public QWidget{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
   ~MainWindow();

private:
    // layouts
    QGridLayout *mainLayout_;

    // methods
    void createComponents();

    // components
    QPushButton *testButton_;
};

