#ifndef Server_H
#define Server_H

#include <list>
#include <vector>
#include <iostream>
#include "connection.h"
#include "TaskSupplier.h"
#include "Utils.h"
#include <pthread.h>
#include <chrono>

using namespace std;


void* __waitResponseFromSlaves(void* _params);
class Server
{
    list<Task*> unfinishedTasks;
    unsigned short slaveListeningPort;
    unsigned short clientListeningPort;
    int currentSlavesNumber;
    int maxSlaves;
    int currentSlaveNumber;
    int awaitConnectionsThread;
    ClientTask* clientTask;
    pthread_t* waitSlavesThread;
    pthread_t* waitResponseFromSlavesThread;
    pthread_t* checkActiveThread;
    connection_t *clientConnection;
    connection_t *slaveConnections;
    SlaveState* slavesState;
public:
    Server(int _maxSlaves, int _listeningSlavePort,int _listeningclientPort);
    void waitClient();
    void receiveTask();
    /*This creates a new thread*/
    void waitSlaves();
    void printCurrentTask();
    void putSlavesToWork(int complexityPerWorker);
    /*This creates a new thread*/
    void waitResponseFromSlaves();
    friend void* __waitResponseFromSlaves(void* params);
private:
    
    ~Server();

};

#endif