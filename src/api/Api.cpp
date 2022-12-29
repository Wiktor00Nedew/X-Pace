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
        qDebug() << "empty";
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
    int statusHeader = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    delete reply;

    if(apiResponse == ""){
        apiResponse = "{\"status\":404,\"message\":\"RouteNotFound\"}";
        statusHeader = 404;
    }

    //TODO logs
    //qDebug() << QString::fromStdString(apiResponse) << "\n";
    //qDebug() << statusHeader;
    return {nlohmann::json::parse(apiResponse), statusHeader};

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
    int statusHeader = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    delete reply;

    if(apiResponse == ""){
        apiResponse = "{\"status\":404,\"message\":\"RouteNotFound\"}";
        statusHeader = 404;
    }

    //TODO logs
    //qDebug() << QString::fromStdString(apiResponse) << "\n";
    //qDebug() << statusHeader;
    return {nlohmann::json::parse(apiResponse), statusHeader};

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
    int statusHeader = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    delete reply;

    if(apiResponse == ""){
        //qDebug() << "empty";
        apiResponse = "{\"status\":404,\"message\":\"RouteNotFound\"}";
        statusHeader = 404;
    }

    //TODO logs
    //qDebug() << QString::fromStdString(apiResponse) << "\n";
    //qDebug() << statusHeader;
    //qDebug() << apiResponse.empty();
    return {nlohmann::json::parse(apiResponse), statusHeader};
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

ApiMessage Api::apiGetUserByToken() {
    return apiGet(apiUrl + "/users/me", apiToken);
}

ApiMessage Api::apiRevokeToken() {
    nlohmann::json body = {
            {"all", false}
    };

    return apiPost(apiUrl + "/auth/token/revoke", body, apiToken);
}

