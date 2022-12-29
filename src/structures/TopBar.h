//
// Created by Wiktor on 29.12.2022.
//

#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QComboBox>
#include "../components/DropdownButton.h"

class TopBar : public QWidget{
    Q_OBJECT
public:
    explicit TopBar(QWidget *parent = nullptr);
    ~TopBar();

    void setUsername(const QString &name);

private:
    QHBoxLayout *mainLayout_;
    DropdownButton *userMenu_;
    QComboBox *teamMenu_;

    void createComponents();
    void setStyling();
    void connectSignals();

signals:
    void logedOut();

};
