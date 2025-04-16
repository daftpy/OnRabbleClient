import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Effects
import OnRabbleClient

Rectangle {
    id: root
    required property ChatClientManager chatClientManager
    // property alias channelModel: serverChannels

    signal channelSelected(channelPayload channelPayload)

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
            spacing: 0
            TabButton {
                id: channelsTabButton
                contentItem: Item {
                    implicitHeight: channelsTabButtonRow.implicitHeight + 4.0
                    Row {
                        id: channelsTabButtonRow
                        anchors.centerIn: parent
                        spacing: 4.0
                        ChatIcon {
                            color: ThemeManager.theme.color("text")
                        }
                        Text {
                            id: channelSelectLabel
                            text: "Channels"
                            Layout.alignment: Qt.AlignCenter
                            font.pointSize: 9.0
                            color: ThemeManager.theme.color("text")
                        }
                    }
                }

                background: Rectangle {
                    anchors.fill: parent
                    color: channelUserTabBar.currentIndex === channelsTabButton.TabBar.index ? ThemeManager.theme.color("primary") :
                        channelsTabHoverHandler.hovered ? ThemeManager.theme.color("primary", "darkest") : ThemeManager.theme.color("background", "lightest")
                    HoverHandler {
                        id: channelsTabHoverHandler
                        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }
            TabButton {
                id: usersTabButton
                contentItem: Item {
                    implicitHeight: userTabButtonRow.implicitHeight + 4.0
                    Row {
                        id: userTabButtonRow
                        anchors.centerIn: parent
                        spacing: 4.0
                        PersonIcon {
                            // color: ThemeManager.theme.color("text")
                        }
                        Text {
                            id: usersSelectLabel
                            text: "Users"
                            Layout.alignment: Qt.AlignCenter
                            font.pointSize: 9.0
                            color: ThemeManager.theme.color("text")
                        }
                    }
                }

                background: Rectangle {
                    anchors.fill: parent
                    color: channelUserTabBar.currentIndex === usersTabButton.TabBar.index ? ThemeManager.theme.color("primary") :
                        usersTabHoverHandler.hovered ? ThemeManager.theme.color("primary", "darkest") : ThemeManager.theme.color("background", "lightest")
                    HoverHandler {
                        id: usersTabHoverHandler
                        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }
            onCurrentIndexChanged: {
                contentStack.currentIndex = currentIndex;
                console.log("Switched to tab index:", currentIndex);
            }
        }

        Component {
            id: highlight

            Item {
                width: channelListView.width; height: channelListView.currentItem.height
                y: channelListView.currentItem.y

                RectangularShadow {
                    anchors.fill: parent
                    Rectangle {
                        color: ThemeManager.theme.color("primary", "light")
                        radius: 5
                        anchors.fill: parent
                    }
                    radius: 5
                    blur: 10
                    spread: 0
                    color: Qt.rgba(0.243, 0.388, 0.866, 0.5)
                }
                Behavior on y {
                    SpringAnimation {
                        spring: 3
                        damping: 0.2
                    }
                }
            }
        }

        StackLayout {
            id: contentStack
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 8.0
            Layout.topMargin: 12.0

            ListView {
                id: channelListView
                anchors.fill: parent
                highlight: highlight // TODO: finish highlight active channel feature
                spacing: 4.0
                // model: ChannelModel { id: serverChannels }
                model: chatClientManager.channelModel
                delegate: Item {
                    width: ListView.view.width
                    height: delegateText.implicitHeight
                    MouseArea {
                        id: channelItemArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            console.log("Clicked channel:", name);
                            // e.g. set proxy model from chatClientManager:
                            // const channelProxy = chatClientManager.proxyForChannel(name);
                            channelListView.currentIndex = index;
                            root.channelSelected(payload);
                        }

                        Text {
                            id: delegateText
                            padding: 6.0
                            text: name
                            font.bold: true
                            font.pointSize: 10.0
                            color: channelItemArea.containsMouse ? ThemeManager.theme.color("text", "highlight") : ThemeManager.theme.color("text")
                        }
                    }
                }
            }

            ListView {
                id: userListView
                model: UserStatusModel { id: connectedUsers }
                delegate: Item {
                    width: ListView.view.width
                    height: userStatusText.implicitHeight
                    MouseArea {
                        id: userItemArea
                        anchors.fill: parent
                        hoverEnabled: true
                        cursorShape: Qt.PointingHandCursor
                        onClicked: {
                            console.log("Clicked user:", username);
                        }

                        Text {
                            id: userStatusText
                            padding: 6.0
                            text: username
                            font.bold: true
                            font.pointSize: 10.0
                            color: userItemArea.containsMouse ? ThemeManager.theme.color("text", "highlight") : ThemeManager.theme.color("text")
                        }
                    }
                }
            }
        }
    }

    Connections {
        target: chatClientManager.broker

        function onConnectedUsersReceived(users) {
            connectedUsers.setUsers(users);
        }
    }
}
