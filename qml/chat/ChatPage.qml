import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import OnRabbleClient

Page {
    id: root
    objectName: "ChatPage"
    required property ChatClientManager chatClientManager
    required property discoveryPayload payload

    RowLayout {
        anchors.fill: parent
        spacing: 0
        ChatSidePanel {
            id: chatSidePanel
            chatClientManager: root.chatClientManager

            // This is important. This is where the ChatSidePanel tells
            // the ChatView which channel was selected
            onChannelSelected: (name) => {
                baseChatView.selectChannelView(name);
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.preferredWidth: 600.0
            Layout.fillHeight: true
            spacing: 0

            StackView {
                id: chatStackView
                Layout.fillWidth: true
                Layout.fillHeight: true
                initialItem: baseChatView
            }

            ChatView {
                id: baseChatView
                chatClientManager: root.chatClientManager
                name: "ChatView"
            }

            ChatInput {

                onSendChatMessage: (message) => {
                root.chatClientManager.broker.sendChatMessage(JSON.stringify({
                   channel: "General",
                   message: message
                }));
               }
            }
        }
    }

    footer: ChatPageFooter {
        id: chatPageFooter
        channelName: baseChatView.currentChannelName

        username: root.chatClientManager.user.username
    }
}
