#include "kernel/qeventdispatcher_amiga_p.h"
#include "qamigaeventdispatcherfactory_p.h"
QAbstractEventDispatcher *QAmigaEventDispatcherFactory::m_eventDispatcher = 0;
QAbstractEventDispatcher *QAmigaEventDispatcherFactory::createAmigaEventDispatcher() {
    if(!m_eventDispatcher) m_eventDispatcher = new QEventDispatcherAMIGA;
    return m_eventDispatcher;
}
void QAmigaEventDispatcherFactory::deleteEventDispatcher() {
    QEventDispatcherAMIGA *m_amigaDispatcher = static_cast<QEventDispatcherAMIGA *>(m_eventDispatcher);
    if(m_amigaDispatcher) delete m_amigaDispatcher;
    m_eventDispatcher = 0;
}