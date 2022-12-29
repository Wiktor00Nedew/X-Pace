//
// Created by Wiktor on 06.05.2022.
//

#pragma once
#include <QMessageBox>
#include "../utilities/Singleton.h"

class MessageBoxManager : public QWidget, public Singleton<MessageBoxManager>{
    Q_OBJECT
public:
    explicit MessageBoxManager(QWidget *parent = nullptr);
    ~MessageBoxManager();

    bool question(const QString& title, const QString& body);
    bool warning(const QString& title, const QString& body);
    bool critical(const QString& title, const QString& body);
    bool about(const QString& title, const QString& body);
};



