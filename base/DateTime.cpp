#include "DateTime.h"
#include <boost/exception/all.hpp>
#include <boost/chrono/chrono.cpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <QtCore/QTimeZone>
#include "base/MtsLog.h"
#include "base/number.h"

static const int DateTimeId = qRegisterMetaType<DateTime>("DateTime");

boost::function<DateTime()> DateTime::_nowFunctor;

boost::function<DateTime()> DateTime::setNowFunctor(boost::function<DateTime()> nowFunctor){
    auto oldFunctor = _nowFunctor;
    _nowFunctor = nowFunctor;
    return oldFunctor;
}

DateTime::DateTime()
    :_localTicks(TIMEZONE_UNKNOWN), _utcTicks()
#ifndef NDEBUG
    ,_date(INVALID_DATE),_time(0)
#endif
{
    assert(isNull());
}

DateTime::DateTime(int time/*210101000*/, int date, TimeZoneCode timezoneCode)
    :_localTicks(timezoneCode), _utcTicks()
#ifndef NDEBUG
    ,_date(date), _time(time)
#endif
{
    int localTicksFromMidnight = DateTime::time2LocalTicksFromMidnight(time);
    if(isNan(localTicksFromMidnight)){
        MTS_ERROR("localTicksFromMidnight is NAN, ignore the date of %d, reset to NULL\n", date);
        clear();
    }else{
        assert(date>=19700101);
        assert(date<=30000101);
        _localTicks.set(localTicksFromMidnight);
        if(localTicksFromMidnight>=TICS_PER_DAY || localTicksFromMidnight<0){
            MTS_ERROR("tick %d out of range, reset to %d\n", localTicksFromMidnight,(localTicksFromMidnight%TICS_PER_DAY));
        }
        setDate(date);
    }
}

DateTime::DateTime(int localHour, int localMinute, int localSecond, int localMillisec, int localDate, TimeZoneCode timezoneCode)
    :_localTicks(timezoneCode), _utcTicks(){
        _localTicks.set(localHour*TICS_PER_HOUR+localMinute*TICS_PER_MINUTE+localSecond*TICS_PER_SECOND+localMillisec/*,nullptr*/);
        setDate(localDate);
#ifndef NDEBUG
        _date = date();
        _time = time();
#endif
    }

