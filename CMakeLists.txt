cmake_minimum_required(VERSION 3.16)

project(OnRabbleClient VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the right packages we need from Qt
find_package(Qt6 REQUIRED COMPONENTS Quick NetworkAuth WebSockets WebEngineQuick)

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
        qml/discovery/DiscoveryPage.qml
        qml/AuthBrowserPage.qml
        qml/ChatWindow.qml
        qml/discovery/RecentServersSelection.qml
        qml/discovery/ServerListItem.qml
        # QML ICONS
        qml/icons/CrossCircledIcon.qml
        qml/icons/PlusIcon.qml
        qml/icons/GlobeIcon.qml
        qml/icons/MagnifyingGlassIcon.qml
        # Util files
        AuthUtils.js
        ChatUtils.js
    SOURCES
        # Auth source files
        auth/authmanager.h auth/authmanager.cpp
        auth/authcore.h auth/authcore.cpp
        # Discovery source files
        discovery/discoverymanager.h discovery/discoverymanager.cpp
        discovery/discoverypayload.h discovery/discoverypayload.cpp
        discovery/discoverypayloadlistmodel.h discovery/discoverypayloadlistmodel.cpp
        discovery/discoverycore.h discovery/discoverycore.cpp
        # Websocket source files
        websocket/websocketmanager.h websocket/websocketmanager.cpp
        # ChatClient source files
        chat/chatclientmanager.h chat/chatclientmanager.cpp
        # Storage source files
        store/discoverystoremanager.h store/discoverystoremanager.cpp
        # System source files
        # Theme source files
        theme/theme.h theme/theme.cpp
        theme/colorpalette.h theme/colorpalette.cpp
        theme/thememanager.h theme/thememanager.cpp
    DEPENDENCIES
        QtCore
        QtWebEngine
        QML_FILES qml/discovery/components/DiscoveryHeader.qml
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
)

target_link_libraries(appOnRabbleClient
    PRIVATE Qt6::Quick Qt6::NetworkAuth Qt6::WebSockets Qt6::WebEngineQuick
)

include(GNUInstallDirs)
install(TARGETS appOnRabbleClient
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
