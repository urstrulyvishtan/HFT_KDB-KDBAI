#pragma once
#include <QtCore/QString>
#include <QtCore/QObject>
#include "base/base_api.h"
#ifdef _WIN32
#include <windows.h>

class BASE_API Library{
    public:
        Library(QObject *parent = Q_NULLPTR);
        Library(const QString &fileName, QObject *parent = Q_NULLPTR);
        ~Library();

        QString errorString() const;
        QString fileName() const;
        bool isLoaded() const;
        bool load();
        QFunctionPointer resolve(const char* symbol);
        void setFileName(const QString&);
        void unload();
    private:
        QString _fileName;
        QString _errorString;
        HMODULE _dllHandle;

};

#else
#include <QtCore/QLibrary>

typedef QLibrary Library;

#endif