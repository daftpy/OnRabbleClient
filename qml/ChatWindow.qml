import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import OnRabbleClient

ApplicationWindow {
    width: 600
    height: 400
    visible: true
    title: payload.serverName

    required property discoveryPayload payload
    required property ChatClientManager chatClientManager

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
                text: "token hidden"
                font.pointSize: 10
                wrapMode: Text.Wrap
                elide: Text.ElideNone
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


    onClosing: function(close) {
        console.log("ChatWindow is closing");
        if (chatClientManager) {
            chatClientManager.destroy();
        }
    }

}
