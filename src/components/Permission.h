//
// Created by Wiktor on 01.01.2023.
//

#pragma once
#include <string>


class Permission {
public:
    Permission(const std::string& entityId, int key);
    ~Permission();

    std::string entityId;
    int key;
};
