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
        const index = privateChatViewInstantiator.userToIndex[payload.id];
        if (index !== undefined) {
            privateChatStack.currentIndex = index;
            console.log("Switched to PrivateChatView for", payload.username, "at index", index);
        } else {
            console.warn("No chat view found for", payload.username);
            chatClientManager.proxyForPrivateUser(user.id);
        }
    }

    StackLayout {
        id: privateChatStack
        anchors.fill: parent
        Component {
            id: privateChatComponent

            ChatMessageView {
                required property string targetUserId

                messageModel: chatClientManager.proxyForPrivateUser(targetUserId)
            }
        }

        Instantiator {
            id: privateChatViewInstantiator

            // maps channelName to stackLayout index
            property var userToIndex: ({})

            // Use the channelModel contents to instantiate the ChatViews, as
            // we should have one chat view per channel
            model: chatClientManager.privateChatMessageProxyList
            delegate: privateChatComponent

            onObjectAdded: (index, object) => {
                object.parent = privateChatStack;
                userToIndex[object.targetUserId] = index; // Store index
                console.log("Inserted PrivateChatView for", object.targetUserId, "at index", index);
            }

            onObjectRemoved: (index, object) => {
                object.destroy();
            }
        }
    }

}
