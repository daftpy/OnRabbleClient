import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import OnRabbleClient

Page {
    id: root
    required property ChatClientManager chatClientManager
    required property discoveryPayload payload
    objectName: "ChatPage"
    RowLayout {
        anchors.fill: parent
        spacing: 0
        ChatSidePanel {
            chatClientManager: root.chatClientManager
        }

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredWidth: 600.0
            Layout.fillHeight: true
            color: ThemeManager.theme.color("background", "light")
            Column {
                anchors.fill: parent
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

    footer: Rectangle {
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
                    width: parent.width
                    color: ThemeManager.theme.color("text", "highlight")
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                    text: root.chatClientManager.user.username // get the username from the chatClientManager
                }
            }
            Item {
                Layout.fillWidth: true
                Layout.preferredWidth: 600.0
                Text {
                    anchors.centerIn: parent
                    text: "Channel location"
                    color: ThemeManager.theme.color("text", "highlight")
                }
            }
        }
    }

    Connections {
        target: chatClientManager

        function onActiveChannelsReceived(channels) {
            console.log("ChatPage: Received active channels:");
            for (let i = 0; i < channels.length; i++) {
                console.log(`  • ${channels[i].name}: ${channels[i].description}`);
            }
        }
    }
}
