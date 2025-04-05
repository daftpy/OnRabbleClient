import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    id: root
    // Required properties from the model
    required property string serverName
    required property int index // Used for model access or logic

    // Signals
    signal clicked()

    // Make the Items width follow the ListView
    implicitWidth: ListView.view.width

    // The Items height is determined by the layout
    implicitHeight: mouseArea.height


    MouseArea {
        id: mouseArea
        width: parent.width
        height: layout.implicitHeight + 10
        onClicked: root.clicked()
        cursorShape: Qt.PointingHandCursor
        hoverEnabled: true

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
                leftPadding: 4
            }

            Text {
                id: msgText
                Layout.fillWidth: true
                text: "Placeholder message."
                elide: Text.ElideRight
                rightPadding: 4
            }

        }

    }
}
