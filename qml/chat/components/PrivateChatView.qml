import QtQuick
import QtQuick.Layouts
import OnRabbleClient

Rectangle {
    id: root
    property string currentUsername: ""
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: ThemeManager.theme.color("background", "light")

    Text {
        anchors.centerIn: parent
        text: `Private window for ${currentUsername}`
        font.bold: true
        color: "white"
    }

    function selectUserView(payload) {
        // const index = chatViewInstantiator.channelToIndex[payload.name];
        // if (index !== undefined) {
        //     chatStack.currentIndex = index;
        //     currentChannelName = payload.name;
        //     console.log("ChatView: Switched to index", index, "for channel", payload.name);
        // } else {
        //     console.warn("ChatView: No view found for", channelName);
        // }
        currentUsername = payload.username;
    }
}
