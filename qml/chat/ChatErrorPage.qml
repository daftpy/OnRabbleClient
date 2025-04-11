import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import OnRabbleClient

Page {
    id: root
    required property ChatClientManager chatClientManager
    property string errorText
    Rectangle {
        anchors.fill: parent
        color: ThemeManager.theme.color("background", "dark")
        ColumnLayout {
            anchors.fill: parent
            id: layout

            Text {
                text: errorText
            }
            Button {
                text: "Reconnect"
                onClicked: {
                    // Call connected() to pop this window
                    // TODO: refactor to chatClientManager.attemptReconnect()
                    // This current solution is just temporary to remove the error page
                    chatClientManager.connected();
                }
            }
        }
    }
}
