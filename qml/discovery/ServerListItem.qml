import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import OnRabbleClient

Item {
    id: root
    required property string serverName
    required property int index

    signal clicked()

    implicitWidth: ListView.view.width
    implicitHeight: layout.implicitHeight + 10

    TapHandler {
        id: tapHandler
        acceptedButtons: Qt.LeftButton
        onTapped: root.clicked()
        cursorShape: Qt.PointingHandCursor
    }

    RowLayout {
        id: layout
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter
        spacing: 8

        Text {
            id: nameText
            font.weight: Font.Bold
            text: root.serverName
            elide: Text.ElideRight
            Layout.maximumWidth: 200
            color: ThemeManager.theme.color("slate", "12")
        }

        Text {
            id: msgText
            Layout.fillWidth: true
            text: "placeholder server motto message."
            elide: Text.ElideRight
            color: ThemeManager.theme.color("indigo", "12")
        }
    }
}
