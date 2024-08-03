#include "LogFixtureMgr.h"
#include <assert.h>
#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QMutexLocker>
#include "MtsPath.h"
#include "MtsUtils.h"
#include "MtsLog.h"

static FILE* openLogFile(const QString& logPath, const QString& prefix = QString()){
    auto filePath = MtsUtils::getLogFilePath(logPath, prefix);
    QDir fileDir = QFileInfo(filePath).absoluteDir();
    if(!fileDir.mkpath(fileDir.path())){
        fprintf(stderr, "Failed to make dir:'%s'\n", qPrintable(fileDir.path()));
        exit(1);
    }
    FILE* fp = fopen(qPrintable(filePath), "a");
    if(!fp){
        fprintf(stderr, "Failed to open file:'%s'\n", qPrintable(filePath));
        exit(1);
    }
#ifndef MTS_UNIT_TEST
    if(MTS_LOG_LEVEL()>=2){
        printf("Open log file: '%s'\n", qPrintable(filePath));
    }
#endif
    return fp;
}

LogFixtureMgr * LogFixtureMgr::instance(const QString& logPath){
    static LogFixtureMgr mgr(logPath);
    return &mgr;
}

FILE * LogFixtureMgr::getLogFile(const QString & prefix){
    return _defaultLogFile;
}

FILE * LogFixtureMgr::getLogFile(const QString & prefix){
    QMutexLocker l(&_mutex);

    assert(!prefix.isEmpty());
    FILE*& f = _logFiles[prefix];
    if(f == nullptr){
        f = openLogFile(_logPath, prefix);
    }
    return f;
}

bool LogFixtureMgr::closeLogFile(const QString& prefix){
    QMutexLocker l(&_mutex);
    FILE*& f = _logFiles[prefix];
    if(f!=nullptr()){
        fclose(f);
    }else {
        return false;
    }
    _logFiles.remove(prefix);
    return true;
}

LogFixtureMgr::LogFixtureMgr(const QString & logPath)
    :_logPath(logPath), _defaultLogFile(nullptr){
    assert(!logPath.isEmpty());
    QMutexLocker l(&_mutex);
    _defaultLogFile = openLogFile(logPath);
}