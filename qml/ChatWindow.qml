import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import OnRabbleClient

Window {
    width: 600
    height: 400
    visible: true
    title: payload.serverName

    required property discoveryPayload payload
    required property string token

    Page {
        anchors.fill: parent

        header: Text {
            text: "# Channel Name"
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            font.bold: true
            padding: 8
        }

        Column {
            anchors.fill: parent
            spacing: 16
            padding: 16

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                text: "This is a Chat Window"
                font.pointSize: 16
            }

            Text {
                width: parent.width - 32
                horizontalAlignment: Text.AlignHCenter
                text: token
                font.pointSize: 10
                wrapMode: Text.Wrap
                elide: Text.ElideNone
            }
        }
    }

    ChatClientManager {
        id: chatClientManager

        onConnected: {
            console.log("Connected to the chat server. Lets go!");
        }
    }

    Component.onCompleted: {
        chatClientManager.setAccessToken(token)
        chatClientManager.setDiscoveryPayload(payload)
        chatClientManager.connectToServer()
    }
}
