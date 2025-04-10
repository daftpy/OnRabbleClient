import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import OnRabbleClient

ApplicationWindow {
    id: root
    width: 600
    height: 400
    minimumWidth: 600
    minimumHeight: 400
    visible: true
    title: payload.serverName
    required property discoveryPayload payload
    required property ChatClientManager chatClientManager

    Page {
        anchors.fill: parent
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
    }

    // Use the injected chatClientManager
    Connections {
        target: chatClientManager

        function onConnected() {
            console.log("ChatWindow: Connected to chat server!");
        }

        function onConnectionError(error) {
            console.error("ChatWindow: Connection error:", error);
        }
    }

    Component.onCompleted: {
        console.log("What window opened for: ", payload.serverName);
    }
}
