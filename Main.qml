import QtQuick 2.15
import QtQuick.Controls 2.15
import OnRabbleClient
import "qml/chat/utils.js" as ChatUtils

ApplicationWindow {
    visible: true
    width: 640
    height: 660
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

        initialItem: discoveryPage
    }

    DiscoveryPage {
        id: discoveryPage

        onDiscoveryCompleted: (payload) => {
            stackView.push(authPageComponent, { payload: payload });
        }
    }

    Component {
        id: authPageComponent

        AuthBrowserPage {
            onLoginCompleted: (payload, token) => {
                discoveryPage.urlInput.text = "Enter a discovery url"
                stackView.pop();
                openChatWindow(payload, token)
            }

            onLoginCanceled: {
                stackView.pop()
            }
        }
    }
}
