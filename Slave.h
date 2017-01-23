#ifndef SLAVE_H
#define SLAVE_H
#include "Utils.h"
#include "connection.h"
#include "Message.h"
#include <openssl/md5.h>

class Slave
{
  private:
    Task *currentTask;
    connection_t *con;
    char *serverIP;
    short serverPort;
  public:
    Slave(const char *_serverIP, short _serverPort);
    void printCurrentTask(){currentTask->printStats();}
    void connectToServer();
    void getTask();
    void executeCurrentTask();
    bool isConnected() {return con->is_connected();}
};

#endif