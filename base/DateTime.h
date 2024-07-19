#pragma once

#include <QtCore/QVariant>
#include <QtCore/QDateTime>
#include <boost/function.hpp>
#include "base/base_api.h"
#include "base/TimeZone.h"
#include "base/Ticks.h"

#define INVALID_DATE 99999999
class BASE_API DateTime{
    public:
        static DateTime now();
        static int time2LocalTicksFromMidnight(int time/*hhmmsszzz*/);
        static int localTicksFromMidnight2Time(int localTicksFromMidnight);
        static DateTime localMillisecsSinceEpoch(qint64 millsecs, TimezoneCode = TIMEZONE_CST);
        static qint64 nowToUTCMIcrosecsSinceEpoch();
        static DateTime fromQDateTime(const QdateTime&);

        DateTime();
        explicit DateTime(qint64 utcMillisecsSinceEpoch, TimezoneCode = TIMEZONE_CST);
        DateTime(int time/*210101000*/, int date, TimezoneCode = TIMEZONE_CST);
        DateTime(int localHour, int localMinute, int localSecond, int localMillisec, int localDate, TimezoneCode = TIMEZONE_CST);
        DateTime(const DateTime&);
        ~DateTime();
        qint64 toUTCMillisecsSinceEpoch()const;

        qint64 operator- (const DateTime&) const;
        DateTime operator+ (qint64) const;
        DateTime operator- (qint64) const;
        bool operator== (const DateTime&) const;
        bool operator!= (const DateTime&) const;
        bool operator> (const DateTime&) const;
        bool operator< (const DateTime&) const;
        bool operator>= (const DateTime&) const;
        bool operator<= (const DateTime&) const;

        DateTime toNextDays(int days) const;

        int date() const;
        void setDate const;
        void setTime;
        int time() const;
        int ticksSinceMidnight() const;

        int year() const;
        int month() const;
        int day() const;

        int hour() const;
        int minute() const;
        int second() const;
        int millisec() const;

        int hoursTo(const DateTime& other) const;
        int minutesTo(const DateTime& other) const;
        int secondsTo(const DateTime& other, bool plusADayIfnegative) const;
        qint64 millisecondsTo(const DateTime& other) const;

    public:
        bool isNull() const;
        bool isUTC() const;
        TimezoneCode countryCode() const;

        QString toString(QChar dateTimeSep=QChar(' ')) const;
        QString toLocalString(QChar dateTimeSep=QChar(' ')) const;

        DateTime toUTC() const;
        DateTime toLocal(TimezoneCode targetTimezone = TIMEZONE_CST) const;

        static bool initTimezoneDatabase;

        static const DateTime Null;

    private:
        void addMilliseconds(qint64 milliseconds);
        void resetToMidnight();
        void resetToNoon();
        void resetTicksSinceMidnight(int ticksFromMidnight);
        void clear();

    private:
        LocalTicks _localTicks;
        UtcTicks _utcTicks;

    #ifndef NDEBUG
        int _date;
        int _time;
    #endif

        static boost::function<DateTime()> _nowFunctor;
    public:
        static boost::function<DateTime()> setNowFunctor (boost::function<DateTime ()> nowFunctor);
    };

Q_DECLARE_METATYPE(DateTime);