 
import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.11

import org.kde.kirigami 2.16 as Kirigami
import org.kde.kcm 1.4 
import org.kde.plasma.extras 2.0 as PlasmaExtras
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 3.0 as PlasmaComponents3

ScrollViewKCM {
    id: rootKCM
    implicitWidth: units.gridUnit * 60
    implicitHeight: units.gridUnit * 25
    ColumnLayout{
        id: root
        anchors.fill: parent
        anchors.leftMargin: units.gridUnit * 2
        anchors.rightMargin: units.gridUnit * 2
        anchors.topMargin: units.gridUnit * 2
        anchors.bottomMargin: units.gridUnit * 2

        PlasmaExtras.Heading {
            level: 1
            Layout.fillWidth: true
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter;
            text: i18n("Configure OpenRC")
            
        }
        
      ColumnLayout {
        id: openRCPanel
        Layout.fillHeight: true
        Layout.fillWidth: true
        PlasmaExtras.Heading {
            level: 2
            Layout.fillWidth: true
            text: i18n("Available Services")
        }
        
        ListView {
            id: serviceView
            model: serviceModel
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: units.gridUnit * 1.5
            
            delegate: Rectangle {
                implicitWidth: rootKCM.implicitWidth
                color: "#3b4252"
                border.color: "#a3be8c"
                    implicitHeight: units.gridUnit * 2
                    
                        
                    RowLayout {   
                        id: toolbar
                        Layout.minimumWidth: parent.implicitWidth
                        anchors.fill: parent
                        PlasmaComponents3.Label {
                                    id: headerItem
                                    Layout.fillWidth: true
                                    text: title
                                    Layout.leftMargin: 1 * units.gridUnit
                        }
                        Controls.ToolButton {
                            
                        Layout.alignment: Qt.AlignRight
                        id: deleteButton
                        icon.name: "delete"
                        text: i18n("Remove")
                        Controls.ToolTip.text: i18n("Removes this service from the default runlevel (for OpenRC).")
                        onClicked: {
                            console.log("Start remove " + name);
                            kcm.tryDisableService(name);
                        }
                        }
                        Controls.ToolButton {
                        id: stopButton
                        Layout.alignment: Qt.AlignRight
                        icon.name: "delete"
                        text: i18n("Stop")
                        Controls.ToolTip.text: i18n("Stops the current service.")
                        onClicked: {
                            kcm.tryStopService(name);
                        }
                        }
                        Controls.ToolButton {
                        id: restartButton
                        Layout.alignment: Qt.AlignRight
                        icon.name: "system-restart"
                        text: i18n("Restart")
                        Controls.ToolTip.text: i18n("Restarts the current service.")
                        onClicked: {
                            kcm.tryRestartService(name);
                        }
                        }
                }
            }
            
        }
        
         ListModel {
            id: serviceModel
            Component.onCompleted: {
                for (var i = 0; i < kcm.allServices.length; i++){
                    serviceModel.append({"name": kcm.allServices[i], "title": kcm.allServiceTitles[i]});
                }
                
            }
        }
    }
        
    }
}


