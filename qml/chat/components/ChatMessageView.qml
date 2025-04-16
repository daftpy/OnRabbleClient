import QtQuick
import QtQuick.Layouts
import OnRabbleClient

ListView {
    required property ChannelProxyModel chatMessageModel
    id: root
    anchors.fill: parent
    anchors.margins: 12.0
    model: chatMessageModel
    spacing: 6.0
    verticalLayoutDirection: ListView.BottomToTop
    highlightFollowsCurrentItem: false
    clip: true

    delegate: Item {
        width: ListView.view.width
        height: childrenRect.height

        ColumnLayout {
            id: delegateLayouut
            width: parent.width
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
        console.log("scrolling to last", currentIndex, " count", count)
        Qt.callLater(function() {
            root.positionViewAtBeginning();
        })
    }
}
