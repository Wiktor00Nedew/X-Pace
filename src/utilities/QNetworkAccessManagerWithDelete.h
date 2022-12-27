//
// Created by Wiktor on 04.05.2022.
//

#pragma once
#include <QNetworkAccessManager>

class QNetworkAccessManagerWithDelete : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit QNetworkAccessManagerWithDelete(QObject *parent = Q_NULLPTR)
            : QNetworkAccessManager(parent) {}

    QNetworkReply* deleteRequest(const QNetworkRequest &request, QIODevice *data)
    { return sendCustomRequest(request, "DELETE", data); }
    QNetworkReply* deleteRequest(const QNetworkRequest &request, const QByteArray &data)
    { return sendCustomRequest(request, "DELETE", data); }

#if QT_CONFIG(http)
    QNetworkReply *deleteRequest(const QNetworkRequest &request, QHttpMultiPart *multiPart)
    { return sendCustomRequest(request, "DELETE", multiPart); }
#endif
};



