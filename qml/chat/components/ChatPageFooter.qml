import QtQuick
import QtQuick.Layouts
import OnRabbleClient

Rectangle {
        required property string username
        required property string channelName
        property alias activeChannelText: activeChannelText

        width: parent.width
        height: 24.0
        color: ThemeManager.theme.color("background", "dark")

        RowLayout {
            anchors.fill: parent

            RowLayout {
                Layout.fillWidth: true
                Layout.minimumWidth: 175.0
                Layout.maximumWidth: 250.0
                Layout.leftMargin: 8.0
                PersonIcon {

                }

                Text {
                    Layout.fillWidth: true
                    color: ThemeManager.theme.color("text", "highlight")
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                    text: root.username // get the username from the chatClientManager
                }
            }
            Item {
                Layout.fillWidth: true
                Layout.preferredWidth: 600.0
                Text {
                    id: activeChannelText
                    anchors.centerIn: parent
                    text: channelName.toString()
                    color: ThemeManager.theme.color("text", "highlight")
                }
            }
        }
    }
