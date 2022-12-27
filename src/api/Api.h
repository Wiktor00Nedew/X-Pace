//
// Created by Wiktor on 01.05.2022.
//

#pragma once

#include "../utilities/Singleton.h"
#include "../utilities/json.hpp"
#include "ApiMessage.h"
#include <string>
#include <QObject>
#include <QNetworkAccessManager>

class Api : public Singleton<Api>, public QObject{
private:
    // basic comunication with API
     ApiMessage apiPost(const std::string& url, const nlohmann::json& params, const std::string& authToken = "");
     ApiMessage apiPatch(const std::string& url, const nlohmann::json& params, const std::string& authToken = "");
     ApiMessage apiDelete(const std::string& url, const nlohmann::json& params, const std::string& authToken = "");
     ApiMessage apiGet(const std::string& url, const std::string& authToken = "");


    // API-specific variables e.g. token, url...
    std::string apiToken;
    std::string apiUrl = "http://localhost:5000/api";
public:
    void setApiToken(const std::string& token);
    const std::string& getApiToken() const;

    // public specific methods to get data from API
    ApiMessage apiUserLogin(const std::string& login, const std::string& password);
    ApiMessage apiGetUserByToken();
    ApiMessage apiRevokeToken();
};



