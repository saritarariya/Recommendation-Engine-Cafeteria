#include "Server.h"

void Server::setName(const int id, const char* name) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (auto& client : collectionOfClients) {
        if (client.id == id) {
            strncpy_s(client.name, name, sizeof(client.name) - 1);
            client.name[sizeof(client.name) - 1] = '\0';
            break;
        }
    }
}

void Server::displayMessageOnServer(const std::string& str) {
    std::lock_guard<std::mutex> lock(printMutex);
    std::cout << str << std::endl;
}

void Server::broadcastMessage(const std::string& message, const int senderId) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (const auto& client : collectionOfClients) {
        if (client.id != senderId) {
            send(client.socket, message.c_str(), message.size(), 0);
        }
    }
}

void Server::endConnection(const int id) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    for (auto it = collectionOfClients.begin(); it != collectionOfClients.end(); ++it) {
        if (it->id == id) {
            closesocket(it->socket);
            collectionOfClients.erase(it);
            break;
        }
    }
}

void Server::handleClient(const SOCKET clientSocket, const int id) {
    char name[100];
    recv(clientSocket, name, sizeof(name), 0);
    setName(id, name);

    while (true) {
        char buffer[256];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            endConnection(id);
            break;
        }
        buffer[bytesReceived] = '\0';
        std::string message = "HYY yes you guys joined";
        displayMessageOnServer(message);
        broadcastMessage(message, id);
    }
}

int Server::createSocket() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    return 0;
}

void Server::assignServerAddress() {
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;
}

int Server::bindSocketAddress() {
    int result = bind(serverSocket, (struct sockaddr*)&server, sizeof(server));
    if (result == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

void Server::closeServer() {
    closesocket(serverSocket);
    WSACleanup();
}

bool Server::handleMultipleClients() {
    listen(serverSocket, SOMAXCONN);
    while (true) {
        int clientLen = sizeof(client);
        clientSocket = accept(serverSocket, (struct sockaddr*)&client, &clientLen);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            return false;
        }

        std::lock_guard<std::mutex> lock(clientsMutex);
        ClientsData clientData;
        clientData.id = countOfClients++;
        clientData.socket = clientSocket;
        collectionOfClients.push_back(clientData);
        std::thread t(&Server::handleClient, this, clientSocket, clientData.id);
        t.detach();
    }
    return true;
}

SOCKET Server::getSocketHandler() {
    return serverSocket;
}

void Server::handleCtrlC(int signal) {
    std::cout << "Server shutting down..." << std::endl;
    for (auto& client : collectionOfClients) {
        closesocket(client.socket);
    }
    closesocket(serverSocket);
    WSACleanup();
    exit(signal);
}

int Server::listenFunction() {
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}
