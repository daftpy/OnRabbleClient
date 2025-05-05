import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.VectorImage
import OnRabbleClient

Item {
    id: recentSelector
    width: parent.width
    // Ensure height recalculates if contentHeight changes
    height: column.height

    signal serverSelected(discoveryPayload payload)

    // Model instance, directly usable from QML
    DiscoveryModel {
        id: discoveryModel
    }
    Column {
        id: column
        width: parent.width


            Rectangle {
                id: recentContainer
                width: parent.width
                height: tab.height
                color: ThemeManager.theme.color("background", "dark")

                    // RecentServers button
                    Rectangle {
                        id: tab
                        height: tabText.implicitHeight + 12
                        width: tabText.implicitWidth + tabIcon.width + 24
                        color: ThemeManager.theme.color("background", "light")
                        radius: 6.0

                        Row {
                            anchors.centerIn: parent
                            spacing: 4.0
                            Text {
                                id: tabText
                                text: "Recent Servers"
                                font.pointSize: 10.0
                                font.bold: true
                                height: tabIcon.height
                                verticalAlignment: Text.AlignVCenter
                                color: ThemeManager.theme.color("text")
                            }
                            PlusIcon {
                                id: tabIcon
                                color: ThemeManager.theme.color("text")
                            }
                        }

                        // provides flat corners for the bottom of the button
                        Rectangle {
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.bottom: parent.bottom
                            width: parent.width
                            height: 10.0
                            color: parent.color
                        }
                        MouseArea {
                            anchors.fill: parent
                            acceptedButtons: Qt.LeftButton
                            cursorShape: Qt.PointingHandCursor
                            onClicked: (mouse) => {
                                if (mouse.button === Qt.LeftButton){
                                    listViewContainer.visible = !listViewContainer.visible
                                }
                            }
                        }
                    }
            }

        // RecentServers listView
        Rectangle {
            id: listViewContainer
            width: parent.width
            height: listView.height
            color: ThemeManager.theme.color("background")

            ListView {
                id: listView
                anchors.centerIn: parent
                width: parent.width
                height: Math.min(contentHeight, 175)
                clip: true

                model: discoveryModel

                delegate: ServerListItem {

                    // Connect the delegate's clicked signal to the view's serverSelected signal
                    onClicked: {
                        // Emit the server selected signal, sending the payload at the given index
                        recentSelector.serverSelected(discoveryModel.get(index));
                    }

                    onDeleteClicked: (itemIndex) => {
                        // Get the discovery payload
                        let payload = discoveryModel.get(itemIndex);
                        console.log("Payload", payload.serverId, "removed from recent servers list");

                        // Remove the payload from storage
                        if (DiscoveryStoreManager.removePayloadById(payload.serverId)) {
                            // Remove the payload from the model
                            discoveryModel.removePayload(itemIndex);
                        }


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
}
