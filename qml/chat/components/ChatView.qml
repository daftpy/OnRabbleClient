import QtQuick
import QtQuick.Layouts
import OnRabbleClient

Rectangle {
    id: root
    required property ChatMessageModel chatMessageModel
    Layout.fillWidth: true
    Layout.preferredWidth: 600.0
    Layout.fillHeight: true
    color: ThemeManager.theme.color("background", "light")

        ListView {
            id: chatListView
            anchors.fill: parent
            model: root.chatMessageModel
            spacing: 6.0

            delegate: Item {
                width: ListView.view.width
                height: childrenRect.height

                ColumnLayout {
                    id: delegateLayouut
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width - 16.0
                    spacing: 2.0
                    RowLayout {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 15.0
                        PersonIcon {}
                        Text {
                            text: username
                            font.bold: true
                            font.pointSize: 10.0
                            color: ThemeManager.theme.color("text")
                        }
                    }

                    Text {
                        Layout.fillWidth: true
                        text: message
                        font.pointSize: 10.0
                        wrapMode: Text.Wrap
                        color: ThemeManager.theme.color("text")
                    }
                }
            }

            // scroll to the end on load
            Component.onCompleted: {
                if (chatListView.count > 0) {
                    chatListView.positionViewAtEnd();
                }
            }

            // scroll to the end on new messages
            onCountChanged: {
                if (chatListView.count > 0) {
                    chatListView.positionViewAtEnd();
                }
            }
        }
}
