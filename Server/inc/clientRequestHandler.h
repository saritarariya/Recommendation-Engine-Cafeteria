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

private:
    DatabaseManager &dbManager;
};

#endif
