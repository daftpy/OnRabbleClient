import QtQuick 2.15
import QtQuick.Controls 2.15
import OnRabbleClient

Item {
    id: recentSelector
    width: parent.width
    height: listView.contentHeight

    signal serverSelected(discoveryPayload payload)

    // Model instance, directly usable from QML
    DiscoveryPayloadListModel {
        id: discoveryModel
    }

    ListView {
        id: listView
        width: parent.width
        spacing: 8
        model: discoveryModel

        delegate: Button {
            text: serverName
            onClicked: {
                console.log("Selected recent server:", serverName)

                // Emit the signal to pass the payload
                serverSelected(discoveryModel.get(index))
            }
        }
    }

    onVisibleChanged: {
        if (visible) {
            console.log("RecentServerSelection activated (visible)");
            discoveryModel.load();
        }
    }
}
