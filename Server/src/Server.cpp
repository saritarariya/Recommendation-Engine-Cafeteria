#include "Server.h"

Server::Server() : serverSocket(INVALID_SOCKET), clientSocket(INVALID_SOCKET), countOfClients(0) {}

Server::~Server() {
    closeServer();
    
}

int Server::createSocket() {
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
    memset(&(server.sin_zero), 0, 8);
}

int Server::bindSocketAddress() {
    int result = ::bind(serverSocket, (sockaddr*)&server, sizeof(server));
    if (result == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
     return 0;
}

void Server::closeServer() {
      if (serverSocket != INVALID_SOCKET) {
        closesocket(serverSocket);
        serverSocket = INVALID_SOCKET;
    }
    WSACleanup();
}

bool Server::handleMultipleClients() {
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return false;
    }
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
    std::cout << "Listening on socket..." << std::endl;
    return 0;
}

void Server::handleClient(const SOCKET clientSocket, const int id) {
    DatabaseManager databaseManager;
    ClientRequestHandler requestHandler(databaseManager);
    char buffer[256];
    
    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) {
            endConnection(id);
            break;
        }
        buffer[bytesReceived] = '\0';
        std::string request(buffer);
        std::cout<<request<<std::endl;
        requestHandler.processRequest(request, clientSocket, id);
    }
}

void Server::endConnection(int id) {
    std::lock_guard<std::mutex> lock(clientsMutex);
    auto it = std::find_if(collectionOfClients.begin(), collectionOfClients.end(),
                           [id](const ClientsData& data) { return data.id == id; });
    if (it != collectionOfClients.end()) {
        std::cout << "Client " << id << " (" << it->email << ") left the server." << std::endl;
        closesocket(it->socket);
        collectionOfClients.erase(it);
    }
}
