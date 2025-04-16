cmake_minimum_required(VERSION 3.16)

project(OnRabbleClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the right packages we need from Qt
find_package(Qt6 REQUIRED COMPONENTS Quick Network NetworkAuth WebSockets WebEngineQuick)

qt_standard_project_setup(REQUIRES 6.9)
set(QT_QML_GENERATE_QMLLS_INI ON) # Generate QML types

qt_add_executable(appOnRabbleClient
    main.cpp
)

qt_add_qml_module(appOnRabbleClient
    URI OnRabbleClient
    VERSION 1.0
    QML_FILES
        # QML files
        Main.qml
        # Chat QML files
        qml/chat/ChatWindow.qml
        qml/chat/ChatPage.qml
        qml/chat/ChatErrorPage.qml
        qml/chat/components/ChatSidePanel.qml
        # Discovery QML files
        qml/discovery/DiscoveryPage.qml
        qml/discovery/components/RecentServersSelection.qml
        qml/discovery/components/ServerListItem.qml
        qml/discovery/components/DiscoveryHeader.qml
        # Auth QML files
        qml/auth/components/AuthHeader.qml
        qml/auth/AuthBrowserPage.qml
        # QML icon
        qml/ui/icons/CrossCircledIcon.qml
        qml/ui/icons/PlusIcon.qml
        qml/ui/icons/GlobeIcon.qml
        qml/ui/icons/MagnifyingGlassIcon.qml
        qml/ui/icons/DangerIcon.qml
        qml/ui/icons/LockOpenIcon.qml
        qml/ui/icons/PersonIcon.qml
        # QML button files
        qml/ui/buttons/PrimaryButton.qml
        qml/ui/buttons/DangerButton.qml
        qml/ui/icons/ChatIcon.qml
        # Util files
        qml/auth/utils.js
        qml/chat/utils.js

    SOURCES
        # Auth source files
        auth/authmanager.h auth/authmanager.cpp
        auth/authcore.h auth/authcore.cpp
        # Client source files
        client/clientuserpayload.h client/clientuserpayload.cpp
        # Discovery source files
        discovery/discoverymanager.h discovery/discoverymanager.cpp
        discovery/discoverypayload.h discovery/discoverypayload.cpp
        discovery/discoverypayloadlistmodel.h discovery/discoverypayloadlistmodel.cpp
        discovery/discoverycore.h discovery/discoverycore.cpp
        # Websocket source files
        websocket/websocketmanager.h websocket/websocketmanager.cpp
        # ChatClient source files
        chat/chatclientmanager.h chat/chatclientmanager.cpp
        chat/chatservermodel.h chat/chatservermodel.cpp
        chat/chatchannelpayload.h chat/chatchannelpayload.cpp
        chat/chatchannelpayloadmodel.h chat/chatchannelpayloadmodel.cpp
        # Messages source files
        messages/messagebroker.h messages/messagebroker.cpp
        # Storage source files
        store/discoverystoremanager.h store/discoverystoremanager.cpp
        # Theme source files
        theme/theme.h theme/theme.cpp
        theme/colorpalette.h theme/colorpalette.cpp
        theme/thememanager.h theme/thememanager.cpp
    DEPENDENCIES
        QtCore
        QtWebEngine
        QML_FILES qml/chat/components/ChatView.qml
        SOURCES chat/chatmessagepayload.h chat/chatmessagepayload.cpp
        SOURCES chat/chatmessagemodel.h chat/chatmessagemodel.cpp
        SOURCES chat/channelproxymodel.h chat/channelproxymodel.cpp
        QML_FILES qml/ui/icons/SendIcon.qml
        SOURCES user/userstatuspayload.h user/userstatuspayload.cpp
        SOURCES user/userstatusmodel.h user/userstatusmodel.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appOnRabbleClient PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appOnRabbleClient
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Set up the include/header directories
target_include_directories(appOnRabbleClient PRIVATE
    ${CMAKE_SOURCE_DIR}/auth
    ${CMAKE_SOURCE_DIR}/discovery
    ${CMAKE_SOURCE_DIR}/websocket
    ${CMAKE_SOURCE_DIR}/chat
    ${CMAKE_SOURCE_DIR}/store
    ${CMAKE_SOURCE_DIR}/theme
    ${CMAKE_SOURCE_DIR}/messages
    ${CMAKE_SOURCE_DIR}/client
    ${CMAKE_SOURCE_DIR}/user
)

target_link_libraries(appOnRabbleClient
    PRIVATE Qt6::Quick Qt6::Network Qt6::NetworkAuth Qt6::WebSockets Qt6::WebEngineQuick
)

include(GNUInstallDirs)
install(TARGETS appOnRabbleClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
