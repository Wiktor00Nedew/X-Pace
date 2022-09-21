//
// Created by wiktor on 9/21/22.
//

#ifndef X_PACE_MAINWINDOW_H
#define X_PACE_MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>

class MainWindow : public QWidget{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
   ~MainWindow();

private:
    // layouts
    QGridLayout *mainLayout_;

    // methods


};

#endif //X_PACE_MAINWINDOW_H
