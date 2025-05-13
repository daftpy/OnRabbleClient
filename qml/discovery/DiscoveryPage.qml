import QtQuick 2.15
import QtQuick.Layouts 2.15
import QtQuick.Controls.Basic 2.15
import OnRabbleClient

/*!
    \qmltype DiscoveryPage
    \inherits Page
    \inqmlmodule OnRabbleClient
    \brief The initial page used to discover available OnRabble chat servers.

    DiscoveryPage presents the user with a text input to enter a discovery URL
    and a button to begin the lookup process. It manages user feedback for success
    or failure and emits a signal when a valid \l DiscoveryPayload is retrieved.

    On successful discovery, the page emits \l discoveryCompleted with the retrieved payload,
    allowing the application to initiate the authentication process (usually by
    pushing \l AuthBrowserPage onto a stack).

    The page also includes a footer area showing previously used servers via
    \l RecentServersSelection.

    \section1 Usage Example

    \qml
    DiscoveryPage {
        id: discoveryPage
        onDiscoveryCompleted: (payload) => {
            stackView.push(authPageComponent, { payload: payload });
        }
    }
    \endqml

    \section2 Properties

    \list
        \li \b urlInput (alias) — Exposes the internal \c TextInput for external interaction (e.g., clearing after authentication).
    \endlist

    \section2 Signals

    \list
        \li \b{discoveryCompleted(\l{DiscoveryPayload} payload)} — Emitted when a valid server configuration has been retrieved.
    \endlist

    \sa DiscoveryManager, AuthBrowserPage, ClientManager
*/

Page {
    id: root

    // Aliases
    property alias urlInput: urlInput // allows input to be cleared on authentication

    // Signals
    signal discoveryCompleted(var payload)

    header: DiscoveryHeader {
        id: header
    }

    Rectangle {
        anchors.fill: parent
        color: ThemeManager.theme.color("background", "dark")

        // Using the column layout to center the child column
        ColumnLayout {
            anchors.fill: parent

            Column {
                Layout.fillWidth: true
                spacing: 20.0
                Rectangle {
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width - (parent.width * 0.2)
                    height: urlInput.height
                    color: ThemeManager.theme.color("background")
                    border.color: urlInput.focus ? ThemeManager.theme.color("primary") : ThemeManager.theme.color("background", "lighter");
                    radius: 6.0

                    RowLayout {
                        width: parent.width

                        MagnifyingGlassIcon {
                            Layout.leftMargin: 8.0
                            color: ThemeManager.theme.color("text", "highlight")
                        }

                        TextInput {
                            id: urlInput
                            text: "Enter a discovery url"
                            Layout.fillWidth: true
                            padding: 8.0
                            color: ThemeManager.theme.color("text")
                            clip: true

                            onTextEdited: {
                                header.errorText.text = "";
                            }
                            onAccepted: {
                                discoveryManager.discover(urlInput.text);
                                urlInput.focus = false;
                            }
                        }
                    }
                }

                PrimaryButton {
                    buttonText: "Authenticate"
                    radius: 6

                    onPressed: {
                        discoveryManager.discover(urlInput.text);
                    }
                }
            }

        }
    }

    footer: RecentServersSelection {
        onServerSelected: (payload) => {
            console.log("Selected recent server:", payload.serverName)

            // Emit discoveryCompleted signal to start auth process
            discoveryCompleted(payload);
        }
    }

    DiscoveryManager {
        id: discoveryManager

        onDiscoverySuccess: (payload) => {
            console.log("DiscoveryManagerQML: Payload received -", payload);

            // Emit discoveryCompleted signal to start auth process
            discoveryCompleted(payload);
        }

        onDiscoveryFailed: (error) => {
            console.log("DiscoveryManagerQML: Discovery failed -", error);
            header.errorText.text = "discovery failed"
       }
    }
}
