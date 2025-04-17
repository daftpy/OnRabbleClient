import QtQuick
import QtQuick.Layouts
import OnRabbleClient

Rectangle {
    id: root
    required property ChatClientManager chatClientManager
    property string currentUsername: ""
    property userStatusPayload user
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: ThemeManager.theme.color("background", "light")

    function selectUserView(payload) {
        currentUsername = payload.username;
        user = payload;
    }

    // ListView {
    //     id: messageList
    //     anchors.fill: parent

    //     model: (user && user.id !== "") ? chatClientManager.proxyForPrivateUser(user.id) : null

    //     delegate: Text {
    //         text: model.username + ": " + model.message
    //     }
    // }
    ChatMessageView {
        messageModel: (user && user.id !== "") ? chatClientManager.proxyForPrivateUser(user.id) : null
    }
}
