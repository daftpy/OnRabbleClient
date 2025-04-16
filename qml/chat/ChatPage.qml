import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import OnRabbleClient

Page {
    id: root
    objectName: "ChatPage"
    required property ChatClientManager chatClientManager
    required property discoveryPayload payload

    // TODO: I think ChannelProxyModel should be switched to ChatChannelPayloadModel (rename to ChannelModel)
    property ChannelProxyModel chatChannelProxy: null
    property bool channelsReady: false

    // TODO: I think this should possibly be refactored out, or at least
    // a lot of this responsibility is duplicated. We aren't worried about
    // ChanelProxyModels here, those are created as needed in the ChatView component
    // here we should probably use ChatChannelPayloadModels. Maybe even move this
    // to the sidebar, or more of it.
    Connections {
        target: chatClientManager

        // This is emitted by the chatClientManager after the activeChannels
        // have been received and the proxy models have been created to filter
        // the chat messages
        function onActiveChannelsReady(proxyList) {
            if (!proxyList || proxyList.length === 0) {
                console.warn("No channel proxies were received.");
                return;
            }

            const proxy = proxyList[0];

            if (proxy) {
                root.chatChannelProxy = proxy;
                chatPageFooter.activeChannelText.text = `# ${proxy.name}`;
            } else {
                console.warn("No proxy found for", firstChannel.name);
            }

            root.channelsReady = true; // Now we can instantiate views
        }
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0
        ChatSidePanel {
            id: chatSidePanel
            chatClientManager: root.chatClientManager

            onChannelSelected: (name) => {
                const proxy = chatClientManager.proxyForChannel(name);

                root.chatChannelProxy = proxy; // Update the PAGE's property
                chatPageFooter.activeChannelText.text = `# ${proxy.name}`;

                let chatView = chatStackView.find(function(item) {
                    return item.name = "ChatView"
                });
                if (chatView) chatView.selectChannelView(proxy.name);
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
                initialItem: chatStackComponent
            }

            Component {
                id: chatStackComponent
                ChatView {
                    id: chatStack
                    chatClientManager: root.chatClientManager
                }
            }

            Rectangle {
                Layout.fillWidth: true
                Layout.preferredHeight: chatInputContainer.implicitHeight + chatInputContainer.anchors.margins * 2
                Layout.maximumHeight: 125.0
                color: ThemeManager.theme.color("background", "lightest")
                RowLayout {
                    id: chatInputContainer
                    anchors.fill: parent
                    anchors.margins: 6.0
                    spacing: 0
                    ScrollView {
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        TextArea {
                            id: chatInput
                            width: parent.width
                            wrapMode: TextEdit.Wrap
                            color: ThemeManager.theme.color("text")

                            Keys.onPressed: (event) => {
                                if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter) {
                                    if (!event.modifiers || event.modifiers === Qt.NoModifier) {
                                        // Send the message
                                        root.chatClientManager.broker.sendChatMessage(JSON.stringify({
                                            channel: "General",
                                            message: chatInput.text
                                        }));
                                        chatInput.clear();
                                        event.accepted = true;
                                    }
                                }
                            }
                        }
                    }
                    Button {
                        id: sendButton
                        Layout.fillHeight: true
                        Layout.preferredWidth: 75.0
                        contentItem: Item {
                            Row {
                                anchors.centerIn: parent
                                spacing: 3.0
                                Text {
                                    height: parent.height
                                    verticalAlignment: Text.AlignVCenter
                                    text: "Send"
                                    color: ThemeManager.theme.color("text")
                                    font.pointSize: 10.0
                                }
                                SendIcon {
                                    color: ThemeManager.theme.color("text")
                                }
                            }
                        }

                        onClicked: {
                            root.chatClientManager.broker.sendChatMessage(JSON.stringify({
                                channel: "General",
                                message: chatInput.text
                            }));
                            chatInput.clear();
                        }

                        background: Rectangle {
                            anchors.fill: parent
                            color: sendButton.hovered ? ThemeManager.theme.color("success") : ThemeManager.theme.color("success", "light")
                            border.color: ThemeManager.theme.color("success", "light")
                            border.width: 1
                            radius: 4.0
                        }
                        HoverHandler {
                            acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                            cursorShape: Qt.PointingHandCursor
                        }
                    }
                }
            }
        }
    }

    footer: ChatPageFooter {
        id: chatPageFooter
        username: root.chatClientManager.user.username
    }
}
