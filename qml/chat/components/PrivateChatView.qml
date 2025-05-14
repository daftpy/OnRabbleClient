import QtQuick
import QtQuick.Layouts
import OnRabbleClient

Rectangle {
    id: root
    required property ClientManager chatClientManager
    property string currentUsername: ""
    property userStatusPayload user
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: ThemeManager.theme.color("background", "light")

    function selectUserView(payload) {
        currentUsername = payload.username;
        user = payload;

        // Find the index in privateMessageProxyList
        const proxyList = chatClientManager.privateMessageProxyList;
        for (let i = 0; i < proxyList.length; i++) {
            if (proxyList[i].targetUserId === payload.id) {
                privateChatStack.currentIndex = i;
                console.log("Switched to PrivateChatView for", payload.username, "at index", i);
                return;
            }
        }

        console.warn("No chat view found for", payload.username, "— creating one");
        chatClientManager.proxyForPrivateUser(payload.id);
    }


    StackLayout {
        id: privateChatStack
        anchors.fill: parent

        Repeater {
            id: privateChatRepeater
            model: chatClientManager.privateMessageProxyList

            ChatMessageView {
                required property string targetUserId
                messageModel: chatClientManager.proxyForPrivateUser(targetUserId)
            }
        }
    }

}
