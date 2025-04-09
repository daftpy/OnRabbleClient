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
                    id: globeIcon
                    color: ThemeManager.theme.color("text")
                }

                Text {
                    text: "Discovery"
                    font.bold: true
                    font.pointSize: 10.0
                    height: globeIcon.height
                    verticalAlignment: Text.AlignVCenter
                    color: ThemeManager.theme.color("text")
                }
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                width: errorIcon.width + errorText.implicitWidth + spacing
                height: errorIcon.height
                spacing: 6.0
                DangerIcon {
                    id: errorIcon
                    color: ThemeManager.theme.color("danger")
                }

                Text {
                    id: errorText
                    text: ""
                    font.pointSize: 10.0
                    height: errorIcon.height
                    verticalAlignment: Text.AlignVCenter
                    color: ThemeManager.theme.color("danger")
                }
                visible: errorText.text.length > 0 ? true : false
            }
        }
    }
}
