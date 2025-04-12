import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import OnRabbleClient

Page {
    id: root
    required property ChatClientManager chatClientManager
    required property discoveryPayload payload
    property ChatMessageModel chatMessageModel: ChatMessageModel {}

    objectName: "ChatPage"

    RowLayout {
        anchors.fill: parent
        spacing: 0
        ChatSidePanel {
            chatClientManager: root.chatClientManager
        }

        ChatView {
            chatMessageModel: root.chatMessageModel
        }
    }

    footer: Rectangle {
        width: parent.width
        height: 24.0
        color: ThemeManager.theme.color("background", "dark")

        RowLayout {
            anchors.fill: parent

            RowLayout {
                Layout.fillWidth: true
                Layout.minimumWidth: 175.0
                Layout.maximumWidth: 250.0
                Layout.leftMargin: 8.0
                PersonIcon {

                }

                Text {
                    width: parent.width
                    color: ThemeManager.theme.color("text", "highlight")
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                    text: root.chatClientManager.user.username // get the username from the chatClientManager
                }
            }
            Item {
                Layout.fillWidth: true
                Layout.preferredWidth: 600.0
                Text {
                    id: activeChannelText
                    anchors.centerIn: parent
                    text: "Channel location"
                    color: ThemeManager.theme.color("text", "highlight")
                }
            }
        }
    }

    Connections {
        target: chatClientManager

        function onActiveChannelsReceived(channels) {
            console.log("ChatPage: Received active channels:");
            for (let i = 0; i < channels.length; i++) {
                console.log(`  • ${channels[i].name}: ${channels[i].description}`);
            }
        }
    }
    Connections {
        target: chatClientManager.broker

        function onActiveChannelChanged(channel) {
            console.log("Sidebar: Received channels from broker:", channel);
            activeChannelText.text = `# ${channel}`;
        }

        function onBulkChatMessagesReceived(messages) {
                console.log(`ChatPage: Received ${messages.length} bulk chat messages`);
                for (let i = 0; i < messages.length; i++) {
                    root.chatMessageModel.appendMessage(messages[i]);
                }
            }
    }
}
