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
            color: ThemeManager.theme.color("background", "darker")


            Column {
                id: column
                width: parent.width
                padding: 8.0
                Row {
                    spacing: 6.0
                    anchors.horizontalCenter: parent.horizontalCenter
                    visible: errorText.text.length > 0 ? false : true
                    GlobeIcon {
                        anchors.verticalCenter: parent.verticalCenter
                        color: ThemeManager.theme.color("text")
                    }

                    Text {
                        anchors.verticalCenter: parent.verticalCenter
                        text: "Discovery"
                        font.bold: true
                        color: ThemeManager.theme.color("text")
                    }
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
                        color: ThemeManager.theme.color("danger")
                    }
                    Text {
                        id: errorText
                        text: ""
                        color: ThemeManager.theme.color("danger")
                    }
                    visible: errorText.text.length > 0 ? true : false
                }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: ThemeManager.theme.color("background", "dark")

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
                    color: ThemeManager.theme.color("background")
                    border.color: urlInput.focus ? ThemeManager.theme.color("primary") : ThemeManager.theme.color("background", "lighter");
                    radius: 6.0

                    RowLayout {
                        width: parent.width

                        MagnifyingGlassIcon {
                            Layout.leftMargin: 8.0
                            color: ThemeManager.theme.color("text", "highlight")
                        }

                        TextInput {
                            id: urlInput
                            text: "Enter a discovery url"
                            Layout.fillWidth: true
                            padding: 8.0
                            color: ThemeManager.theme.color("text")
                            clip: true

                            onTextEdited: {
                                errorText.text = "";
                            }
                            onAccepted: {
                                discoveryManager.discover(urlInput.text);
                                urlInput.focus = false;
                            }
                        }
                    }
                }

                Button {
                    id: authButton
                    onClicked: discoveryManager.discover(urlInput.text);
                    anchors.horizontalCenter: parent.horizontalCenter
                    contentItem: Text {
                        text: "Authenticate"
                        color: ThemeManager.theme.color("text", "highlight")
                        font.pointSize: 8
                        font.bold: true
                    }

                    background: Rectangle {
                        anchors.fill: parent
                        radius: 6
                        color: authButton.hovered ? ThemeManager.theme.color("primary", "light") : ThemeManager.theme.color("primary")
                        border.color: ThemeManager.theme.color("primary")
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
