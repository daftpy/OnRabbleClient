import QtQuick
import QtQuick.Layouts
import OnRabbleClient

ListView {
    // required property ChannelProxyModel chatMessageModel
    required property var messageModel
    id: root
    anchors.fill: parent
    anchors.topMargin: 6.0
    anchors.bottomMargin: 6.0
    model: messageModel
    verticalLayoutDirection: ListView.BottomToTop
    highlightFollowsCurrentItem: false
    clip: true

    delegate: Item {
        width: ListView.view.width
        height: delegateLayout.implicitHeight + 8

        Rectangle {
            height: parent.height
            width: parent.width
            color: delegateHoverHandler.hovered ? ThemeManager.theme.color("background", "lightest") : "transparent"

            Column {
                anchors.centerIn: parent
                id: delegateLayout
                width: parent.width - 16

                // Don't show the username repetitively
                // Check the previous message to see if we need
                // to show the username again
                property bool showUsername: {
                    if (index === count - 1) {
                        return true;
                    }
                    let previousMessage = root.model.get(index + 1);
                    return previousMessage.ownerId !== ownerId;
                }

                Row {
                    width: parent.width
                    height: visible ? 18.0 : 0
                    spacing: visible ? 2.0 : 0
                    visible: parent.showUsername  // only show if needed
                    PersonIcon {}
                    Text {
                        text: username
                        font.bold: true
                        font.pointSize: 10.0
                        color: ThemeManager.theme.color("text")
                    }
                }

                TextEdit {
                    text: message
                    font.pointSize: 10.0
                    wrapMode: Text.Wrap
                    color: ThemeManager.theme.color("text")
                    readOnly: true
                    width: Math.min(implicitWidth + 6.0, parent.width)
                }
            }

            HoverHandler {
                id: delegateHoverHandler
            }
        }
    }


    onCountChanged: {
        console.log("scrolling to last", currentIndex, " count", count)
        Qt.callLater(function() {
            root.positionViewAtBeginning();
        })
    }
}
