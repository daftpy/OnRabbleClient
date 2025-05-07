import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import OnRabbleClient

Page {
    id: root
    objectName: "ChatPage"
    required property ClientManager chatClientManager
    required property discoveryPayload payload

    Rectangle {
        anchors.fill: parent
        color: ThemeManager.theme.color("background", "light")

        RowLayout {
            anchors.fill: parent
            spacing: 0
            ChatSidePanel {
                id: chatSidePanel
                chatClientManager: root.chatClientManager

                // This is important. This is where the ChatSidePanel tells
                // the ChatView which channel was selected
                onChannelSelected: (payload) => {
                    baseChatView.selectChannelView(payload);

                    // If a channel is selected and the ChatView isn't visible, pop the chatStackView
                    if (chatStackView.currentItem !== baseChatView) chatStackView.pop();
                }

                onUserSelected: (payload) => {
                    privateChatView.selectUserView(payload);
                    // Push the chat view
                    if (chatStackView.currentItem !== privateChatView) chatStackView.push(privateChatView);
                }
            }

            // the chatView and privateChatView initialized, but hidden
            // ready to be attatched to chatStackView
            Item {
                id: parkedItems
                visible: false

                ChatView {
                    id: baseChatView
                    chatClientManager: root.chatClientManager
                }

                PrivateChatView {
                    id: privateChatView
                    chatClientManager: root.chatClientManager
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
                    clip: true
                    initialItem: baseChatView
                }

                ChatInput {
                    id: chatInput
                    onSendChatMessage: (message) => {
                        if (chatStackView.currentItem === privateChatView) {
                            console.log("Sending private message to", chatSidePanel.currentUserPayload);
                            const selectedUser = chatSidePanel.currentUserPayload;
                            if (selectedUser) {
                                console.log("Sending private message to", selectedUser.username);
                                root.chatClientManager.broker.sendPrivateChatMessage(JSON.stringify({
                                    recipientId: selectedUser.id,
                                    message: message
                                }));
                            }
                        } else {
                            // Otherwise send a chat message
                            root.chatClientManager.broker.sendChatMessage(JSON.stringify({
                                channel: "General",
                                message: message
                            }));
                        }
                   }
                }
            }
        }
    }

    footer: ChatPageFooter {
        id: chatPageFooter
        channelName: chatStackView.currentItem === baseChatView ? baseChatView.currentChannelName : privateChatView.currentUsername

        username: root.chatClientManager.user.username
    }
}
