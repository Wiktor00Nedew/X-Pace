//
// Created by Wiktor on 01.05.2022.
//

#include <iostream>
#include "Api.h"
#include "../utilities/QNetworkAccessManagerWithDelete.h"
#include "../utilities/QNetworkAccessManagerWithPatch.h"
#include <QEventLoop>
#include <QNetworkReply>
#include <QHttpPart>


ApiMessage Api::apiPost(const std::string& url, const nlohmann::json& params, const std::string& authToken) {
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QByteArray data = QByteArray::fromStdString(params.dump());

    QNetworkRequest req(QUrl(QString::fromStdString(url)));
    req.setRawHeader("Authorization", QByteArray::fromStdString(authToken));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = mgr.post(req, data);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    std::string apiResponse = (reply->readAll()).toStdString();
    QVariant statusHeader = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    delete reply;

    int statusCode = statusHeader.toInt();

    if(!statusHeader.isValid()){
        //qDebug() << "empty";
        apiResponse = "{\"status\":404,\"message\":\"RouteNotFound\"}";
        statusCode = 404;
    }

    if(statusHeader.isValid() && apiResponse.empty()){
        apiResponse = "{\"data\":\"no\"}";
    }

    //qDebug() << "here";
    //TODO logs
    //qDebug() << QString::fromStdString(apiResponse) << "\n";
    //qDebug() << statusHeader;
    //nlohmann::json::parse(apiResponse);
    //qDebug() << apiResponse.empty();
    return {nlohmann::json::parse(apiResponse), statusCode};

}

ApiMessage Api::apiPatch(const std::string& url, const nlohmann::json& params, const std::string& authToken) {
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManagerWithPatch mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QByteArray data = QByteArray::fromStdString(params.dump());

    QNetworkRequest req(QUrl(QString::fromStdString(url)));
    req.setRawHeader("Authorization", QByteArray::fromStdString(authToken));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = mgr.patch(req, data);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    std::string apiResponse = (reply->readAll()).toStdString();
    QVariant statusHeader = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    delete reply;

    int statusCode = statusHeader.toInt();

    if(!statusHeader.isValid()){
        //qDebug() << "empty";
        apiResponse = "{\"status\":404,\"message\":\"RouteNotFound\"}";
        statusCode = 404;
    }

    if(statusHeader.isValid() && apiResponse.empty()){
        apiResponse = "{\"data\":\"no\"}";
    }

    //TODO logs
    //qDebug() << QString::fromStdString(apiResponse) << "\n";
    //qDebug() << statusHeader;
    return {nlohmann::json::parse(apiResponse), statusCode};

}

ApiMessage Api::apiDelete(const std::string& url, const nlohmann::json& params, const std::string& authToken) {
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManagerWithDelete mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QByteArray data = QByteArray::fromStdString(params.dump());

    QNetworkRequest req(QUrl(QString::fromStdString(url)));
    req.setRawHeader("Authorization", QByteArray::fromStdString(authToken));
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = mgr.deleteRequest(req, data);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    std::string apiResponse = (reply->readAll()).toStdString();
    QVariant statusHeader = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    delete reply;

    int statusCode = statusHeader.toInt();

    if(!statusHeader.isValid()){
        //qDebug() << "empty";
        apiResponse = "{\"status\":404,\"message\":\"RouteNotFound\"}";
        statusCode = 404;
    }

    if(statusHeader.isValid() && apiResponse.empty()){
        apiResponse = "{\"data\":\"no\"}";
    }

    //TODO logs
    //qDebug() << QString::fromStdString(apiResponse) << "\n";
    //qDebug() << statusHeader;
    return {nlohmann::json::parse(apiResponse), statusCode};

}

