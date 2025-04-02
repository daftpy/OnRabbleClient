import QtQuick
import OnRabbleClient

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    DiscoveryPage {
        id: discoveryPage
    }

    WebsocketManager {
        id: websocketManager
    }
}
