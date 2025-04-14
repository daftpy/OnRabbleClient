import QtQuick
import QtQuick.Controls.Basic
import QtQuick.Layouts
import OnRabbleClient

Page {
    id: root
    required property ChatClientManager chatClientManager
    required property discoveryPayload payload
    property ChatMessageModel chatMessageModel: chatClientManager.messageModel

    objectName: "ChatPage"

    RowLayout {
        anchors.fill: parent
        spacing: 0
        ChatSidePanel {
            chatClientManager: root.chatClientManager
        }


        ColumnLayout {
            Layout.fillWidth: true
            Layout.preferredWidth: 600.0
            Layout.fillHeight: true
            spacing: 0

            ChatView {
                chatMessageModel: root.chatMessageModel
            }

            RowLayout {
                id: chatInputContainer
                Layout.fillWidth: true
                // Layout.fillHeight: true
                // Layout.preferredHeight: 150.0
                Layout.preferredHeight: chatInput.implicitHeight + 6.0
                Layout.maximumHeight: 100
                spacing: 0

                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: ThemeManager.theme.color("background", "lightest")
                    ScrollView {
                        anchors.fill: parent
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
                }

                Button {
                    id: sendButton
                    Layout.fillHeight: true
                    Layout.preferredWidth: 75.0
                    contentItem: Text {
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        text: "Send"
                        color: ThemeManager.theme.color("text", "highlight")
                        font.pointSize: 8
                        font.bold: true
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
                        color: sendButton.hovered ? ThemeManager.theme.color("primary", "light") : ThemeManager.theme.color("primary")
                        border.color: ThemeManager.theme.color("primary")
                        border.width: 1
                    }
                    HoverHandler {
                        acceptedDevices: PointerDevice.Mouse | PointerDevice.TouchPad
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }
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
}