ApiMessage Api::apiGet(const std::string& url, const std::string& authToken) {
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req(QUrl(QString::fromStdString(url)));
    req.setRawHeader("Authorization", QByteArray::fromStdString(authToken));
    QNetworkReply *reply = mgr.get(req);
    eventLoop.exec(); // blocks stack until "finished()" has been called

    std::string apiResponse = (reply->readAll()).toStdString();
    QVariant statusHeader = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    delete reply;

    int statusCode = statusHeader.toInt();

    if(!statusHeader.isValid()){
        //qDebug() << "empty";
        apiResponse = "{\"status\":404,\"message\":\"RouteNotFound\"}";
        statusCode = 404;
    }

    //qDebug() << QString::fromStdString(apiResponse);

    if(statusHeader.isValid() && apiResponse.empty()){
        apiResponse = "{\"data\":\"no\"}";
    }

    //TODO logs
    //qDebug() << QString::fromStdString(apiResponse) << "\n";
    //qDebug() << statusHeader;
    //qDebug() << apiResponse.empty();
    return {nlohmann::json::parse(apiResponse), statusCode};
}

ApiMessage Api::apiUserLogin(const std::string &login, const std::string &password) {
    nlohmann::json body = {
            {"email", login},
            {"password", password}
    };

    return apiPost(apiUrl + "/auth/login", body);
}

ApiMessage Api::apiUserRegister(const std::string &username, const std::string &email, const std::string &password) {
    nlohmann::json body = {
            {"username", username},
            {"email", email},
            {"password", password}
    };

    return apiPost(apiUrl + "/auth/register", body);
}

void Api::setApiToken(const std::string &token) {
    apiToken = token;
}

const std::string &Api::getApiToken() const {
    return apiToken;
}

ApiMessage Api::apiFetchUser() {
    ApiMessage apiResponse = apiGet(apiUrl + "/users/me", apiToken);

    if (apiResponse.type == ApiMessage::NoError)
        apiUser = apiResponse.data;

    return apiResponse;
}

ApiMessage Api::apiRevokeToken() {
    nlohmann::json body = {
            {"all", false}
    };

    return apiPost(apiUrl + "/auth/token/revoke", body, apiToken);
}

ApiMessage Api::apiGetTeamById(const std::string& id) {
    return apiGet(apiUrl + "/teams/" + id, apiToken);
}

nlohmann::json Api::getUser() {
    return apiUser;
}

ApiMessage Api::apiCreateTeam(const std::string& name) {
    nlohmann::json body = {
            {"name", name}
    };
    return apiPost(apiUrl + "/teams/create", body, apiToken);
}

ApiMessage Api::apiDeleteTeam(const std::string &teamId) {
    nlohmann::json body = {
            {"teamId", teamId}
    };
    return apiDelete(apiUrl + "/teams/delete", body, apiToken);
}

ApiMessage Api::apiGetDirectoryById(const std::string &directoryId) {
    //qDebug() << "maybe here";
    return apiGet(apiUrl + "/directories/" + directoryId, apiToken);
}

ApiMessage Api::apiGetPageById(const std::string &pageId) {
    return apiGet(apiUrl + "/pages/" + pageId, apiToken);
}

ApiMessage Api::apiAddPage(const std::string &name, const std::string &team, const std::string &parentDirectory,
                           const std::string &content) {
    nlohmann::json body = {
            {"name", name},
            {"team", team},
            {"parentDirectory", parentDirectory},
            {"content", content}
    };
    ApiMessage message = apiPost(apiUrl + "/pages/create", body, apiToken);
    //qDebug() << QString::fromStdString(message.data.dump());
    return message;
}

ApiMessage Api::apiAddDirectory(const std::string &name, const std::string &team, const std::string &parentDirectory) {
    nlohmann::json body = {
            {"name", name},
            {"team", team},
            {"parentDirectory", parentDirectory},
    };
    return apiPost(apiUrl + "/directories/create", body, apiToken);
}

void Api::setCurrentTeam(const std::string &currentTeam) {
    this->currentTeam = currentTeam;
}

const std::string& Api::getCurrentTeam(){
    return currentTeam;
}

