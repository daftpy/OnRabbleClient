import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import OnRabbleClient

Page {
    id: root

    // Aliases
    property alias urlInput: urlInput // allows input to be cleared on authentication

    // Signals
    signal discoveryCompleted(var payload)

    header: Column {
        padding: 5.0
        Text {
            width: parent.width
            text: "Discovery"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
        }
        Text {
            id: errorText
            topPadding: 5.0
            width: parent.width
            horizontalAlignment: Text.AlignHCenter
            text: ""
            color: "red"
        }
    }

    ColumnLayout {
        anchors.fill: parent
        Column {
            Layout.fillWidth: true
            spacing: 20.0
            TextInput {
                id: urlInput
                text: "Enter a discovery url"
                anchors.horizontalCenter: parent.horizontalCenter
                onTextEdited: {
                    errorText.text = "";
                }
            }

            Button {
                text: "Authenticate"
                onClicked: discoveryManager.discover(urlInput.text);
                anchors.horizontalCenter: parent.horizontalCenter
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
            errorText.text = "Discovery Failed"
       }
    }
}
