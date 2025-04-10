// qml/AuthBrowserPage.qml
import QtQuick 2.15
import QtQuick.Layouts
import QtQuick.Controls.Basic 2.15
import QtWebEngine 1.15
import OnRabbleClient

Page {
    id: authPage

    // Properties
    property discoveryPayload payload

    // Signals
    signal loginCompleted(discoveryPayload payload, string token)
    signal loginCanceled()

    header: AuthHeader {
        id: authHeader
    }

    // Auth page body
    Rectangle {
        // Fill the page
        anchors.fill: parent
        color: ThemeManager.theme.color("background")

        /*
            This is the WebView, Indicator, and Error area. When the page
            loads the indicator is visible while a health-check is done
            on the auth service. If the auth service is healthy, the WebView
            becomes visible. If the auth service is not ready, an error is
            displayed.

            Only one item is visible at a given time: The WebView, error, or
            indicator.
        */
        Item {
            anchors.fill: parent
            WebEngineView {
                id: webView
                width: parent.width
                height: parent.height
                url: ""
                visible: url.length > 0

                onVisibleChanged: {
                    console.log("Visibility changed"< visibility);
                }
            }
            BusyIndicator {
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                running: authHeader.errorText.text.length === 0
                visible: authHeader.errorText.text.length === 0 && !webView.visible
            }
            Text {
                text: "There was an issue authenticating with " + "<b>" + payload.serverName + ".</b>" + " Contact a server administrator."
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width
                padding: 12.0
                color: ThemeManager.theme.color("text")
                horizontalAlignment: Text.AlignHCenter
                visible: authHeader.errorText.text.length > 0
                wrapMode: Text.Wrap
            }
        }
    }

    footer: DangerButton {
        buttonText: "Cancel"
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
            console.log(error);
           authHeader.errorText.text = error;
       }
        onAuthorizationUrlAvailable: (url) => {
            console.log("WebView loading URL:", url);
            webView.url = url;
            webView.visible = true;
        }
    }
    Component.onCompleted: {
        authManager.beginAuthorization(payload);
    }
}
