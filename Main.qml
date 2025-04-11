import QtQuick 2.15
import QtQuick.Controls 2.15
import OnRabbleClient
import "qml/auth/utils.js" as AuthUtils
import "qml/chat/utils.js" as ChatUtils

ApplicationWindow {
    visible: true
    width: 640
    height: 580
    title: qsTr("OnRabble")

    // A list of the chat windows
    // property var chatServers: []
    ListModel { id: chatServers; dynamicRoles: true }

    Instantiator {
        model: ChatServerModel {id: chatServersModel }
        delegate: ChatWindow {}

    }

    // Creates/Updates a ChatServerModel entry, creating a delegate
    // ChatWindow
    function openChatWindow(payload, token) {
        chatServersModel.openChatWindoow(payload, token)
    }

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
                    console.log("MainWindow: login completed for", payload.serverName);

                    // Reset the DiscoveryPage input
                    discoveryPage.urlInput.text = "Enter a discovery url";

                    // Create the chat window
                    openChatWindow(payload, token);
                });
            }
        }
    }
}
