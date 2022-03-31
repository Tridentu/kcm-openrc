

#include "openrc_actions.h"
#include <KAuth/KAuthAction>
#include <KAuth/KAuthExecuteJob>
#include <rc.h>
#include <qprocess.h>



KAuth::ActionReply OpenRCHelper::removeservice( const QVariantMap& args )
{
    KAuth::ActionReply reply;
    QString serviceName(args[QStringLiteral("serviceName")].toString());
    if(!rc_service_delete("default", serviceName.toStdString().c_str())) {
        reply = KAuth::ActionReply::HelperErrorReply();
        reply.setErrorDescription(QStringLiteral("OpenRC failed to remove service ") + serviceName + QStringLiteral("."));
        return reply;
    }
    return reply;
}

KAuth::ActionReply OpenRCHelper::stopservice(const QVariantMap& args)
{
    KAuth::ActionReply reply;
    QString serviceName(args[QStringLiteral("serviceName")].toString());
    QProcess process(this);
    process.setProgram(QStringLiteral("/etc/init.d/") + serviceName);
    QStringList cmds;
    cmds << QStringLiteral("stop");
    process.setArguments(cmds);
    process.start();
    if(!process.waitForFinished(20000)) {
        reply = KAuth::ActionReply::HelperErrorReply();
        reply.setErrorDescription(QStringLiteral("OpenRC failed to stop service ") + serviceName + QStringLiteral("."));
        return reply;
    }
     if(process.exitStatus() == QProcess::CrashExit) {
        reply = KAuth::ActionReply::HelperErrorReply();
        reply.setErrorDescription(QStringLiteral("OpenRC failed to stop service ") + serviceName + QStringLiteral("."));
        return reply;
    }
    return reply;
}

KAuth::ActionReply OpenRCHelper::restartservice(const QVariantMap& args)
{
    KAuth::ActionReply reply;
    QString serviceName(args[QStringLiteral("serviceName")].toString());
    QProcess process(this);
    process.setProgram(QStringLiteral("/etc/init.d/") + serviceName);
    QStringList cmds;
    cmds << QStringLiteral("restart");
    process.setArguments(cmds);
    process.start();
    if(!process.waitForFinished(20000)) {
        reply = KAuth::ActionReply::HelperErrorReply();
        reply.setErrorDescription(QStringLiteral("OpenRC failed to restart service ") + serviceName + QStringLiteral("."));
        return reply;
    }
    if(process.exitStatus() == QProcess::CrashExit) {
        reply = KAuth::ActionReply::HelperErrorReply();
        reply.setErrorDescription(QStringLiteral("OpenRC failed to restart service ") + serviceName + QStringLiteral("."));
        return reply;
    }
    return reply;
}


KAUTH_HELPER_MAIN("tridentu.auth.openrc.service", OpenRCHelper);
