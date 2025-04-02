import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic
import OnRabbleClient

Page {
    id: root
    anchors.fill: parent

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

    AuthManager {
        id: authManager
        onAuthenticated: (payload, accessToken) => {
            console.log("AuthManager: authentication process complete");
            console.log("AuthManager: chat endpoint -", payload.chatEndpoint)
            // websocketManager.initiateConnection(payload, accessToken);
        }
        onAuthenticationError: (error) => {
           errorText.text = error;
       }
    }
    DiscoveryManager {
        id: discoveryManager

        onDiscovered: (payload) => {
            console.log("DiscoveryManagerQML: Payload received -", payload);

            // Use the payload to authenticate
            authManager.authenticate(payload);
        }
        onDiscoveryFailed: (error) => {
            console.log("DiscoveryManagerQML: Discovery failed -", error);
            errorText.text = "Discovery Failed"
       }
    }
}
