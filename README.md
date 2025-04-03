# OnRabbleClient

**OnRabbleClient** is a modern, modular chat client built with **Qt 6.9**, combining **C++** for core logic and **QML** for a responsive UI. It connects to the [OnRabbleServer](https://github.com/daftpy/OpenRabbleServer) using a discovery-based architecture and OAuth2-secured WebSocket communication.

## ✨ Features

- **OAuth2 Authentication**  
  Secure user authentication via a token-based OAuth2 flow handled by the C++ `AuthManager`.

- **Server Discovery**  
  Automatically configures endpoints for OAuth2 and WebSocket chat communication using a `DiscoveryPayload`.

- **WebSocket Chat Interface**  
  Real-time communication with OnRabbleServer using a secured WebSocket managed by `WebsocketManager`.

- **QML User Interface**  
  A modern, declarative UI built with Qt Quick Controls 2 and `StackView` navigation.

- **Modular C++ Architecture**  
  Clear separation between logic and UI:
  - `AuthManager`: Coordinates authentication and emits tokens securely.
  - `WebsocketManager`: Encapsulates WebSocket connection logic.
  - `ChatClientManager`: Bridges QML and backend logic for chat.

- **Token-Safe Design**  
  Access tokens are passed securely into C++ and are never exposed to QML properties or UI bindings. Tokens are handled transiently through signals and not persisted.

- **Server Discovery**  
  Automatically configures endpoints for OAuth2 and WebSocket chat communication using a `DiscoveryPayload`.

- **WebSocket Chat Interface**  
  Real-time communication with OnRabbleServer using a secured WebSocket managed by `WebsocketManager`.

- **QML User Interface**  
  A modern, declarative UI built with Qt Quick Controls 2 and `StackView` navigation.

- **Modular C++ Architecture**  
  Clear separation between logic and UI:
  - `AuthManager`: Coordinates authentication and emits tokens securely.
  - `WebsocketManager`: Encapsulates WebSocket connection logic.
  - `ChatClientManager`: Bridges QML and backend logic for chat.

## 🔧 Prerequisites

- **Qt 6.9** or newer (with QtQuick, QtWebSockets, QtWebEngineQuick, QtNetworkAuth modules)
- **CMake 3.15+**
- **Modern C++ compiler** (supporting C++17 or later)
- [OnRabbleServer](https://github.com/daftpy/OpenRabbleServer) instance running

### Qt Modules Required

Your Qt installation must include the following modules:

- QtQuick
- QtNetworkAuth
- QtWebSockets
- QtWebEngineQuick

You can verify this by inspecting your Qt installation:

- **Linux/macOS**: `$QT_DIR/lib/cmake/`
- **Windows**: `C:\Qt\6.9.0\<compiler>\lib\cmake\Qt6*`

Or use the Qt Maintenance Tool to add any missing modules.

## 🚀 Getting Started

You can build this project manually using CMake, or open it directly in **Qt Creator** (recommended).

### Qt Creator (Recommended)

1. Open the project folder in Qt Creator (`File > Open File or Project...`).
2. Select your desired **Qt Kit** (e.g., `Qt 6.9 MinGW 64bit` or `MSVC 2022 64bit`).
3. Qt Creator will automatically configure and build the project using CMake.
4. Press the **Run** button to launch the application.

### Manual Build

```bash
git clone https://github.com/your-username/OnRabbleClient.git
cd OnRabbleClient
mkdir build && cd build
cmake ..
cmake --build .
```

> You may need to set `CMAKE_PREFIX_PATH` to your Qt installation path if Qt modules are not detected.

## 🥪 Usage

1. The client starts at a **DiscoveryPage** to enter a server URL.
2. On discovery completion, it navigates to the **AuthBrowserPage**, which:
   - Loads the authorization URL in a `WebEngineView`
   - Emits `authorizationSucceeded(payload, token)` on success
3. `ChatUtils.js` creates and configures a `ChatClientManager` securely:
   ```js
   const chatClientManager = Qt.createQmlObject(`
       import OnRabbleClient 1.0;
       ChatClientManager {}
   `, Qt.application);
   chatClientManager.setAccessToken(token);
   chatClientManager.setDiscoveryPayload(payload);
   chatClientManager.connectToServer();
   ```
4. The manager is injected into `ChatWindow.qml` as a property. No token is stored or exposed in QML.
5. Enjoy a chat session over a secure websocket connection.

## 🔐 Security Considerations

- Access tokens are never stored in QML properties or displayed in UI.
- All token handling occurs in C++ and is passed via signals for one-time use.

## 📃 License

This project is licensed under the **GNU General Public License v3.0 (GPLv3)**.  
You are free to redistribute and modify this software under the terms of the GPLv3, as published by the Free Software Foundation.

See [LICENSE](./LICENSE) for more details.

