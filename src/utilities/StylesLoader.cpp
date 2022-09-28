//
// Created by Wiktor on 28.09.2022.
//

#include "StylesLoader.h"
#include <fstream>

QString StylesLoader::readStyleFromFile(std::string filename) {
    std::ifstream cssFile(filename);
    QString cssFileContents;
    std::string line;

    while(std::getline(cssFile, line)) {
        cssFileContents += QString::fromStdString(line);
    }
    cssFile.close();

    return cssFileContents;
}

StylesLoader::~StylesLoader() {

}

StylesLoader::StylesLoader() {

}
