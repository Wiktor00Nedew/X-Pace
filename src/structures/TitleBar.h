//
// Created by Wiktor on 16.11.2022.
//

#pragma once

#include <QWidget>
#include <QLabel>
#include <QEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QPushButton>
#include <QHBoxLayout>

class TitleBar : public QWidget{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);
    ~TitleBar();

private:
    QPoint cursor_;
    QLabel *windowTitle_;
    QWidget *parent_;
    QPushButton *testButton;
    QHBoxLayout *mainLayout;

    void setStyling();
    void createComponents();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};
