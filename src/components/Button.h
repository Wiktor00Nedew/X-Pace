//
// Created by Wiktor on 29.12.2022.
//

#pragma once


#include <QPushButton>

class Button : public QPushButton{
Q_OBJECT
public:
    explicit Button(QWidget *parent = nullptr);
    ~Button();
};
