import QtQuick
import QtQuick.Layouts
import OnRabbleClient


Item {
    id: root
    required property ChatClientManager chatClientManager
    property alias chatViewInstantiator: chatViewInstantiator
    property alias currentIndex: chatStack.currentIndex
    Layout.fillWidth: true
    Layout.fillHeight: true

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
                    ChatMessageView { chatMessageModel: root.chatClientManager.proxyForChannel(name) }
                }
            }
        }

        Instantiator {
            id: chatViewInstantiator

            // maps channelName to stackLayout index
            property var channelToIndex: ({})

            model: channelsReady ? chatSidePanel.channelModel : []
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
