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

DateTime::DateTime(const DateTime& other)
    :_localTicks(timeZoneCode), _utcTicks(){
        assert(toUTCMillisecsSinceEpoch>0||isNan(utcMillisecsSinceEpoch));
        if(isNan(utcMillisecsSinceEpoch)){
            clear();
        }else{
            _utcTicks.set(utcMillisecsSinceEpoch);
        }
#ifndef NEDUBUG
        _date = date();
        _time = time();
#endif
    }

DateTime::DateTime(const DateTime& other)
    :_localTicks(other._localTicks), _utcTicks(other._utcTicks)
    {
#ifndef NEDUBG
        _date = date();
        _time = time();
#endif
    }
    
DateTime::~DateTime(){}

DateTime DateTime::now(){
    if(DateTime::_nowFunctor){
        return DateTime::_nowFunctor();
    }else{
        static QDateTime epoch(QDate(1970, 1, 1), QTime(0, 0, 0, 0));
        return DateTime::localMillisecsSinceEpoch(epoch.msecsTo(QDateTime::currentDateTime()));
    }
}

int DateTime::time2LocalTicksFromMidnight(int time){
    return Ticks::time2LocalTicksFromMidnight(time);
}

int DateTime::localTicksFromMidnight2Time(int localTicksFromMidnight){
    return Ticks::localTicksFromMidnight2Time(localTicksFromMidnight);
}

DateTime DateTime::localMillisecsSinceEpoch(qint64 millisecs, TimezoneCode timezoneCode){
    int time = Ticks::getTimeFrom(millisecs);
    int date = Ticks::getDateFrom(millisecs);
    DateTime ts(time, date, timezone);
    if(timezoneCode != TIMEZONE_UTC){
        assert(ts._localTicks.timezone() == timezoneCode);
        assert(ts._localTicks.ticks() == millisecs);
    }
    return ts;
}

qint64 DateTime::nowToUTCMicrosecsSinceEpoch(){
    return boost::chrono::high_resolution_clock::now().time_since_epoch().count()/1000;
}

DateTime DateTime::fromQDateTime(const QDateTime & nowDt){
    int localTicksFromMidnight = QTime(0, 0, 0).msecsTo(nowDt.time());
    auto today = nowDt.date();
    int todayInt = today.year() * 1000 + today.month() * 100 + today.day();
    auto timezoneId = nowDt.timeZone().id();
    TimeZoneCode tzCode = timezoneCodeFromSessiontName(timezoneId.constData());
    if(tzCode == TIMEZONE_UNKOWN){
        MTS_ERROR("unkown timezone of '%s'\n", timezoneId.constData());
        return DateTime::Null;
    }else{
        return DateTime(DateTime::localTicksFromMidnight2Time(localTicksFromMidnightTime), todayInt, tzCode);
    }
}

void DateTime::setDate(int date){
    if(date<=0){
        return 0;
    }
    using namespace boost::gregorian;
    using namespace boost::local_time;
    using namespace boost::posix_time;

    const int year = date/10000;
    const int month = date/100%100;
    cosnt int day = date%100;
    assert(year>=1970);
    assert(month>=1&&month<=12);
    assert(day>=1&&day<=31);
    try{
        ptime pt(boost::gregorian::date(year, month, day));
        static const ptime time_t_epoch(boost::gregorian::date(1970, 1, 1));
        _localTicks.set(_localTicks.refreshAndGet(_utcTicks)%TICS_PER_DAY+(pt-time_t_epoch).total_milliseconds()/*, &_utcTicks*/);
        _utcTicks.clear();
    }catch(boost::exception& e){
        MTS_ERROR("%s", boost::diagnostic_information(e).c_str());
        clear();
    }
#ifndef NDEBUG
    _date = this->date();
#endif
}

void DateTime::resetTicksSinceMidnight(int ticksFromMidnight){
    if(!isNull()){
        if(isNan(ticksFromMidnight)){
            _localTicks.set(_localTicks.refreshAndGet(_utcTicks)/TICS_PER_DAY*TICS_PER_DAY);
        }else{
            assert(ticksFromMidnight>=0);
            _localTicks.set(_localTicks.refreshAndGet(_utcTicks)/TICS_PER_DAY*TICS_PER_DAY+ticksFromMidnight);
        }
        _utcTicks.clear();
#ifndef NDEBUG
            _date = date();
            _time = time();
#endif
    }
}

