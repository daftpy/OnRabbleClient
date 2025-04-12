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
            spacing: 0
            TabButton {
                id: channelsTabButton
                contentItem: Text {
                    text: "Channels"
                    font.pointSize: 8
                    font.bold: true
                    color: channelUserTabBar.currentIndex === channelsTabButton.TabBar.index ? ThemeManager.theme.color("text", "highlight") : ThemeManager.theme.color("text")
                }
                height: channelUserTabBar.height
                implicitHeight: height

                background: Rectangle {
                    anchors.fill: parent
                    color: channelUserTabBar.currentIndex === channelsTabButton.TabBar.index ? ThemeManager.theme.color("primary") : ThemeManager.theme.color("background", "lightest")
                    HoverHandler {
                        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }
            TabButton {
                id: usersTabButton
                contentItem: Text {
                        text: "Users"
                        font.pointSize: 8
                        font.bold: true
                        color: channelUserTabBar.currentIndex === usersTabButton.TabBar.index ? ThemeManager.theme.color("text", "highlight") : ThemeManager.theme.color("text")
                    }
                height: channelUserTabBar.height
                implicitHeight: height

                background: Rectangle {
                    anchors.fill: parent
                    color: channelUserTabBar.currentIndex === usersTabButton.TabBar.index ? ThemeManager.theme.color("primary") : ThemeManager.theme.color("background", "lightest")
                    HoverHandler {
                        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }
            onCurrentIndexChanged: {
                print("currentIndex changed to", currentIndex)
            }
        }

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 8.0
            spacing: 4.0
            clip: true
            model: ChatChannelPayloadModel { id: serverChannels }
            delegate: Text {
                text: name
                font.bold: true
                font.pointSize: 12.0
                color: ThemeManager.theme.color("text")
                HoverHandler {
                    acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                    cursorShape: Qt.PointingHandCursor
                }
            }
        }
    }

    Connections {
        target: chatClientManager.broker

        function onActiveChannelsReceived(channels) {
            console.log("Sidebar: Received channels from broker:", channels);
            serverChannels.addChannels(channels);
        }
    }
}
