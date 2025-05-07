import QtQuick
import QtQuick.Layouts
import OnRabbleClient


Item {
    id: root
    required property ClientManager chatClientManager
    property string currentChannelName: ""

    Layout.fillWidth: true
    Layout.fillHeight: true

    function selectChannelView(payload) {
        const index = chatViewInstantiator.channelToIndex[payload.name];
        if (index !== undefined) {
            chatStack.currentIndex = index;
            currentChannelName = payload.name;
            console.log("ChatView: Switched to index", index, "for channel", payload.name);
        } else {
            console.warn("ChatView: No view found for", channelName);
        }
    }

    Connections {
        target: chatClientManager

        // This handles the signal after the activeChannels
        // have been received and the proxy models have been created to filter
        // the chat messages
        function onActiveChannelsReady(proxyList) {
            if (!proxyList || proxyList.length === 0) {
                console.warn("No channels received.");
                return;
            }
            currentChannelName = proxyList[0].name;
        }
    }

    StackLayout {
        id: chatStack
        anchors.fill: parent

        Component {
            id: chatChannelComponent
            Item {
                required property string name
                Layout.fillWidth: true
                Layout.fillHeight: true

                Rectangle {
                    anchors.fill: parent
                    color: ThemeManager.theme.color("background", "light")
                    ChatMessageView { messageModel: root.chatClientManager.proxyForChannel(name) }
                }
            }
        }

        Instantiator {
            id: chatViewInstantiator

            // maps channelName to stackLayout index
            property var channelToIndex: ({})

            // Use the channelModel contents to instantiate the ChatViews, as
            // we should have one chat view per channel
            model: chatClientManager.channelProxyList
            delegate: chatChannelComponent

            onObjectAdded: (index, object) => {
                object.parent = chatStack;
               channelToIndex[object.name] = index; // Store index
               console.log("Inserted ChatView for", object.name, "at index", index);
            }

            onObjectRemoved: (index, object) => {
                object.destroy();
            }
        }
    }
}
