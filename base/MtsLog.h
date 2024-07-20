#pragma once
#include <QtCore/QDateTime>
#include <QtCore/QThread>
#include <QtCore/QMutex>
#include <QtCore/QTime>
#include <QtCore/QByteArray>
#include <stdio.h>
#include <stdlib.h>
#include "base/base_api.h"

#ifdef NDEBUG
#endif

class BASE_API ThreadNameRegister{
    public:
        static ThreadNameRegister* instance();
        void registerThread(qlonglong threadId, const QString& threadName);
        qlonglong registerCurrentThread(const QString& threadName);
        QString findThreadName(qlonglong threadid);
        QString currentThreadName();
    private:
        QMutex _mutex;
        QHash<qlonglong, QString> _threadName;
};

#define LOGEX(format) "[%s@%s]" format,__FUNCTION__,qPrintable(ThreadNameRegister::instance()->currentThreadName())

void BASE_API SET_MTS_LOG_LEVEL(int);
int BASE_API MTS_LOG_LEVEL();

BASE_API void MTS_SET_FP_PATH(const char* logFilePath);

BASE_API FILE *MTS_FP();

#define TIMESTAMP(format) "[%s]" format, qPrintable(QTime::currentTime().toString("hh:mm:ss.zzz"))

BASE_API FILE *MTS_FP_PREFIX(const char* prefix);

#ifdef MTS_LOG_DISABLED
    #ifdef _WIN32
        #define MTS_LOG __noop
        #define MTS_WARN __noop
        #define MTS_ERROR __noop
        #define MTS_FILE __noop
        #define MTS_FILE_RAW __noop
        #define MTS_DEBUG __noop
        #define MTS_LOG_FILE __noop

    #else  
        #define MTS_LOG
        #define MTS_WARN
        #define MTS_ERROR
        #define MTS_FILE
        #define MTS_FILE_RAW
        #define MTS_DEBUG
        #define MTS_LOG_FILE
    #endif
#else
#define MTS_LOG(format, ...) qInfor(LOGEX(format), ##__VA_ARGS__)
#define MTS_WARN(format, ...) qWarning(LOGEX(format), ##__VA_ARGS__)
#define MTS_ERROR(format, ...) qCritical(LOGEX(format), ##__VA_ARGS__)
#define MTS_FILE(format, ...) qInfo(LOGEX(format), ##__VA_ARGS__)
#define MTS_FILE_RAW(format, ...) fprintf(MTS_FP(), format, ##__VA_ARGS__);\
    fflush(MTS_FP());

#define MTS_LOG_FILE(prefix, format, ...)\
        fprintf(MTS_FP_PREFIX(prefix), format, ##__VA_ARGS__);\
        fflush(MTS_FP_PREFIX(prefix));

#ifndef NDEBUG
#define MTS_DEBUG(format, ...) qDebug(LOGEX(format), ##__VA_ARGS__)
#else
#ifdef _WIN32
#define MTS_DEBUG __noop
#else
#define MTS_DEBUG
#endif
#endif
#endif
#define MTS_PREF_FILE(format, ...)\
    fprintf(MTS_FP_PREFIX("pref"), format, ##__VA_ARGS__);\
    fflush(MTS_FP_PREFIX("pref"));

typedef void(*LogToFixtureFunc)(const QString&);

BASE_API LogToFixtureFunc setLogFixtureHook(QtMsgType type, LogToFixtureFunc hook);

BASE_API void clearLogFixtureHook(QtMsgType type);