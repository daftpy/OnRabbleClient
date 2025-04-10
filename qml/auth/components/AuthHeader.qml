import QtQuick
import QtQuick.Layouts
import OnRabbleClient

Rectangle {
    id: headerRoot
    property alias errorText: errorText

    width: parent.width
    height: layout.height + 16.0 // Add some padding
    color: ThemeManager.theme.color("background", "dark")

    ColumnLayout {
        id: layout
        anchors.centerIn: parent // Center in the parent rectangle
        width: parent.width

        // The normal status bar, informing which server the user is connecting to
        Row {
            Layout.alignment: Layout.Center
            spacing: 6.0

            Text {
                id: titleLabel
                color: ThemeManager.theme.color("text")
                text: qsTr("Authenticating with") + " <b>" + payload.serverName + "</b>"
                textFormat: Text.RichText
            }
            LockOpenIcon {
                id: titleIcon
                color: ThemeManager.theme.color("text")
            }
            visible: errorText.text.length === 0 ? true : false
        }

        // The error status bar, informing the user of any errors during the auth process
        Row {
            id: errorMessage
            Layout.alignment: Layout.Center
            spacing: 6.0
            leftPadding: 12.0
            rightPadding: 12.0

            DangerIcon {
                anchors.verticalCenter: parent.verticalCenter
                id: errorIcon
                color: ThemeManager.theme.color("danger")
            }

            Text {
                id: errorText
                color: ThemeManager.theme.color("danger")
                width: Math.min(headerRoot.width - 15.0 - errorMessage.spacing - errorMessage.leftPadding * 2, textMetrics.width + 15.0)
                text: ""
                elide: Text.ElideRight
                maximumLineCount: 2
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                onTextChanged: {
                    textMetrics.text = text
                }
            }
            visible: errorText.text.length > 0 ? true : false
            TextMetrics {
                id: textMetrics
                font: errorText.font
            }
        }
    }
}
