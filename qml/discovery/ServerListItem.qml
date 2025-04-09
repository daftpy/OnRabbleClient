import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import OnRabbleClient

Item {
    id: root
    required property string serverName
    required property int index

    signal clicked()
    signal deleteClicked(int itemIndex)

    implicitWidth: ListView.view.width
    implicitHeight: layout.implicitHeight + 16.0

    HoverHandler {
        id: hoverHandler
        cursorShape: Qt.PointingHandCursor
    }

    TapHandler {
        id: tapHandler
        acceptedButtons: Qt.LeftButton
        cursorShape: Qt.PointingHandCursor

        onTapped: {
            // Only process the root click if the mouse is NOT currently over the delete icon
            if (!deleteHoverHandler.hovered) {
                console.log("Root TapHandler fired for:", root.serverName)
                root.clicked()
            } else {
                // Optional: Log that the root click was deliberately ignored
                console.log("Root TapHandler suppressed (tap was on delete icon)")
            }
        }
    }

    Rectangle {
        width: parent.width
        height: root.height
        color: hoverHandler.hovered ? ThemeManager.theme.color("primary", "dark") : "#00000000"
        RowLayout {
            id: layout
            width: parent.width - 16.0
            anchors.centerIn: parent
            spacing: 8

            Text {
                id: nameText
                font.weight: Font.Bold
                text: root.serverName
                elide: Text.ElideRight
                Layout.maximumWidth: 200
                color: ThemeManager.theme.color("text", "highlight")
            }

            Text {
                id: msgText
                Layout.fillWidth: true
                text: "placeholder server motto message."
                elide: Text.ElideRight
                color: ThemeManager.theme.color("text")
            }

            Item {
                id: deleteIconContainer
                width: deleteIcon.implicitWidth
                height: deleteIcon.implicitHeight
                Layout.alignment: Qt.AlignVCenter // Align vertically within the row

                CrossCircledIcon {
                    id: deleteIcon
                    anchors.centerIn: parent // Center icon within its container
                    // Bind the color directly to the hoverHandler
                    color: deleteHoverHandler.hovered
                        ? ThemeManager.theme.color("danger")
                        : hoverHandler.hovered
                            ? ThemeManager.theme.color("text", "highlight")
                            : ThemeManager.theme.color("text", "muted")
                }

                HoverHandler {
                    id: deleteHoverHandler // Tracks hover specifically for the delete icon
                }

                TapHandler {
                    id: deleteTapHandler // Handles taps specifically for the delete icon
                    acceptedButtons: Qt.LeftButton
                    cursorShape: Qt.PointingHandCursor // Pointing hand ONLY over the icon
                    onTapped: {
                        console.log("Delete TapHandler fired for:", root.serverName, "index:", root.index)
                        // Signal that this handler dealt with the event.
                        // While it doesn't stop the root handler directly here, it's good practice.
                        root.deleteClicked(root.index)
                    }
                }
            }
        }
        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            height: 1.0
            color: ThemeManager.theme.color("border")
        }
    }
}
