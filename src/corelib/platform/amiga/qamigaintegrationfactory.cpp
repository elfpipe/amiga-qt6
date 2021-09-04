#include <qpa/qplatformintegration.h>
#include "../../../gui/platform/amiga/qamigaintegration.h"
QPlatformIntegration *QAmigaIntegrationFactory::createAmigaPlatformIntegration(const QStringList &parameters) {
    return new QAmigaIntegration(parameters);
}