#pragma once
#include <QuartzCore/QObject>
#include "Component.h"
#include "base/DateTime.h"
#include "TimerCallback.h"
#include "DateCallback.h"

namespace mts{
    class MTS_CORE_API Clock:public Component{
        public:
            Clock(void);
            virtual ~Clock(void);
            virtual DateTime now() const = 0;
            virtual int currentTradingDay() const = 0;

            int createTimer(int beginTime, int interval, TimerCallback*);
            bool destroyTimer(int id);

            void addDateCallback(DateCallback*);
        protected:
            virtual QObject* doCreateTimer(int id, qint64 beginTicks, int interval, TimerCallback*) = 0;
            virtual bool doDestroyTimer(QObject*) = 0;
            void clear();
            void notifyBusinessDateChanged(int newBusinessDate);
        private:
            QList<QObject*> _ids;
            QList<DateCallback*> _dateCallbacks;
#ifdef MTS_UNIT_TEST
        public:
#endif
            qint64 calcBeginUTCTicks(int beginTime, int interval) const;
    };
}