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
        channelName: baseChatView.currentChannelName

        username: root.chatClientManager.user.username
    }
}
