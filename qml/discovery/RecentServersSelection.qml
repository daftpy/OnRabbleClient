import QtQuick 2.15
import QtQuick.Controls 2.15
import OnRabbleClient

Item {
    id: recentSelector
    width: parent.width
    // Ensure height recalculates if contentHeight changes
    // height: listView.contentHeight
    height: rectangle.height

    signal serverSelected(discoveryPayload payload)

    // Model instance, directly usable from QML
    DiscoveryPayloadListModel {
        id: discoveryModel
    }

    Rectangle {
        id: rectangle
        width: parent.width
        height: listView.height + 10
        color: ThemeManager.theme.color("slate", "2")

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            height: 1
            color: ThemeManager.theme.color("slate", "4")
        }

        ListView {
            id: listView
            anchors.centerIn: parent
            width: parent.width - 10
            height: Math.min(contentHeight, 175)
            clip: true

            model: discoveryModel

            delegate: ServerListItem {

                // Connect the delegate's clicked signal to the view's serverSelected signal
                onClicked: {
                    // Emit the server selected signal, sending the payload at the given index
                    recentSelector.serverSelected(discoveryModel.get(index));
                }
            }
        }

        onVisibleChanged: {
            if (visible) {
                console.log("RecentServerSelection activated (visible)");
                discoveryModel.load(); // Load data
            }
        }
    }
}
