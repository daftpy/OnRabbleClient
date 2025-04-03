import QtQuick 2.15
import QtQuick.Controls 2.15
import OnRabbleClient
import "AuthUtils.js" as AuthUtils
import "ChatUtils.js" as ChatUtils

ApplicationWindow {
    visible: true
    width: 640
    height: 580
    title: qsTr("Hello World")

    StackView {
        id: stackView
        anchors.fill: parent

        // The application starts at the DiscoveryPage
        initialItem: DiscoveryPage {
            id: discoveryPage

            // Signal handler for when discovery is complete.
            onDiscoveryCompleted: (payload) => {
                console.log("signal working", payload);

                // Create and push the Auth page to the front
                AuthUtils.pushAuthPageWith(stackView, payload, (payload, token) => {
                    // Authentication complete lambda
                    console.log("MainWindow: login complete!", payload, token);

                    // Reset the DiscoveryPage input
                    discoveryPage.urlInput.text = "Enter a discovery url";

                    // Create the chat window
                    ChatUtils.openChatWindow(payload, token);
                });
            }

        }
    }
}
