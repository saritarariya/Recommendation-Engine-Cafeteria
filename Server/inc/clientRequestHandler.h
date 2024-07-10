#ifndef CLIENTREQUESTHANDLER_H
#define CLIENTREQUESTHANDLER_H

#include <string>
#include <winsock2.h>
#include <vector>
#include <tuple>
#include "DatabaseManager.h"

class ClientRequestHandler
{
public:
    ClientRequestHandler(DatabaseManager &dbManager);
    void processRequest(const std::string &request, const SOCKET clientSocket, const int id);
    void sendResponse(const SOCKET clientSocket, const std::string &response);
private:
    DatabaseManager &dbManager;
};

#endif
