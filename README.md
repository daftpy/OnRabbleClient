# OnRabbleClient

OnRabbleClient is a Qt-based chat client built with C++ and QML designed to interface with the [OnRabbleServer](https://github.com/daftpy/OpenRabbleServer). The client provides OAuth2-based authentication and discovery features, serving as a foundation for a modern chat application.

## Features

- **OAuth2 Authentication:**  
  Securely authenticates users using an OAuth2 flow.
  
- **Server Discovery:**  
  Discovers and configures endpoints required for authentication and chat communication.
  
- **QML-Based UI:**  
  Uses QML for a responsive and modern user interface.
  
- **Modular Architecture:**  
  Clean separation between core logic (e.g., authentication, discovery, and chat) and QML integration.

## Prerequisites

- **Qt 6.5**  
  Install from [Qt Downloads](https://www.qt.io/download).

- **CMake**  
  Ensure CMake is installed on your system.

- A C++ compiler supporting C++11 or later.

## License

This project is licensed under the GNU General Public License v3.0 (GPLv3).  
You are free to redistribute and modify this software under the terms of the GPLv3, as published by the Free Software Foundation.
