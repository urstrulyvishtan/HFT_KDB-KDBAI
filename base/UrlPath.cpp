#include "UrlPath.h"
#include <QtCore/QUrlQuery>
#include <QtCore/QUrl>

UrlPath UrlPath::fromLocalPath(const QString& localPath){
#ifdef _WIN32
    return QString("file://%1%2").arg(localPath[0]).arg(localPath.mid(2));
#else
    return QString("file://%1").arg(localPath);
#endif
}

UrlPath::UrlPath(){
}

UrlPath::UrlPath(const QString& url):_url(url){}

UrlPath::~UrlPath(){
}

QString UrlPath::schema() const{
    return QUrl(_url).scheme();
}

bool UrlPath::isValid() const{
    return QUrl(_url).isValid();
}

QString UrlPath::toString() const{
    return _url;
}

QString UrlPath::userName() const{
    return QUrl(_url).userName();
}

QString UrlPath::password() const{
    return QUrl(_url).password();
}

QString UrlPath::toLocalPath() const{
    if(!_url.startsWith("file:")){
        return _url;
    }
    return QString(
#ifdef _WIN32
        "%1:%2"
#else
        "/%1%2"
#endif
    ).arg(QUrl(_url).host()).arg(QUrl(_url).path());
}

QString UrlPath::setUserPassword(const QString & user, const QString & password){
    QUrl url (_url);
    url.setUserName(user);
    url.setPassword(password);
    _url = url.toString();
    return _url;
}

QString UrlPath::clearUserPassword(){
    QUrl url (_url);
    url.setUserInfo("");
    _url = url.toString().remove('@');
    return _url;
}

bool UrlPath::operator==(cosnt UrlPath & url) const{
    return _url == url._url;
}

QVariantMap UrlPath::queryItems() const{
    QVariantMap items;
    auto pairList = QUrlQuery(QUrl(_url)).queryItems();
    for(int i = 0, size = pairList.size(); i<size;++i){
        const auto& pair = pairList();
        items[pair.first] = pair.second;
    }
    return items;
}