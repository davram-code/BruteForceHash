#ifndef CLIENT_H
#define CLIENT_H

#include <list>
#include <vector>
#include <iostream>
#include <string>
#include "Utils.h"
#include "connection.h"
using namespace std;

class Client
{
    char* serverIP;
    unsigned short serverPort;
    connection_t* connection;
    ClientTask currentTask;
public:
    Client();
    bool connectToServer(const char * ip, unsigned short port);
    void setTask(const char* hashType,unsigned char* hash);
    void sendTaskToServer();
    void waitResponse();

};  
#endif

// struct ClientTask
// {
//     char* hashType[10];
//     unsigned char* hash[128];
// };