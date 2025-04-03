function openChatWindow(payload, token) {
    const component = Qt.createComponent("qml/ChatWindow.qml");

    if (component.status === Component.Ready) {
        const win = component.createObject(null, {
            payload: payload,
            token: token
        });

        if (win) {
            win.show(); // or win.visible = true;
        }
    } else {
        console.error("ChatUtils: Failed to load ChatWindow.qml");
    }
}
