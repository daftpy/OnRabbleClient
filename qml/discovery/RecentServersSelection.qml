import QtQuick 2.15
import QtQuick.Controls 2.15
import OnRabbleClient

Item {
    id: recentSelector
    width: parent.width
    // Ensure height recalculates if contentHeight changes
    height: listView.contentHeight

    signal serverSelected(discoveryPayload payload)

    // Model instance, directly usable from QML
    DiscoveryPayloadListModel {
        id: discoveryModel
    }

    ListView {
        id: listView
        width: parent.width
        height: 200

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
