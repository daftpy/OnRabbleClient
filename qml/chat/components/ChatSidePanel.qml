import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import QtQuick.Effects
import OnRabbleClient

Rectangle {
    id: root
    required property ChatClientManager chatClientManager
    required property ChannelProxyModel currentChannelProxy // new, allows the ChatView to be set to specific channel
    property alias channelModel: serverChannels

    signal channelSelected(var channelProxy)

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
                    implicitHeight: childrenRect.height
                    Row {
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
                    color: channelUserTabBar.currentIndex === channelsTabButton.TabBar.index ? ThemeManager.theme.color("primary") : ThemeManager.theme.color("background", "lightest")
                    HoverHandler {
                        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }
            TabButton {
                id: usersTabButton
                contentItem: Item {
                    implicitHeight: childrenRect.height + 6.0
                    Row {
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

        ListView {
            id: channelListView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 8.0
            Layout.topMargin: 12.0
            highlight: highlight // TODO: finish highlight active channel feature
            spacing: 4.0
            model: ChatChannelPayloadModel { id: serverChannels }
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
                        const channelProxy = chatClientManager.proxyForChannel(name);
                        // root.currentChannelProxy = channelProxy;

                        channelListView.currentIndex = index;
                        root.channelSelected(channelProxy);
                    }

                    Text {
                        id: delegateText
                        padding: 6.0
                        text: name
                        font.bold: true
                        font.pointSize: 10.0
                        color: ThemeManager.theme.color("text")
                    }
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
