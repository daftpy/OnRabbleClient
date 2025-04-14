import QtQuick
import QtQuick.Layouts
import OnRabbleClient

Rectangle {
    id: root
    required property ChatMessageModel chatMessageModel
    Layout.fillWidth: true
    Layout.fillHeight: true
    Layout.preferredHeight: 450.0
    color: ThemeManager.theme.color("background", "light")
    Component {
        id: highlight
        Rectangle {
            width: 180; height: 40
            color: "lightsteelblue"; radius: 5
            y: list.currentItem.y
            Behavior on y {
                SpringAnimation {
                    spring: 3
                    damping: 0.2
                }
            }
        }
    }

        ListView {
            id: chatListView
            anchors.fill: parent
            model: root.chatMessageModel
            spacing: 6.0
            verticalLayoutDirection: ListView.BottomToTop
            highlightFollowsCurrentItem: false

            footer: Item {
                    id: scrollAnchor
                    width: 1
                    height: 1
                }

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
            onCountChanged: {
                console.log("scrolling to last", currentIndex)
                Qt.callLater(function() {
                    chatListView.positionViewAtBeginning();
                })
            }
        }
}
