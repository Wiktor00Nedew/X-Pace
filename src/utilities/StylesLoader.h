//
// Created by Wiktor on 28.09.2022.
//

#pragma once

#include "Singleton.h"
#include <string>
#include <QApplication>

class StylesLoader : public Singleton<StylesLoader> {
public:
    StylesLoader();
    ~StylesLoader();

    QString readStyleFromFile(std::string filename);
};



