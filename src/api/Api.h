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
    std::string currentTeam;
    std::string apiUrl = "http://localhost:5000/api";

    nlohmann::json apiUser;
public:
    void setApiToken(const std::string& token);
    const std::string& getApiToken() const;

    // public specific methods to get data from API
    ApiMessage apiUserLogin(const std::string& login, const std::string& password);
    ApiMessage apiUserRegister(const std::string &username, const std::string &email, const std::string &password);
    ApiMessage apiFetchUser();
    ApiMessage apiRevokeToken();
    ApiMessage apiGetTeamById(const std::string& id);
    ApiMessage apiCreateTeam(const std::string& name);
    ApiMessage apiDeleteTeam(const std::string& teamId);
    ApiMessage apiGetPageById(const std::string& pageId);
    ApiMessage apiGetDirectoryById(const std::string& directoryId);
    ApiMessage apiAddPage(const std::string& name, const std::string& team, const std::string& parentDirectory, const std::string& content = ".");
    ApiMessage apiAddDirectory(const std::string& name, const std::string& team, const std::string& parentDirectory);
    ApiMessage apiDeletePage(const std::string& pageId);
    ApiMessage apiDeleteDirectory(const std::string& directoryId);
    ApiMessage apiRenameDirectory(const std::string& directoryId, const std::string& name);
    ApiMessage apiRenamePage(const std::string& pageId, const std::string& name);


    nlohmann::json getUser();
    void setCurrentTeam(const std::string& currentTeam);
    const std::string& getCurrentTeam();
};



