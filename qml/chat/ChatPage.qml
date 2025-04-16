import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import OnRabbleClient

Page {
    id: root
    objectName: "ChatPage"
    required property ChatClientManager chatClientManager
    required property discoveryPayload payload

    property ChannelProxyModel chatChannelProxy: null
    property bool channelsReady: false

    Connections {
        target: chatClientManager

        // This is emitted by the chatClientManager after the activeChannels
        // have been received and the proxy models have been created to filter
        // the chat messages
        function onActiveChannelsReady(channels) {
            if (!channels || channels.length === 0) {
                console.warn("No channels received.");
                return;
            }

            const firstChannel = channels[0];
            const proxy = chatClientManager.proxyForChannel(firstChannel.name);

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
            currentChannelProxy: root.chatChannelProxy
            chatClientManager: root.chatClientManager

            onChannelSelected: (proxy) => {
                root.chatChannelProxy = proxy; // Update the PAGE's property
                chatPageFooter.activeChannelText.text = `# ${proxy.name}`;

                const index = chatViewInstantiator.channelToIndex[proxy.name];
                if (index !== undefined) {
                   chatStack.currentIndex = index;
                   console.log("Switched to stack index", index, "for", proxy.name);
                } else {
                   console.warn("No stack view found for", proxy.name);
                }
            }
        }


        ColumnLayout {
            Layout.fillWidth: true
            Layout.preferredWidth: 600.0
            Layout.fillHeight: true
            spacing: 0

            StackLayout {
                id: chatStack
                Layout.fillWidth: true
                Layout.fillHeight: true

                Instantiator {
                    // maps channelName to stackLayout index
                    property var channelToIndex: ({})
                    id: chatViewInstantiator
                    model: channelsReady ? chatSidePanel.channelModel : []
                    delegate: ChatView {
                        required property string name
                        chatMessageModel: chatClientManager.proxyForChannel(name)

                        Component.onCompleted: {
                            console.log("ChatView loaded for:", name);
                        }
                    }

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
