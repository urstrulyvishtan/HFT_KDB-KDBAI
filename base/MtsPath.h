#pragma once
#include <QtCore/QString>
#include <boost/function.hpp>
#include "base/base_api.h"
#include "MtsType.h"

#define DAILY_BAR_INTERVAL 86400000 //millisecs

class BASE_API MtsPath{
    public:
        static QString appDirPath();

        static QString mtsDirPath(bool hasColon = true);
        static QString configDirPath();
        static QString testDirPath();
        static QString docDirPath();
        static QString logDirPath();

        static QString metaInfoFilePath(mts::InstrumentType, int date, const QString& dataType = "fmd", const QString& dataDirPath = MtsPath::dataDirPath());

        static QString fmdDirPath(mts::InstrumentType, const QString& dataDirPath = MtsPath::dataDirPath());
        static QStringList fmdFilePath(mts::InstrumentType, int date, const QString& symbol, const QString& dataDirPath = MtsPath::dataDirPath());
        enum BarInterval {BI_15M = 15, BI_60M = 60, BI_DAILY = DAILY_BAR_INTERVAL};
        static QString bkdDirPath(mts::InstrumentType, int sec, const QString& dataDirPath = MtsPath::dataDirPath());
        static QString bkdFilePath(mts::InstrumentType, int sec, int date, const QString& symbol, const QString& dataDirPath = MtsPath::dataDirPath());


        static QString mtsScriptDirPath();
        static QString workspaceDirPath();
        static QString searchDirPath(const QString& basePath, const QString& dirName);
        static QString dataDirPath();
    public:
        static void setScriptDirPath(const QString&);
    private:
        static QString searchFilePath(const QString& basePath, const QString& dirName, const QString& fileName);
        static QString searchPath(const QString& basePath, const QString& dirName, const boost::function<bool(const QString&)>& isMatch);
        static QString _scriptDirPath;
};