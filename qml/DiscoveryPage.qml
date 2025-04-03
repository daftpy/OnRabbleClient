import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import OnRabbleClient

Page {
    id: root
    anchors.fill: parent

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
                text: "https://example.com/"
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

    DiscoveryManager {
        id: discoveryManager

        onDiscovered: (payload) => {
            console.log("DiscoveryManagerQML: Payload received -", payload);

            // Emit the discoveryCompleted signal
            discoveryCompleted(payload);
        }

        onDiscoveryFailed: (error) => {
            console.log("DiscoveryManagerQML: Discovery failed -", error);
            errorText.text = "Discovery Failed"
       }
    }
}
