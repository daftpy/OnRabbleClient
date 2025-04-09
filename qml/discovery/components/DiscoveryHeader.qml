import QtQuick
import OnRabbleClient
/*
    The header for the DiscoveryPage
    Simply displays the title with an icon or a discovery error.
*/

Item {
    property alias errorText: errorText
    width: parent.width
    height: column.implicitHeight

    Rectangle {
        anchors.fill: parent
        color: ThemeManager.theme.color("background", "darker")


        Column {
            id: column
            width: parent.width
            padding: 8.0
            Row {
                spacing: 6.0
                anchors.horizontalCenter: parent.horizontalCenter
                visible: errorText.text.length > 0 ? false : true
                GlobeIcon {
                    anchors.verticalCenter: parent.verticalCenter
                    color: ThemeManager.theme.color("text")
                }

                Text {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Discovery"
                    font.bold: true
                    color: ThemeManager.theme.color("text")
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                width: errorLabel.implicitWidth + errorText.implicitWidth + spacing
                height: errorLabel.implicitHeight
                spacing: 3
                Text {
                    id: errorLabel
                    text: "Error"

                    font.bold: true
                    color: ThemeManager.theme.color("danger")
                }
                Text {
                    id: errorText
                    text: ""
                    color: ThemeManager.theme.color("danger")
                }
                visible: errorText.text.length > 0 ? true : false
            }
        }
    }
}
