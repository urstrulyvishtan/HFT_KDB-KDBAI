#pragma once 
#include <QtCore/QByteArray>
#include <QtCore/QString>
#include <QtCore/QFileInfo>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QMap>
#include <QtCore/QDateTime>
#include "base/base_api.h"

#ifndef utf8Printable
# define utf8Printable(string) string.toUtf8().constData()
#endif

#define ParseJsonObject(str, ok)\
        QJsonParseError jsonError; \ 
        QJsonDocument jsonDoc = QJsonDocument::fromJson(str.c_str(), &jsonError); \
        if(jsonError.error != QJsonParseError::NoError){\
            MTS_ERROR("invalid json msg:%s, error:%s\n", str.c_str(), qPrintable(jsonError.errorString())); \
            ok = false; \
        } else if(!jsonDoc.isObject()){\
            MTS_ERROR("invalid json object msg:%s\n", str.c_str()); \
            ok = false; \
        } else { \
            ok = true; \
        }
    
#define ParseJsonArray(str,ok)\
        QJsonParseError jsonError; \ 
        QJsonDocument jsonDoc = QJsonDocument::fromJson(str.c_str(), &jsonError); \
        if(jsonError.error != QJsonParseError::NoError){\
            MTS_ERROR("invalid json msg:%s, error:%s\n", str.c_str(), qPrintable(jsonError.errorString())); \
            ok = false; \
        } else if(!jsonDoc.isArray()){\
            MTS_ERROR("invalid json array msg:%s\n", str.c_str()); \
            ok = false; \
        } else { \
            ok = true; \
        }

class BASE_API MtsUtils{
    public:
        static QByteArray toUtf8(const char* str);
        static QString getUserName();
        static QString getLogFilePath(const QString& logPath, const QString& prefix);

        static bool touchFile(const QString& filePath);
        static void listFiles(const QString& path, QStringList& files);
        static QFileInfoList getMtsLogs(const QString& logDir);

        static QString getLastErrorMessage();
        static QString getSymbolFromFileName(const QString&);
        static bool parseJsonFileAsObject(const QString& filePath, QJsonObject& jsonObj);
        static QJsonObject str2Json(const QString& str);
        static QString json2Str(const QJsonObject& json);
        static QString getBuildDateStr();
        static QString getMachineHostName();
        static QString buildUrlQueryString(const QMap<QString, QString>& params);
        static QDateTime getUTCTimeFromISO8601(const QString& tmsp);
        static qint64 getTimeStampFromISO8601(const QString& tmsp);
        static QString getISO8601TimeString(qint64 tmsp);
};