//
// Created by Wiktor on 28.12.2022.
//

#pragma once
#include <QLabel>

class ClickableLabel : public QLabel{
Q_OBJECT
public:
    explicit ClickableLabel(QWidget* parent = nullptr);
    ~ClickableLabel();

signals:
    void clicked();

private:
    void setStyling();

protected:
    void mousePressEvent(QMouseEvent* event);

};