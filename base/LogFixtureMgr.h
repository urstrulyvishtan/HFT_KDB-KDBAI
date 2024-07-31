#pragma once
#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtCore/QMutex>

class LogFixtureMgr{
    public:
        static LogFixtureMgr* instance(const QString logPath = QString());
        FILE* getLogFile();
        FILE* getLogFile(const QString& prefix);
        bool closeLogFile(const QString& prefix);
    private:
        LogFixtureMgr(const QString& logPath);
        QMutex _mutex;
        const QString _logPath;
        QHash<QString, FILE*> _logFiles;
        FILE* _defaultLogFile;
}