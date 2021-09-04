#ifndef QAMIGAEVENTDISPATCHERFACTORY_H
#define QAMIGAEVENTDISPATCHERFACTORY_H

#include <QtGui/QStringList>

class QPlatformIntegration;
class QAmigaIntegrationFactory {
    static QPlatformIntegration *createAmigaPlatformIntegration(const QStringList &parameters);
};

#endif