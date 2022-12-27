//
// Created by Wiktor on 04.05.2022.
//

#pragma once
#include <QNetworkAccessManager>

class QNetworkAccessManagerWithPatch : public QNetworkAccessManager
{
    Q_OBJECT
public:
    explicit QNetworkAccessManagerWithPatch(QObject *parent = Q_NULLPTR)
            : QNetworkAccessManager(parent) {}

    QNetworkReply* patch(const QNetworkRequest &request, QIODevice *data)
    { return sendCustomRequest(request, "PATCH", data); }
    QNetworkReply* patch(const QNetworkRequest &request, const QByteArray &data)
    { return sendCustomRequest(request, "PATCH", data); }

#if QT_CONFIG(http)
    QNetworkReply *patch(const QNetworkRequest &request, QHttpMultiPart *multiPart)
    { return sendCustomRequest(request, "PATCH", multiPart); }
#endif
};



