#include "Server.h"

Server::Server() : serverSocket(INVALID_SOCKET), clientSocket(INVALID_SOCKET), countOfClients(0) {}
Server::~Server()
{
    closeServer();
}

int Server::createSocket()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET)
    {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    return 0;
}

void Server::assignServerAddress()
{
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;
    memset(&(server.sin_zero), 0, 8);
}

int Server::bindSocketAddress()
{
    int result = ::bind(serverSocket, (sockaddr *)&server, sizeof(server));
    if (result == SOCKET_ERROR)
    {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

void Server::closeServer()
{
    if (serverSocket != INVALID_SOCKET)
    {
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

    std::cout << "Listening on socket..." << std::endl;

    while (true) {
        int clientLen = sizeof(client);
        SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&client, &clientLen);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }

        std::thread t(&Server::handleClient, this, clientSocket);
        t.detach();
    }

    return true;
}

SOCKET Server::getSocketHandler()
{
    return serverSocket;
}

void Server::handleCtrlC(int signal)
{
    std::cout << "Server shutting down..." << std::endl;
    for (auto &client : collectionOfClients)
    {
        closesocket(client.socket);
    }
    closesocket(serverSocket);
    WSACleanup();
    exit(signal);
}

int Server::listenFunction()
{
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "Listening on socket..." << std::endl;
    return 0;
}

void Server::handleClient(SOCKET clientSocket)
{
    DatabaseManager databaseManager;
    ClientRequestHandler requestHandler(databaseManager);
    char buffer[256];

    while (true)
    {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0)
        {
            closesocket(clientSocket);
            break;
        }

        buffer[bytesReceived] = '\0';
        std::string request(buffer);

        if (request.substr(0, 10) == "loginUser:")
        {
            std::string email = request.substr(10);
            databaseManager.connect();
            bool loginSuccess = databaseManager.loginUser(email);
            std::string response = loginSuccess ? "Login successful" : "Login failed";

            send(clientSocket, response.c_str(), response.size(), 0);

            if (loginSuccess)
            {
                std::lock_guard<std::mutex>lock(clientsMutex);
                ClientsData clientData;
                clientData.id = countOfClients++;
                clientData.socket = clientSocket;
                clientData.email = email; 
                collectionOfClients.push_back(clientData);
            }
        }
        else
        {
            std::lock_guard<std::mutex> lock(clientsMutex);
            auto it = std::find_if(collectionOfClients.begin(), collectionOfClients.end(),
                                   [clientSocket](const ClientsData &data)
                                   { return data.socket == clientSocket; });

            if (it != collectionOfClients.end())
            {
                requestHandler.processRequest(request, clientSocket, it->id);
            }
            else
            {
                std::string response = "Unauthorized request";
                send(clientSocket, response.c_str(), response.size(), 0);
            }
        }
    }
}

void Server::endConnection(int id)
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    auto it = std::find_if(collectionOfClients.begin(), collectionOfClients.end(),
                           [id](const ClientsData &data)
                           { return data.id == id; });
    if (it != collectionOfClients.end())
    {
        std::cout << "Client " << id << " (" << it->email << ") left the server." << std::endl;
        closesocket(it->socket);
        collectionOfClients.erase(it);
    }
}
