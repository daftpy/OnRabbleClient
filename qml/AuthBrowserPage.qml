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

    header: Rectangle {
        id: headerRoot
        width: parent.width
        height: layout.height + 16.0
        color: ThemeManager.theme.color("background", "dark")

        ColumnLayout {
            id: layout
            anchors.centerIn: parent
            width: parent.width
            Row {
                Layout.alignment: Layout.Center
                spacing: 6.0

                Text {
                    id: titleLabel
                    color: ThemeManager.theme.color("text")
                    text: qsTr("Authenticating with") + " <b>" + payload.serverName + "</b>"
                    textFormat: Text.RichText
                }
                LockOpenIcon {
                    id: titleIcon
                    color: ThemeManager.theme.color("text")
                }
                visible: errorText.text.length === 0 ? true : false
            }
            Row {
                id: errorMessage
                Layout.alignment: Layout.Center
                spacing: 6.0
                leftPadding: 12.0
                rightPadding: 12.0

                DangerIcon {
                    anchors.verticalCenter: parent.verticalCenter
                    id: errorIcon
                    color: ThemeManager.theme.color("danger")
                }

                Text {
                    id: errorText
                    color: ThemeManager.theme.color("danger")
                    width: Math.min(headerRoot.width - 15.0 - errorMessage.spacing - errorMessage.leftPadding * 2, textMetrics.width + 15.0)
                    text: ""
                    elide: Text.ElideRight
                    maximumLineCount: 2
                    wrapMode: Text.Wrap
                    horizontalAlignment: Text.AlignHCenter
                    onTextChanged: {
                        textMetrics.text = text
                    }
                }
                visible: errorText.text.length > 0 ? true : false
                TextMetrics {
                    id: textMetrics
                    font: errorText.font
                }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: ThemeManager.theme.color("background")
        ColumnLayout {
            anchors.fill: parent
            WebEngineView {
                id: webView
                Layout.fillWidth: true
                Layout.fillHeight: true
                url: ""
                visible: url > 0 ? true : false
            }
            BusyIndicator {
                Layout.alignment: Layout.Center
                running: errorText.text.length === 0
                visible: errorText.text.length === 0
            }
            Text {
                text: "Could not connect to authentication server for " + "<b>serverName. </b>" + "Contact a server administrator."
                Layout.fillWidth: true
                padding: 12.0
                color: ThemeManager.theme.color("text")
                horizontalAlignment: Text.AlignHCenter
                visible: errorText.text.length > 0
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
