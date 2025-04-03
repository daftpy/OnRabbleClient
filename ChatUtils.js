function openChatWindow(payload, token) {
    const chatClientManager = Qt.createQmlObject(`
        import OnRabbleClient 1.0;
        ChatClientManager {}
    `, Qt.application, "InjectedChatClientManager");

    chatClientManager.setAccessToken(token);
    chatClientManager.setDiscoveryPayload(payload);
    chatClientManager.connectToServer();

    const component = Qt.createComponent("qml/ChatWindow.qml");

    if (component.status === Component.Ready) {
        const win = component.createObject(null, {
            payload: payload,
            chatClientManager: chatClientManager
        });

        if (win) {
            win.show(); // or win.visible = true;
        }
    } else {
        console.error("ChatUtils: Failed to load ChatWindow.qml");
    }
}
