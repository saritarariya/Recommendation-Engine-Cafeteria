#include "Client.h"

void Client::handleCtrlC(int signal)
{
    char str[MAX_LEN] = "#exit";
    send(clientSocket, str, sizeof(str), 0);
    exitFlag = true;
    tSend.detach();
    tReceive.detach();
    closesocket(clientSocket);
    std::cout << signal;
    exit(signal);
}

void Client::sendMessage(SOCKET clientSocket)
{
    while (1)
    {
        char str[MAX_LEN];
        std::cin.getline(str, MAX_LEN);
        send(clientSocket, str, sizeof(str), 0);
        if (strcmp(str, "#exit") == 0)
        {
            exitFlag = true;
            tReceive.detach();
            closesocket(clientSocket);
            return;
        }
    }
}

void Client::recvMessage(SOCKET clientSocket)
{
    char welcomemsg[MAX_LEN];
    int bytes_received1 = recv(clientSocket, welcomemsg, sizeof(welcomemsg), 0);
    if (bytes_received1 <= 0)
    {
        return;
    }
    std::cout << welcomemsg << std::endl;
    while (1)
    {
        if (exitFlag)
        {
            return;
        }
        char str[MAX_LEN];
        recv(clientSocket, str, sizeof(str), 0);
        if (strcmp(str, "#exit") == 0)
        {
            std::cout << "Sorry, server is not present anymore" << std::endl;
            exitFlag = true;
            tReceive.detach();
            closesocket(clientSocket);
            exit(2);
        }
        std::cout << str << std::endl;
        fflush(stdout);
    }
}

int Client::createSocket()
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    return 0;
}

int Client::connectSocket()
{
    int result = connect(clientSocket, (struct sockaddr *)&client, sizeof(client));
    if (result == SOCKET_ERROR)
    {
        std::cerr << "Unable to connect to server: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    return 0;
}

void Client::assignClientAddress(const std::string &ipAddress, int port)
{
    portNumber = port;
    std::string ipAdd;
    client.sin_family = AF_INET;
    client.sin_port = htons(portNumber);
    inet_pton(AF_INET, ipAddress.c_str(), &client.sin_addr);
}

void Client::sendRole(const std::string &role)
{
    char roleBuffer[MAX_LEN];
    strcpy_s(roleBuffer, role.c_str());
    send(clientSocket, roleBuffer, sizeof(roleBuffer), 0);
}

void Client::messageTransfer()
{
    std::thread t1(&Client::sendMessage, this, clientSocket);
    std::thread t2(&Client::recvMessage, this, clientSocket);
    tSend = std::move(t1);
    tReceive = std::move(t2);
    if (tSend.joinable())
    {
        tSend.join();
    }
    if (tReceive.joinable())
    {
        tReceive.join();
    }
}

bool Client::connectToServer()
{
    WSADATA wsaData;
    int wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaResult != 0) {
        std::cerr << "WSAStartup failed: " << wsaResult << std::endl;
        return 0;
    }
    try
    {
        assignClientAddress("127.0.0.1", 8080);
        createSocket();
        connectSocket();
    }
    catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
        return 0;
	}
    return 1;
}