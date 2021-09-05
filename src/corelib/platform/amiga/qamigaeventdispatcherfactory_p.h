#ifndef QAMIGAEVENTDISPATCHERFACTORY_H
#define QAMIGAEVENTDISPATCHERFACTORY_H

class QAbstractEventDispatcher;
class QAmigaEventDispatcherFactory {
public:
    static QAbstractEventDispatcher *createAmigaEventDispatcher();
    static QAbstractEventDispatcher *m_eventDispatcher;
    static void deleteEventDispatcher();
};

#endif