// creates an AuthBrowserPage and pushes it to the front of the stackView
function pushAuthPageWith(stackView, payload, handleLoginCompleted) {
    const component = Qt.createComponent("qml/AuthBrowserPage.qml");

    if (component.status === Component.Ready) {
        const page = component.createObject(stackView, {
            payload: payload
        });

        if (page) {
            // Connect the onLoginCompleted signal
            page.loginCompleted.connect((payload, token) => {
                stackView.pop();

                // If an onLoginCompleted handler is provided, call it
                if (handleLoginCompleted) {
                    handleLoginCompleted(payload, token);
                }
            });

            // Connect the onLoginCanceled signal
            page.loginCanceled.connect(() => {
                stackView.pop();
            });

            // Push the page to the front
            stackView.push(page);
        }
    }
}
