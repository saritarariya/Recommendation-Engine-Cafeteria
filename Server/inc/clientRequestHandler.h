#ifndef CLIENTREQUESTHANDLER_H
#define CLIENTREQUESTHANDLER_H

#include <string>
#include <winsock2.h>
#include "DatabaseManager.h"

class ClientRequestHandler
{
public:
    ClientRequestHandler(DatabaseManager &dbManager);
    void processRequest(const std::string &request, const SOCKET clientSocket, const int id);
    std::string receiveEmail(const SOCKET clientSocket);
    std::string receiveString(const SOCKET clientSocket);
    double receiveDouble(const SOCKET clientSocket);
    bool receiveBool(const SOCKET clientSocket);

private:
    DatabaseManager &dbManager;
};

#endif // CLIENTREQUESTHANDLER_H
