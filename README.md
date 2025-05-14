# OnRabbleClient

**OnRabbleClient** is a modern, modular chat client built with **Qt 6.9**, combining **C++** for core logic and **QML** for a responsive UI. It connects to the [OnRabbleServer](https://github.com/daftpy/OpenRabbleServer) using a discovery-based architecture and OAuth2-secured WebSocket communication.

## ✨ Features

- **OAuth2 Authentication**  
  Secure user authentication via a token-based OAuth2 flow handled by the C++ `AuthManager`.

- **Server Discovery**  
  Automatically configures endpoints for OAuth2 and WebSocket chat communication using a `DiscoveryPayload`.

- **Recent Server Selection**  
  A `QAbstractListModel`-based view of previously connected servers, allowing users to reconnect quickly via a dynamic `ListView` driven by `DiscoveryModel`.

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

## 🔍 How It Works

1. The app starts at `DiscoveryPage`, where users can enter or select a server.

2. On successful discovery, it transitions to `AuthBrowserPage` for OAuth2 login.

3. When login completes, `openChatWindow(payload, token)` is called in QML, which invokes the C++ `ChatServerModel::openChatWindoow()` method:
   - Creates a `ChatClientManager`
   - Adds an entry to a model which tracks active chat clients
   - Instantiates a `ChatWindow` delegate

4. Each `ChatWindow` manages:
   - Its own `ChatClientManager` (handles connection)
   - Navigation between different pages and sub-views.
   - Message routing via its `MessageBroker`, exposed by the `ChatClientManager`

## 🔐 Security Considerations

- Access tokens are never stored in QML properties or displayed in UI.
- All token handling occurs in C++ and is passed via signals for one-time use.

## Developer Documentation

For detailed architecture, API usage, and extension guidelines, visit the **[Client Developer Guide](https://clientguide.onrabble.com)** to explore the available technical documentation for OnRabbleClient.

## 📃 License

This project is licensed under the **GNU General Public License v3.0 (GPLv3)**.  
You are free to redistribute and modify this software under the terms of the GPLv3, as published by the Free Software Foundation.

