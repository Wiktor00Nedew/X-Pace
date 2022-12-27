//
// Created by Wiktor on 27.12.2022.
//

#pragma once
#include <QLabel>
#include <QMovie>

class LoadingIndicator : public QLabel{
Q_OBJECT
public:
    explicit LoadingIndicator(QWidget *parent = nullptr);
    ~LoadingIndicator();

private:
    QMovie *loadingAnimation;
};




