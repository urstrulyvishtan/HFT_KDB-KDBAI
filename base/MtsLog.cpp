#include "MtsLog.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QThreadStorage>
#include "base/DateTime.h"
#include <QtCore/QMutexLocker>
#include "LogFixtureMgr.h"

#define DEFAULT_LOG_LEVEL 2

ThreadNameRegister *ThreadNameRegister::instance(){
    static ThreadNameRegister tnRegister;
    return &tnRegister;
}

void ThreadNameRegister::registerThread(qlonglong threadId, const QString & threadName){
    QMutexLocker l(&_mutex);
    _threadNameMap[threadId] = threadName;
}

qlonglong ThreadNameRegister::registerCurrentThread(const QString & threadName){
    qlonglong id = (qlonglong)QThread::currentThreadId();
    registerThread(id, threadName);
    return id;
}

QString ThreadNameRegister::findThreadName(qlonglong threadId){
    QMutexLocker l(&_mutex);
    QString tname =_threadNameMap.value(threadId);
    if(tname.isNull()){
        return QString::number(threadId);
    }else{
        return tname;
    }
}

QString ThreadNameRegister::currentThreadName(){
    return findThreadName((qlonglong)QThread::currentThreadId());
}

inline
void doLogToStdout(const char* text){
    fprintf(stdout, "%s\n", text);
    fflush(stdout);
}

inline 
void doLogToFile(const char* text){
    auto logFile = MTS_FP();
    if(stdout!=logFile && stderr!=logFile){
        fprintf(logFile, "%s\n", text);
        fflush(logFile);
    }
}

inline 
void doLogToStderr(const char* text){
    fprintf(stderr, "%s\n", text);
    fflush(stderr);
}   

void logToStdoutAndFile(const QString& text){
    auto textLocal = text.toLocal8Bit();
    const char* textAsc = textLocal.constData();
    doLogToStdout(textAsc);
    doLogToFile(textAsc);
}

void logToStderrAndFile(const QString& text){
    auto textLocal = text.toLocal8Bit();
    const char* textAsc = textLocal.constData();
    doLogToStderr(textAsc);
    doLogToFile(textAsc);
}

void logToFileOnly(const QString& text){
    doLogToFile(qPrintable(text));
}

void logToBlackHole(const QString&){}

static LogToFixtureFunc LOG_FIXTURE_FUNCS_LIST[3][5] = {
    {logToBlackHole, logToBlackHole, logToStderrAndFile, logToStderrAndFile, logToBlackHole},
    {logToFileOnly, logToFileOnly, logToStderrAndFile, logToStderrAndFile, logToFileOnly},
    {logToStdoutAndFile, logToStderrAndFile, logToStderrAndFile, logToStderrAndFile, logToStdoutAndFile}
};

static int LOG_LEVEL = DEFAULT_LOG_LEVEL;
static LogToFixtureFunc* LOG_FIXTURE_FUNCS = LOG_FIXTURE_FUNCS_LIST[DEFAULT_LOG_LEVEL];
static const char* LOG_FIXTURE_PREFIX[5] = {"DBG", "WRN", "ERR", "EMG", "INFO"};
static LogToFixtureFunc LOG_FIXTURE_HOOK_FUNCS[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};

LogToFixtureFunc setLogFixtureHook(QtMsgType type, LogToFixtureFunc hook){
    auto prevHook = LOG_FIXTURE_HOOK_FUNCS[type];
    LOG_FIXTURE_HOOK_FUNCS[type] = hooks;
    return prevHook;
}

void clearLogFixtureHook(QtMsgType type){
    LOG_FIXTURE_HOOK_FUNCS[type] = nullptr;
}

inline
QString genOutputText(QtMsg type, const QMessageLogContext &, const QString &msg){
    auto localMsg = msg;
    if(!msg.endsWith('\n')){
        localMsg += '\n';
    }
    auto nowStr = DateTime::now().toLocalString();
    return QString("[%1] %2:%3").arg(nowStr).arg(LOG_FIXTURE_PREFIXS[type]).arg(localMsg);
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg){
    #ifdef NDEBUG
    if(type==QtDebugMsg){
        return;
    }
    #endif
        auto text = genOutputText(type, context, msg);
        if(auto func = LOG_FIXTURE_HOOK_FUNCS[type]){
            func(text);
        }
        LOG_FIXTURE_FUNCS[type](text);
        if(type==QtFatalMsg){
            abort();
        }
}

void BASE_API SET_MTS_LOG_LEVEL(int level){
    if(level<0||level>2){
        MTS_ERROR("SET_MTS_LOG_LEVEL should be 0~2\n");
        return;
    }
    LOG_LEVEL = level;
    LOG_FIXTURE_FUNCS = LOG_FIXTURE_FUNCS_LIST[level];
    MTS_DEBUG("SET_MTS_LOG_LEVEL %d\n", level);
}

int MTS_LOG_LEVEL(){
    return LOG_LEVEL;
}

static qlonglong MAIN_THREAD_ID = [](){
    auto id = ThreadNameRegister::instance()->registerCurrentThread("mainThread");
#ifndef MTS_LOG_DISABLED
    qInstallMessageHandler(myMessageOutput);
#endif
    return id;
}();

static voaltile bool LOG_FIXTURE_MGR_INITALIZED = false;

FILE *MTS_FP(){
    if(!LOG_FIXTURE_MGR_INITALIZED){
        return LogFixtureMgr::instance()->getLogFile(prefix);
    }else{
        return stdout;
    }
}

void MTS_SET_FP_PATH(const char* logFilePath){
    LogFixtureMgr::instance(logFilePath);
    LOG_FIXTURE_MGR_INITALIZED = true;
}
