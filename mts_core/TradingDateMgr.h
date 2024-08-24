#pragma once
#include "mts_core_api.h"
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QPair>
#include "base/DateTime.h"
#include "mts_core/enums.h"

namespace mts{
    enum TradingDateTimeCheckMode{
        TCM_EXACT,
        TCM_ROUND
    };
    class MTS_CORE_API TradingDateMgr{
    public:
        static bool init(const QString& configDir, bool is24H);
        static TradingDateMgr* instance();

        virtual int nextDate(int dt) const = 0;
        virtual int prevDate(int dt) const = 0;
        virtual int forceToDate(int dt) const = 0;

        virtual int tradingDate(const DateTime& realDateTime) const = 0;
        virtual bool isTradingDate(int dt) const = 0;
        virtual bool isHalfTradingDate(int dt) const = 0;
        virtual bool isTradingTime(const DateTime& dt, TradingDateTimeCheckMode = TCM_EXACT) const = 0;

        virtual int realDate(int tradingDate, int realTime) const = 0;

        virtual int nextDate(int dt, int n) const = 0;
        virtual int countTradingDay(int begDt, int endDt) = 0;

        virtual int openTradingTime(int dt = INVALID_DATE) const = 0;
        virtual int closeTradingTime(int dt = INVALID_DATE) const = 0;
        virtual DateTime nextTime(int futureTime, const DateTime& baseTime) const = 0;
    private:
        static TradingDateMgr* _instance;
    };
}