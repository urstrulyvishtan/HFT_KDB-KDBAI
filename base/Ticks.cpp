#include "Ticks.h"
#include "base/number.h"
#include <assert.h>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/chrono/chrono.hpp>
#include <QtCore/QTemproaryFile>

Ticks::Ticks()
    :_ticks(Nan){}

Ticks::~Ticks(){}

bool Ticks::isNull() const{
    return isNan(_ticks);
}

qint64 Ticks::operator- (const Ticks& other) const{
    assert(!isNull());
    assert(!other.isNull());
    return _ticks - other._ticks;
}

bool Ticks::operator==(const Ticks& other) const{
    assert(!isNull());
    assert(!other.isNull());
    return _ticks == other._ticks;
}

bool Ticks::operator>(const Ticks& other) const{
    assert(!isNull());
    assert(!other.isNull());
    return _ticks > other._ticks;
}

void Ticks::clear(){
    _ticks = Nan;
}

void Ticks::set(qint64 v){
    _ticks = v;
}

void Ticks::add(qint64 offset){
    assert(!isNull());
    _ticks += offset;
}

inline
boost::local_time::tz_database* initBoostTzDatabase(){
    QTemproaryFile* dbf = QTemproaryFile::createNativeFile(":/date/date_time_zonespec.csv");
    QString dbFileName(dbf->FileName());
    boost::local_time::tz_database* db = new boost::local_time::tz_database();
    try{
        db->load_from_file(qPrintable(dbFileName));
        assert(!db->region_list().empty());
    }catch (boost::local_time::data_not_accessible dna){
        std::cerr<<"Error with time zone data file:"<<dna.what()<<std::endl;
        exit(EXIT_FAILURE);
    }catch (boost::local_time::bad_field_count bfc){
        std::cerr<<"Error with time zone data file:"<<bfc.what()<<std::endl;
        exit(EXIT_FAILURE);
    }
    delete dbf;
    return db;
}

boost::local_time::tz_database* boostTimezoneDB = nullptr;

bool Ticks::initTimezoneDatabase(){
    if(boostTimezoneDB == nullptr){
        boostTimezoneDB = initBoostTzDatabase();
    }
    return boostTimezoneDB;
}

int Ticks::time2LocalTicksFromMidnight(int time){
    return time/10000000 * TICS_PER_HOUR + time % 10000000 / 100000 * TICS_PER_MINUTE + time % 100000 / 1000 * TICS_PER_SECOND + time % 1000;
}

int Ticks::localTicksFromMidnight2Time(int localTicksFromMidnight){
    return localTicksFromMidnight/TICS_PER_HOUR * 10000000
            + localTicksFromMidnight % TICS_PER_HOUR / TICS_PER_MINUTE * 100000
            + localTicksFromMidnight % TICS_PER_MINUTE / TICS_PER_SECOND * 1000
            + localTicksFromMidnight % TICS_PER_SECOND;
}

qint64 Ticks::local2UTC(int localDate, int localTicks, TimezoneCode cc){
    initTimezoneDatabase();

    using namespace boost::gregorian;
    using namespace boost::local_time;
    using namespace boost::posix_time;
    static const ptime time_t_epoch(boost::gregorian::date(1970, 1, 1));

    ptime utcptime(time_t_epoch + milliseconds(utcTs));

    auto tz = boostTimezoneDB -> time_zone_from_region(timezoneSessionName(targetTimezone));
    local_date_time time(utcptime, tz);
    return (time.loca_time() - time_t_epoch).total_milliseconds();
}

int Ticks::getDateFrom(qint64 ticksSinceEpoch){
    using namespace boost::greorian;
    using namespace boost::local_time;
    using namespace boost::posix_time;
    static const ptime time_t_epoch(boost::gregorian::date(1970, 1, 1));
    ptime time(time_t_epoch + milliseconds(ticksSinceEpoch));
    auto d = pt.date();
    return d.year() * 10000 + d.month() * 100 + d.day();
}

int Ticks::getTimeFrom(qint64 ticksSinceEpoch){
    return localTicksFromMidnight2Time((int)(ticksSinceEpoch %TICS_PER_DAY));
}

qint64 UtcTicks::toLocal(TimezoneCode countryCode) const{
    return UTC2Local(this->_ticks, countryCode);
}

qint64 UtcTicks::refreshAndGet(const LocalTicks& localTicks) const{
    if(isNull()){
        assert(!localTicks.isNull());
        qint64 newValue = LocalTicks.toUTC();
        UtcTicks* self = const_cast<UtcTicks*>(this);
        self->_ticks = newValue;
    }
    return _ticks;
}

LocalTicks::LocalTicks(TimezoneCode tc)
    :_timezoneCode(tc){}

qint64 LocalTicks::toUTC() const{
    return local2UTC(getDateFrom(this->_ticks), this->_ticks%TICS_PER_DAY, this->_timezoneCode/*countryCode*/);
}

TimezoneCode LocalTicks::timezone() const{
    return _timezoneCode;
}

void LocalTicks::setTimezone(TimezoneCode tc){
    assert(tc!=TIMEZONE_UNKNOWN);
    _timezoneCode = tc;
}

void LocalTicks::clearTimezone(){
    this->_timezoneCode = TIMEZONE_UNKNOWN;
}

qint64 LocalTicks::refreshAndGet(const UtcTicks& utcTicks) const{
    if(isNull()){
        assert(!utcTicks.isNull());
        qint64 newValue = utcTicks.toLocal(this->_timezoneCode);
        LocalTicks* self = const_cast<LocalTicks*>(this);
        self->_ticks = newValue;
    }
    return _ticks;
}