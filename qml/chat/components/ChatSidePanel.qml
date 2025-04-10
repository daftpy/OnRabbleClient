import QtQuick
import QtQuick.Layouts
import OnRabbleClient

Rectangle {
    anchors.fill: parent
    color: ThemeManager.theme.color("background", "dark")
    RowLayout {
        anchors.fill: parent
        Rectangle {
            Layout.fillWidth: true
            Layout.minimumWidth: 175.0
            Layout.maximumWidth: 250.0
            Layout.fillHeight: true
            color: ThemeManager.theme.color("background")
            Column {
                Text {
                    text: "Sidebar"
                }
            }
        }

        Column {
            Layout.fillWidth: true
            Layout.preferredWidth: 600.0
            spacing: 16
            padding: 16

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "This is a Chat Window for " + payload.serverName
                color: ThemeManager.theme.color("text")
                font.pointSize: 16
            }

            Text {
                width: parent.width - 32
                horizontalAlignment: Text.AlignHCenter
                text: "token hidden"
                font.pointSize: 10
                wrapMode: Text.Wrap
                elide: Text.ElideNone
            }
        }
    }
}
