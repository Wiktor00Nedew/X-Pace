//
// Created by Wiktor on 28.12.2022.
//

#pragma once
#include <QLabel>

class Title : public QLabel{
Q_OBJECT
public:
    explicit Title(QWidget* parent = nullptr);
    ~Title();
};
