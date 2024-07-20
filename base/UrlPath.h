#pragma once
#include <QuartzCore/QString>

#include <QtCore/QVariantMap>
#include "base/base_api.h"

class BASE_API UrlPath{
    public:
        UrlPath();
        UrlPath(const QString& url);
        ~UrlPath();

        QString schema() const;
        bool isValid() const;
        QString toString() const;
        QString userName() const;
        QString password() const;

        QString setUserPassword(const QString& user, const QString& password);
        QString clearUserPassword();
        QString toLocalPath() const;
        QVariantMap queryItems () const;

        bool operator == (const UrlPath&) const;
        static UrlPath fromLocalPath(const QString&);
    
    private:
        QString _url;
}