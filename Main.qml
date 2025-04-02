import QtQuick
import QtQuick.Controls.Basic
import OnRabbleClient

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Column {
        Text {
            id: tokenLabel
            text: "Access token:";
        }
        TextInput {
            id: urlInput
            text: "https://example.com/"
        }

        Button {
            text: "Authenticate"
            onClicked: discoveryManager.discover(urlInput.text);
        }
    }

    AuthManager {
        id: authManager
        onAuthenticated: (payload, accessToken) => {
            console.log("AuthManager: authentication process complete");
            console.log("AuthManager: chat endpoint -", payload.chatEndpoint)
            websocketManager.initiateConnection(payload, accessToken);
        }
    }
    DiscoveryManager {
        id: discoveryManager

        onDiscovered: (payload) => {
            console.log("DiscoveryManagerQML: Payload received:", payload);

            // Use the payload to authenticate
            authManager.authenticate(payload);
        }
    }
    WebsocketManager {
        id: websocketManager
    }
}