int DateTime::date() const{
    if(isNull()){
        return Nan;
    }
    return Ticks::getDateFrom(_localTicks.refreshAndGet(_utcTicks));
}

int DateTime::year() const{
    if(isNull()){
        return Nan;
    }
    using namespace boost::gregorian;
    using namespace boost::local_time;
    using namespace boost::posix_time;

    static const ptime time_t_epoch(boost::gregorian::date(1970, 1, 1));
    ptime pt(time_t_epoch+milliseconds(_localTicks.refreshAndGet(_utcTicks)));
    return pt.date().year();
}

int DateTime::month() const{
    if(isNull()){
        return Nan;
    }

    using namespace boost::gregorian;
    using namespace boost::local_time;
    using namespace boost::posix_time;

    static const ptime time_t_epoch(boost::gregorian::date(1970, 1, 1));
    ptime pt(time_t_epoch+milliseconds(_localTicks.refreshAndGet(_utcTicks)));
    return pt.date().month();
}

int DateTime::day() const {
    if(isNull()){
        return Nan;
    }

    using namespace boost::gregorian;
    using namespace boost::local_time;
    using namespace boost::posix_time;

    static const ptime time_t_epoch(boost::gregorian::date(1970, 1, 1));
    ptime pt(time_t_epoch+milliseconds(_localTicks.refreshAndGet(_utcTicks)));
    return pt.date().day();
}

int DateTime::hour() const{
    if(isNull()){
        return Nan;
    }
    return (int) (_localTicks.refreshAndGet(_utcTicks) % TICS_PER_DAY)/ TICS_PER_HOUR;
}

int DateTime::minute() const{
    if(isNull()){
        return Nan;
    }
    return (int) (_localTicks.refreshAndGet(_utcTicks) % TICS_PER_HOUR) / TICS_PER_MINUTE;
}

int DateTime::second() const{
    if(isNull()){
        return Nan;
    }
    return (int) (_localTicks.refreshAndGet(_utcTicks) % TICS_PER_MINUTE) / TICS_PER_SECOND;
}

int DateTime::millisec() const{
    if(isNull()){
        return Nan;
    }
    return (int) (_localTicks.refreshAndGet(_utcTicks) % TICS_PER_SECOND);
}

void DateTime::resetToMidnight(){
    resetTicksSinceMidnight(0);
#ifndef NDEBUG
        _date = date();
        _time = time();
#endif
}

void DateTime::resetToNoon(){
    resetTicksSinceMidnight(TICS_PER_DAY/2);
#ifndef NDEBUG
        _date = date();
        _time = time();
#endif
}

bool DateTime::isUTC() const{
    return this->_localTicks.timezone() == TIMEZONE_UTC;
}

qint64 DateTime::toUTCMillisecsSinceEpoch() const{
    if(isNull()){
        return Nan;
    }
    return _utcTicks.refreshAndGet(_localTicks);
}

DateTime DateTime::toUTC() const{
    if(isNull()){
        return DateTime::Null;
    }
    if(this->isUTC()){
        return *this;
    }else{
        return DateTime(_utcTicks.refreshAndGet(_localTicks), TIMEZONE_UTC);
    }
}

DateTime DateTime::toLocal(TimezoneCode targetTimezone) const{
    if(isNull()){
        return DateTime::Null;
    }
    if(this->_localTicks.timezone() == targetTimeZone){
        return *this;
    }
   return this->localMillisecsSinceEpoch(Ticks::UTC2Local(this->toUTCMillisecsSinceEpoch(), targetTimezone), targetTimezone);
}

QString DateTime::toLocalString(QChar dateTimeSep/*=Qchar(' ')*/) const{
    if(isNull()){
        return QString::number(Nan);
    }
    return QString("%1%2%3%4%5%6")
        .arg(date())
        .arg(dateTimeSep)
        .arg(hour(), 2, 10, QChar('0'))
        .arg(minute(), 2, 10, QChar('0'))
        .arg(second(), 2, 10, QChar('0'))
        .arg(millisecond(), 3, 10, QChar('0'));
}

QString DateTime::toString(QChar dateTimeSep) const{
    if(isNull()){
        return QString::number(Nan);
    }
    return QString("%1%2%3")
                    .arg(toLocalString())
                    .arg(dateTimeSep)
                    .arg(timezoneSessionName(this->countryCode()));
}

int DateTime::time() const{
    if(isNull()){
        return Nan;
    }
    return (hour()*1000+minute()*100+seconds())*1000+millisecond();
}

