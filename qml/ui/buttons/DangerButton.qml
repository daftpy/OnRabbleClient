import QtQuick
import QtQuick.Controls.Basic
import OnRabbleClient

Button {
    required property string buttonText
    property int radius
    id: root
    anchors.horizontalCenter: parent.horizontalCenter

    contentItem: Text {
        text: "Cancel"
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
        font.bold: true
        color: ThemeManager.theme.color("text")
    }

    background: Rectangle {
        anchors.fill: parent
        radius: root.radius && root.radius // Inherit parent radius
        color: root.hovered ? ThemeManager.theme.color("danger", "light") : ThemeManager.theme.color("danger")
        border.color: ThemeManager.theme.color("danger")
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
