import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls.Basic 2.15
import OnRabbleClient

Page {
    id: root

    // Aliases
    property alias urlInput: urlInput // allows input to be cleared on authentication

    // Signals
    signal discoveryCompleted(var payload)

    header: Item {
        width: parent.width
        height: column.implicitHeight

        Rectangle {
            anchors.fill: parent
            color: ThemeManager.theme.color("slate", "2")

            // Bottom border
            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                height: 1
                color: ThemeManager.theme.color("slate", "4")
            }


            Column {
                id: column
                width: parent.width
                padding: 8.0
                Text {
                    width: parent.width
                    text: "Discovery"
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    color: ThemeManager.theme.color("slate", "12")
                    visible: errorText.text.length > 0 ? false : true
                }
                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: errorLabel.implicitWidth + errorText.implicitWidth + spacing
                    height: errorLabel.implicitHeight
                    spacing: 3
                    Text {
                        id: errorLabel
                        text: "Error"

                        font.bold: true
                        color: ThemeManager.theme.color("ruby", "10")
                    }
                    Text {
                        id: errorText

                        horizontalAlignment: Text.AlignHCenter
                        text: ""
                        color: ThemeManager.theme.color("ruby", "10")
                    }
                    visible: errorText.text.length > 0 ? true : false
                }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: ThemeManager.theme.color("slate", "3")

        // Using the column layout to center the child column
        ColumnLayout {
            anchors.fill: parent

            Column {
                Layout.fillWidth: true
                spacing: 20.0
                Rectangle {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width - (parent.width * 0.2)
                    height: urlInput.height
                    color: ThemeManager.theme.color("slate", "4")
                    border.color: urlInput.focus ? ThemeManager.theme.color("indigo", "5") : ThemeManager.theme.color("slate", "6")
                    radius: 6.0

                    TextInput {
                        id: urlInput
                        text: "Enter a discovery url"
                        width: parent.width
                        verticalAlignment: Text.AlignVCenter
                        padding: 8.0
                        color: ThemeManager.theme.color("slate", "12")

                        onTextEdited: {
                            errorText.text = "";
                        }
                        onAccepted: {
                            discoveryManager.discover(urlInput.text);
                            urlInput.focus = false;
                        }
                    }
                }

                Button {
                    id: authButton
                    onClicked: discoveryManager.discover(urlInput.text);
                    anchors.horizontalCenter: parent.horizontalCenter
                    contentItem: Text {
                        text: "Authenticate"
                        color: ThemeManager.theme.color("indigo", "12")
                        font.pointSize: 8
                        font.bold: true
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        radius: 6
                        color: authButton.hovered ? ThemeManager.theme.color("indigo", "8") : ThemeManager.theme.color("indigo", "9")
                        border.color: ThemeManager.theme.color("indigo", "9")
                        border.width: 1
                    }
                }
            }

        }
    }

    footer: RecentServersSelection {
        onServerSelected: (payload) => {
            console.log("Selected recent server:", payload.serverName)

            // Emit discoveryCompleted signal to start auth process
            discoveryCompleted(payload);
        }
    }

    DiscoveryManager {
        id: discoveryManager

        onDiscovered: (payload) => {
            console.log("DiscoveryManagerQML: Payload received -", payload);

            // Emit discoveryCompleted signal to start auth process
            discoveryCompleted(payload);
        }

        onDiscoveryFailed: (error) => {
            console.log("DiscoveryManagerQML: Discovery failed -", error);
            errorText.text = "discovery failed"
       }
    }
}
