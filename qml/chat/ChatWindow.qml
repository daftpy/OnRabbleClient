import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts
import OnRabbleClient

ApplicationWindow {
    id: root
    width: 600
    height: 400
    visible: true
    minimumWidth: 600
    minimumHeight: 400
    title: payload.serverName

    required property discoveryPayload payload
    required property ClientManager chatClientManager

    StackView {
        id: chatWindowView
        anchors.fill: parent
        initialItem: chatPageComponent
    }

    // ChatPage component
    Component {
        id: chatPageComponent
        ChatPage {
            payload: root.payload
            chatClientManager: root.chatClientManager
        }
    }

    // ChatErrorPage component
    Component {
        id: chatErrorPageComponent
        ChatErrorPage {
            chatClientManager: root.chatClientManager
        }
    }

    // ChatClientManager signals
    Connections {
        target: chatClientManager

        // Push the chat page on succesful connection
        function onConnected() {
            if (chatWindowView.currentItem && chatWindowView.currentItem.objectName === "ChatPage") {
                return; // already on chat page
            }
            console.log("ChatWindow: Connected to chat server!");
            chatWindowView.push(chatPageComponent.createObject());
        }

        // Push the error page on connection error
        function onConnectionError(error) {
            console.error("ChatWindow: Connection error:", error);

            // Create the error page with the chat manager and error text
            const errorPage = chatErrorPageComponent.createObject(chatWindowView, {
                errorText: error
            });

            // Push the error page
            if (errorPage) {
                chatWindowView.push(errorPage);
            } else {
                console.error("Failed to create ChatErrorPage.");
            }
        }

        function onDisconnected() {
            console.error("ChatWindow: disconnected from the server");

            // Create the error page with the chat manager and error text
            const errorPage = chatErrorPageComponent.createObject(chatWindowView, {
                errorText: "Disconnected from the server"
            });

            // Push the error page
            if (errorPage) {
                chatWindowView.push(errorPage);
            } else {
                console.error("Failed to create ChatErrorPage.");
            }
        }
    }

    Component.onCompleted: {
        console.log("Chat window opened for: ", payload.serverName);
    }
}

