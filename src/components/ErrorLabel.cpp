//
// Created by Wiktor on 01.05.2022.
//

#include "ErrorLabel.h"
#include "../utilities/common.h"

ErrorLabel::ErrorLabel(QWidget *parent) {

}

void ErrorLabel::setError(const std::string& key) {
    setText(QString::fromStdString(APIErrors[key]));
}
