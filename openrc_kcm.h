
#pragma once


#include <KQuickAddons/ManagedConfigModule>
#include <rc.h>
#include <QSettings>
#include "openrckcmsettings.h"
#include <KAboutData>

class OpenRCKCM : public KQuickAddons::ManagedConfigModule {
        Q_OBJECT
public:
    OpenRCKCM(QObject* parent, const KPluginMetaData& data, const QVariantList& args);
public:
    Q_PROPERTY(QStringList allServiceTitles READ getAllServiceTitles)
    Q_PROPERTY(QStringList allServices READ getAllServices)

    Q_INVOKABLE void tryDisableService(QString serviceName);
    Q_INVOKABLE void tryStopService(QString serviceName);
    QStringList getAllServiceTitles();
    QStringList getAllServices();
    Q_INVOKABLE void tryRestartService(QString serviceName);

private:
    QSettings settings;
};

