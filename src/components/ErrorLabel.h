//
// Created by Wiktor on 01.05.2022.
//

#pragma once
#include <QLabel>
#include <map>

class ErrorLabel : public QLabel{
    Q_OBJECT
public:
    explicit ErrorLabel(QWidget *parent = nullptr);
    void setError(const std::string& key);

};



