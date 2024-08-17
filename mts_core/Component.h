#pragma once
#include <QtCore/QObject>
#include "mts_core_api.h"

class MTS_CORE_API Component:public QObject{
    Q_OBJECT
public:
    Component();
    virtual ~Component();

    virtual bool initialize(const QVariantMap& params)=0;
    bool isInitialized() const;

public Q_SLOTS:
    void emitInitalizeDone();
    void emitInitializeError(const QString& err);

Q_SIGNALS:
    void initalizeDone();
    void initalizeError(const QString& err);

private:
    bool m_initialized;
}