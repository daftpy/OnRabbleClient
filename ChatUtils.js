function createChatClientManager(payload, token) {
    // Create a unique name to avoid conflicts when multiple ChatClientManager instances
    // are created and injected into the same parent (Qt.application)
    const uniqueName = `InjectedChatClientManager_${Date.now()}_${Math.random().toString(36).substr(2, 5)}`;
    const chatClientManager = Qt.createQmlObject(`
        import OnRabbleClient 1.0;
        ChatClientManager {}
    `, Qt.application, uniqueName);

    chatClientManager.setAccessToken(token);
    chatClientManager.setDiscoveryPayload(payload);
    chatClientManager.connectToServer();

    return chatClientManager;
}

function openChatWindow(payload, token) {
    const chatClientManager = createChatClientManager(payload, token);
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
