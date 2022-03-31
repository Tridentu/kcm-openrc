

#pragma once

#include <KAuth/KAuthActionReply>
#include <KAuth/KAuthHelperSupport>

class OpenRCHelper: public QObject {
    Q_OBJECT
public Q_SLOTS:
    KAuth::ActionReply removeservice(const QVariantMap& args);
    KAuth::ActionReply stopservice(const QVariantMap& args);
    KAuth::ActionReply restartservice(const QVariantMap& args);

};
