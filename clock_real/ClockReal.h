#pragma once
#include "base/DateTime.h"
#include "mts_core/Clock.h"
#include <QtCore/QTimer>

namespace mts{
    class ClockTimeReal:pubic QTimer{
        Q_OBJECT
    public:
        ClockTimerReal(int id, TimerCallback*, QObject * parent = 0);
        virtual ~ClockTimeReal();
    
    private Q_SLOTS:
        void onTimeout();
    
    private:
        const int _id;
        TimerCallback* _callback;
    };

    class ClockReal:public Clock{
        Q_OBJECT
    public:
        ClockReal();
        virtual ~ClockReal(void);

        virtual DateTime now() const override;
        virtual int currentTradingDay() const override;
    protected:
        virtual QObject* doCreateTimer(int id, qint64 beginTicks, int interval, TimerCallback*) override;
        virtual bool doDestroyTimer(QObject*) override;

        virtual bool initialize(const QVariantMap & params) override;
    
    private Q_SLOTS:
        void onTimeout();
    private:
        qint64 getNextBeginTimeInterval() const;
    }
}