ApiMessage Api::apiDeletePage(const std::string &pageId) {
    nlohmann::json body = {
            {"pageId", pageId}
    };

    return apiDelete(apiUrl + "/pages/delete", body, apiToken);
}

ApiMessage Api::apiDeleteDirectory(const std::string &directoryId) {
    nlohmann::json body = {
            {"directoryId", directoryId}
    };

    return apiDelete(apiUrl + "/directories/delete", body, apiToken);
}

ApiMessage Api::apiRenameDirectory(const std::string &directoryId, const std::string &name) {
    nlohmann::json body = {
            {"directoryId", directoryId},
            {"name", name}
    };

    return apiPatch(apiUrl + "/directories/name", body, apiToken);
}

ApiMessage Api::apiRenamePage(const std::string &pageId, const std::string &name) {
    nlohmann::json body = {
            {"pageId", pageId},
            {"name", name}
    };

    return apiPatch(apiUrl + "/pages/name", body, apiToken);
}

ApiMessage Api::apiEditPage(const std::string &pageId, const std::string &content) {
    nlohmann::json body = {
            {"pageId", pageId},
            {"content", content}
    };

    return apiPatch(apiUrl + "/pages/edit", body, apiToken);
}

ApiMessage Api::apiGetNameForUserById(const std::string &id) {
    return apiGet(apiUrl + "/users/name/" + id);
}

ApiMessage Api::apiRenameTeam(const std::string &teamId, const std::string &name) {
    nlohmann::json body = {
            {"teamId", teamId},
            {"name", name}
    };

    return apiPatch(apiUrl + "/teams/name", body, apiToken);
}

ApiMessage Api::apiGenerateMemberCode(const std::string &teamId) {
    nlohmann::json body = {
            {"teamId", teamId}
    };

    return apiPost(apiUrl + "/teams/member", body, apiToken);
}

ApiMessage Api::apiGenerateModeratorCode(const std::string &teamId) {
    nlohmann::json body = {
            {"teamId", teamId}
    };

    return apiPost(apiUrl + "/teams/moderator", body, apiToken);
}

ApiMessage Api::apiGenerateOwnerCode(const std::string &teamId) {
    nlohmann::json body = {
            {"teamId", teamId}
    };

    return apiPost(apiUrl + "/teams/owner", body, apiToken);
}

ApiMessage Api::apiJoinTeam(const std::string &teamToken) {
    nlohmann::json body = {
            {"tokenId", teamToken}
    };

    return apiPost(apiUrl + "/teams/token/register", body, apiToken);
}

ApiMessage Api::apiDeletePagePermission(const std::string &pageId, const std::string &entityId, const int accessLevel) {
    nlohmann::json body = {
            {"pageId", pageId},
            {"permission", {
                        {"entityId", entityId},
                        {"key", accessLevel}
            }}
    };

    return apiDelete(apiUrl + "/pages/permission", body, apiToken);
}

ApiMessage Api::apiAddPagePermission(const std::string &pageId, const std::string &entityId, const int accessLevel) {
    nlohmann::json body = {
            {"pageId", pageId},
            {"permission", {
                    {"entityId", entityId},
                    {"key", accessLevel}
            }}
    };

    return apiPost(apiUrl + "/pages/permission", body, apiToken);
}

ApiMessage Api::apiDeleteDirectoryPermission(const std::string &pageId, const std::string &entityId, const int accessLevel) {
    nlohmann::json body = {
            {"directoryId", pageId},
            {"permission", {
                    {"entityId", entityId},
                    {"key", accessLevel}
            }}
    };

    return apiDelete(apiUrl + "/directories/permission", body, apiToken);
}

ApiMessage Api::apiAddDirectoryPermission(const std::string &pageId, const std::string &entityId, const int accessLevel) {
    nlohmann::json body = {
            {"directoryId", pageId},
            {"permission", {
                    {"entityId", entityId},
                    {"key", accessLevel}
            }}
    };

    return apiPost(apiUrl + "/directories/permission", body, apiToken);
}


