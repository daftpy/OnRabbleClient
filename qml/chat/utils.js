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