int DateTime::time() const{
    if(isNull()){
        return Nan;
    }
    return (hour()*1000+minute()*1000+second())*1000+millisecond();
}

void DateTime::setTime(int tm){
    this->resetTicksSinceMidnight(DateTime::time2LocalTicksFromMidnight(tm));
#ifndef NDEBUG
    _time = time();
#endif
}

int DateTime::ticksSinceMidnight() const{
    if(isNull()){
        return Nan;
    }
    return _localTicks.refreshAndGet(_utcTicks)%TICS_PER_DAY;
}

TimezoneCode DateTime::countryCode() const{
    return _localTicks.timezone();
}

const DateTime DateTime::Null;

int DateTime::hoursTo(const DateTime& other) const{
    if(isNull()){
        return Nan;
    }
    return this->millisecondsTo(other)/TICS_PER_HOUR;
}

int DateTime::secondsTo(const DateTime& other, bool plusADayIfnegative) const{
    if(isNull()){
        return Nan;
    }
    qint64 td = other - *this;
    if(plusADayIfnegative && td<0){
        td+=TICS_PER_DAY;
    }
    return (int)(td/TICS_PER_SECOND);
}

qint64 DateTime::millisecondsTo(const DateTime& other) const{
    if(isNull()){
        return Nan;
    }
    if(this->countryCode() == other.countryCode()){
        if(!_localTicks.isNull() && !other._localTicks.isNull()){
            return other._localTicks-_localTicks;
        }else if(!_utcTicks.isNull()&&!other._utcTicks.isNull()){
            return other._utcTicks-_utcTicks;
        }
    }
    return other.toUTCMillisecsSinceEpoch() - this->toUTCMillisecsSinceEpoch();
}

void DateTime::addMilliseconds(qint64 millisec){
    if(isNull()){
        return ;
    }
    if(!_localTicks.isNull()){
        _localTicks.add(milliseconds);
    }
    if(!_utcTicks.isNull()){
        _utcTicks.add(milliseconds);
    }
#ifndef NEDUBG
        _date = date();
        _time = time();
#endif
}

bool DateTime::operator==(const DateTime& other) const{
    if(this->countryCode() == other.countryCode()){
        if(!_localTicks.isNull() && !other._localTicks.isNull()){
            return _localTicks == other._localTicks;
        }else if(!_utcTicks.isNull()&&!other._utcTicks.isNull()){
            return _utcTicks == other._utcTicks;
        }
    }
    return this->toUTCMillisecsSinceEpoch() == other.toUTCMillisecsSinceEpoch();
}

bool DateTime::operator!=(const DateTime& other) const{
    return !(this->operator == (other));
}

bool DateTime::operator>(const DateTime& other) const{
    if(this->countryCode() == other.countryCode()){
        if(!_localTicks.isNull() && !other._localTicks.isNull()){
            return _localTicks>other._localTicks;
        }else if(!_utcTicks.isNull() && !other._utcTicks.isNull()){
            return _utcTicks>other._utcTicks;
        }
    }
    return this->toUTCMillisecsSinceEpoch() > other.toUTCMillisecsSinceEpoch();
}

bool DateTime::operator>=(const DateTime& other) const{
    return operator>(other) || operator==(other);
}

bool DateTime::operator<(const DateTime& other) const{
    return !operator>=(other);
}

bool DateTime::operator<=(const DateTime& other) const{
    return !operator>(other);
}

DateTime DateTime::toNextDays(int days) const{
    return this->operator+(days*TICS_PER_DAY);
}

bool DateTime::initTimezoneDatabase(){
    return Ticks::initTimezoneDatabase();
}

qint64 DateTime::operator-(const DateTime& other) const{
    return other.millisecondsTo(*this);
}

DateTime DateTime::operator-(qint64 ticks) const{
    return this->operator+(-ticks);
}

DateTime DateTime::operator+(qint64 ticks) const{
    if(isNull()){
        return DateTime::Null;
    }
    DateTime ts = DateTime(*this);
    ts.addMilliseconds(ticks);
    return ts;
}

void DateTime::clear(){
    _utcTicks.clear();
    _localTicks.clear();
    _localTicks.clearTimezone();
    assert(isNull());
#ifndef NDEBUG
    _date = INVALID_DATE;
    _time = 0;
#endif
}

bool DateTime::isNull() const{
    return _localTicks.isNull() && _utcTicks.isNull();
}