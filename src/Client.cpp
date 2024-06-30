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
    
int Client::createSocket()
{
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0)
    {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    this->clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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

bool Client::verifyUser() {
    // Construct the request string with "login_user" followed by the email ID
    std::string request = "loginUser:" + mailID + '\0';  // Ensure null-termination

    // Send the request string to the server
    if (send(clientSocket, request.c_str(), request.size(), 0) == -1) {
        std::cerr << "Failed to send request" << std::endl;
        return false;
    }

    // Prepare buffer for receiving the response
    char response[MAX_LEN];
    int bytesReceived = recv(clientSocket, response, MAX_LEN - 1, 0);  // Reserve space for null terminator
    if (bytesReceived <= 0) {
        std::cerr << "Failed to receive response or connection closed" << std::endl;
        return false;
    }

    // Null-terminate the response to safely convert to a string
    response[bytesReceived] = '\0';
    std::string verificationResponse = response;

    // Check if the response is "Verified"
    if (verificationResponse == "Login successful") {
        return true;
    } else {
        std::cerr << "Verification failed: " << verificationResponse << std::endl;
        return false;
    }
}

void Client::setEmail(const std::string& email) {
    mailID = email;
}

std::string Client::getEmail() {
    return mailID;
}

SOCKET Client::getClientSocket() {
    return clientSocket;
}
