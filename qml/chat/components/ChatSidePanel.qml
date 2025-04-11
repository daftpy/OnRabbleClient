import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import OnRabbleClient

Rectangle {
    id: root
    required property ChatClientManager chatClientManager
    Layout.fillWidth: true
    Layout.minimumWidth: 175.0
    Layout.maximumWidth: 250.0
    Layout.fillHeight: true
    color: ThemeManager.theme.color("background")
    ColumnLayout {
        anchors.fill: parent
        spacing: 0
        TabBar {
            id: channelUserTabBar
            Layout.fillWidth: true
            Layout.preferredHeight: 28.0
            TabButton {
                text: "Channels"
                font.pointSize: 10.0
                height: channelUserTabBar.height
                implicitHeight: height
            }
            TabButton {
                text: "Users"
                font.pointSize: 10.0
                height: channelUserTabBar.height
                implicitHeight: height
            }
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 8.0
            spacing: 4.0
            model: ChatChannelPayloadModel { id: serverChannels }
            delegate: Text {
                text: name
                font.bold: true
                font.pointSize: 12.0
                color: ThemeManager.theme.color("text")
            }
        }
    }

    Connections {
        target: chatClientManager
        function onActiveChannelsReceived(channels) {
            console.log("LOOK HERE LOOK HERE LOOK HERE", channels);
            serverChannels.addChannels(channels);
        }
    }
}
