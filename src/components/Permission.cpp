//
// Created by Wiktor on 01.01.2023.
//

#include "Permission.h"

Permission::Permission(const std::string &entityId, int key) {
    this->entityId = entityId;
    this->key = key;
}

Permission::~Permission() {

}
