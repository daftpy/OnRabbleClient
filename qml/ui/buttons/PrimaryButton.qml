import QtQuick
import QtQuick.Controls.Basic
import OnRabbleClient

Button {
    required property string buttonText
    required property int radius
    id: root
    onClicked: discoveryManager.discover(urlInput.text);
    anchors.horizontalCenter: parent.horizontalCenter
    contentItem: Text {
        text: root.buttonText
        color: ThemeManager.theme.color("text", "highlight")
        font.pointSize: 8
        font.bold: true
    }

    background: Rectangle {
        anchors.fill: parent
        radius: root.radius && root.radius // Inherit parent radius
        color: root.hovered ? ThemeManager.theme.color("primary", "light") : ThemeManager.theme.color("primary")
        border.color: ThemeManager.theme.color("primary")
        border.width: 1
    }
    MouseArea {
        hoverEnabled: true
        anchors.fill: parent
        cursorShape: containsMouse ? Qt.PointingHandCursor : Qt.ArrowCursor

        onClicked: {
            root.clicked();
        }
    }
}
