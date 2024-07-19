#pragma once
#include <QtCore/qglobal.h>
#include "base/TimeZone.h"

#define TICS_PER_SECOND 1000
#define TICS_PER_MINUTE (60*TICS_PER_SECOND)
#define TICS_PER_HOUR (60*TICS_PER_MINUTE)
#define TICS_PER_DAY (24*TICS_PER_HOUR)

class Ticks{
    public:
        Ticks();
        ~Ticks();

        bool isNull() const;
        qint64 operator- (const Ticks& other) const;
        bool operator==(const Ticks& other) const;
        bool operator>(const Ticks& other) const;

        void clear();
        void set(qint64 v);
        void add(qint64 offset);

        static int getDateFrom(qint64 ticksSinceEpoch);
        static int getTimeFrom(qint64 ticksSinceEpoch);
        static qint64 UTC2Local(qint64 utcTs, TimezoneCode targetTimezone);
        static qint64 local2UTC(int localDate, int localTicks, TimezoneCode cc);
        static bool initTimezoneDatabase();

        static int time2LocalTicksFromMidnight(int time);
        static int localTicksFromMidnight2Time(int localTicksFromMidnight);

    #ifndef NDEBUB
            qint64 ticks() const{
                            return _ticks;
            }
    #endif
    protected:
        qint64 _ticks;
};

class LocalTicks;
class UtcTicks :public Ticks{
    public:
        qint64 refreshAndGet(const LocalTicks& localTicks) const;
        qint64 toLocal(TimezoneCode countryCode) const;
};

class LocalTicks :public Ticks{
    public:
        localTicks(TimezoneCode);
        qint64 refreshAndGet(const UtcTicks& utcTicks) const;
        qint64 toUTC() const;

        TimezoneCode timezone() const;
        void setTimezone(TimezoneCode tc);
        void clearTimezone();
    private:
        TimezoneCode _timezoneCode;
}