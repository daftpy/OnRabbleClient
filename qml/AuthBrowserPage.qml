// qml/AuthBrowserPage.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtWebEngine 1.15
import OnRabbleClient

Page {
    id: authPage

    // Properties
    property discoveryPayload payload

    // Signals
    signal loginCompleted(discoveryPayload payload, string token)
    signal loginCanceled()

    header: Rectangle {
        width: parent.width
        height: titleLabel.implicitHeight + 8.0
        color: ThemeManager.theme.color("background", "dark")

        Text {
            id: titleLabel
            color: ThemeManager.theme.color("text")
            anchors.centerIn: parent
            text: qsTr("Authenticating with") + " <b>" + payload.serverName + "</b>"
            textFormat: Text.RichText
        }
    }

    WebEngineView {
        id: webView
        anchors.fill: parent
        url: ""
    }

    footer: Button {
        text: "Cancel"
        onClicked: {
            loginCanceled();
            authManager.cancelAuthorization();
        }
    }

    AuthManager {
        id: authManager
        onAuthorizationSucceeded: (payload, accessToken) => {
            console.log("AuthManager: authentication process complete");
            console.log("AuthManager: chat endpoint -", payload.chatEndpoint)

            // Emit the login is complete with the payload and token
            // This is used to create the new ChatWindow and ChatClientManager
            loginCompleted(payload, accessToken);
        }
        onAuthorizationErrorOccurred: (error) => {
           errorText.text = error;
       }
        onAuthorizationUrlAvailable: (url) => {
            console.log("WebView loading URL:", url);
            webView.url = url;
        }
    }
    Component.onCompleted: {
        authManager.beginAuthorization(payload);
    }
}
