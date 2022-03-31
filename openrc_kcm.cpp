
#include "openrc_kcm.h"
#include <KPluginFactory>
#include <KLocalizedString>
#include "openrckcmsettings.h"
#include <sys/queue.h>
#include <QString>
#include <KAuth/KAuthAction>
#include <KAuth/KAuthExecuteJob>

K_PLUGIN_CLASS_WITH_JSON(OpenRCKCM, "package/kcm_openrc.json");

OpenRCKCM::OpenRCKCM(QObject* parent, const KPluginMetaData& data, const QVariantList& args)
    : KQuickAddons::ManagedConfigModule(parent, data, args)
{
    setButtons(Help | Apply | Default);
    KAboutData * aboutData = new KAboutData(QStringLiteral("kcm_openrc"), i18n("OpenRC Settings"));
    aboutData->addAuthor(QStringLiteral("Tridentu Group"));
    aboutData->addLicense(KAboutLicense::LGPL_V2);
    aboutData->setHomepage(QStringLiteral("https://tridentu.github.io/openrc-settings"));
    
    setAboutData(aboutData);

}

QStringList OpenRCKCM::getAllServiceTitles(){
    QStringList list;
    {
      RC_STRINGLIST* listS = rc_services_in_runlevel("default");
      RC_STRING* svc;
      TAILQ_FOREACH(svc, listS, entries) {
        std::string serviceStrStd(svc->value);
        std::string serviceDescription(rc_service_description(svc->value,""));
        QString serviceStr =  QString::fromStdString(serviceStrStd) +  QString::fromStdString(" (") + QString::fromStdString(serviceDescription) + QString::fromStdString(")");   
        list << serviceStr;
      }
      rc_stringlist_free(listS);
    }
    return list;
}

QStringList OpenRCKCM::getAllServices(){
    QStringList list;
    {
      RC_STRINGLIST* listS = rc_services_in_runlevel("default");
      RC_STRING* svc;
      TAILQ_FOREACH(svc, listS, entries) {
        std::string serviceStrStd(svc->value);
        QString serviceStr =  QString::fromStdString(serviceStrStd);
        list << serviceStr;
      }
      rc_stringlist_free(listS);
    }
    return list;
}


void OpenRCKCM::tryDisableService ( QString serviceName )
{
    QVariantMap map;
    map[QStringLiteral("serviceName")] = serviceName;
    KAuth::Action removal_service(QStringLiteral("tridentu.auth.openrc.service.removeservice"));
    removal_service.setHelperId(QStringLiteral("tridentu.auth.openrc.service"));
    removal_service.setArguments(map);
    KAuth::ExecuteJob* job = removal_service.execute();
    qDebug() << "Running rc-update...";
    if(!job->exec()){
        qDebug() << QStringLiteral("OpenRC Suite failed: ") << job->errorString();
    }
}


void OpenRCKCM::tryStopService( QString serviceName )
{
    QVariantMap map;
    map[QStringLiteral("serviceName")] = serviceName;
    KAuth::Action stop_service(QStringLiteral("tridentu.auth.openrc.service.stopservice"));
    stop_service.setHelperId(QStringLiteral("tridentu.auth.openrc.service"));
    stop_service.setArguments(map);
    KAuth::ExecuteJob* job = stop_service.execute();
    qDebug() << "Running rc-update...";
    if(!job->exec()){
        qDebug() << QStringLiteral("OpenRC Suite failed: ") << job->errorString();
    }
}

void OpenRCKCM::tryRestartService( QString serviceName )
{
    QVariantMap map;
    map[QStringLiteral("serviceName")] = serviceName;
    KAuth::Action rs_service(QStringLiteral("tridentu.auth.openrc.service.restartservice"));
    rs_service.setHelperId(QStringLiteral("tridentu.auth.openrc.service"));
    rs_service.setArguments(map);
    KAuth::ExecuteJob* job = rs_service.execute();
    qDebug() << "Running rc-update...";
    if(!job->exec()){
        qDebug() << QStringLiteral("OpenRC Suite failed: ") << job->errorString();
    }
}


#include "openrc_kcm.moc"
