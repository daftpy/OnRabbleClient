import QtQuick
import QtQuick.Layouts
import OnRabbleClient

ListView {
    // required property ChannelProxyModel chatMessageModel
    required property var messageModel
    id: root
    anchors.fill: parent
    anchors.margins: 12.0
    model: messageModel
    spacing: 6.0
    verticalLayoutDirection: ListView.BottomToTop
    highlightFollowsCurrentItem: false
    clip: true

    delegate: Item {
        width: ListView.view.width
        height: childrenRect.height

        ColumnLayout {
            id: delegateLayout
            width: parent.width
            spacing: 2.0

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

            RowLayout {
                Layout.fillWidth: true
                Layout.preferredHeight: 15.0
                visible: parent.showUsername  // only show if needed
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
        console.log("scrolling to last", currentIndex, " count", count)
        Qt.callLater(function() {
            root.positionViewAtBeginning();
        })
    }
}
