#include "Server.h"

Server::Server(int _maxSlaves, int _listeningPort, int _listeningclientPort)
    : maxSlaves(_maxSlaves), slaveListeningPort(_listeningPort), clientListeningPort(_listeningclientPort) //10000 is task complexity, change later?
{
    clientConnection = new connection_t();
    slaveConnections = new connection_t[maxSlaves];
    clientTask = nullptr;
    slavesState = new SlaveState[maxSlaves];
    for (int i = 0; i < maxSlaves; i++)
        slavesState[i] = SlaveState::NotWorking;
}
void Server::waitClient()
{
    clientConnection->await_connection_on(clientListeningPort);
}

void Server::waitSlaves()
{
    waitSlavesThread = connection_t::await_multiple_connections(slaveConnections, maxSlaves, slaveListeningPort);
}
void Server::receiveTask()
{
    //TODO: Watch for memory leaks!
    if (clientTask != nullptr)
        delete clientTask;
    clientTask = new ClientTask();
    clientConnection->receive_as(&clientTask);
}
void Server::printCurrentTask()
{
    int i;
    printf("Tip hash: %s\n", clientTask->hashType);
    for (i = 0; i < 16; i++)
        printf("[%d]:%x\n", i, clientTask->hash[i]);
    printf("\n");
    fflush(stdout);
}
void Server::putSlavesToWork(int complexityPerWorker)
{
    bool anyFree;
    struct timespec tim; //We could do that!
    tim.tv_sec = 1;      //Or maybe signals?
    tim.tv_nsec = 0;

    //WARNING STRANGE CAST?
    TaskSupplier ts(complexityPerWorker, (const char *)(clientTask->hashType), (const unsigned char *)(clientTask->hash));
    while (true)
    {
        anyFree = false;
        for (int i = 0; i < maxSlaves; i++)
        {
            if (slaveConnections[i].is_connected() == true && slavesState[i] == SlaveState::NotWorking)
            {
                anyFree = true;
                Task *task = ts.getNextTask();
                printf("Sending task: [%s] [%s]\n", task->beginMessage.getData(), task->endMessage.getData());
                slaveConnections[i].send_as(task, sizeof(Task));
                slavesState[i] = SlaveState::Working;
            }
        }
        //        if (anyFree = false)
        //        {
        //
        //           nanosleep(&tim, NULL);
        //            printf("thread execute!\n");
        //        }
    }
}
void Server::waitResponseFromSlaves()
{
    pthread_t *new_thread = new pthread_t;
    int creation_status = pthread_create(new_thread, NULL, __waitResponseFromSlaves, (void *)this);

    if (creation_status)
    {
        std::cerr << "pthread_create() failed with error code " << creation_status << "\n";
        return;
    }

    waitResponseFromSlavesThread = new_thread;
}

/*This will run on a separate thread*/
void *__waitResponseFromSlaves(void *_params)
{
    Server *server = (Server *)_params;
    SlaveResponse *slaveResponse;
    bool *readySlave = new bool[server->maxSlaves];
    while (true)
    {
        connection_t::poll(server->slaveConnections, server->maxSlaves, 100, readySlave);
        for (int i = 0; i < server->maxSlaves; i++)
        {
            if (readySlave[i] == true)
            {
                slaveResponse = new SlaveResponse;
                server->slaveConnections[i].receive_as(&slaveResponse);
                if (slaveResponse->decrypted == true)
                {
                    printf("Password was found:%s", slaveResponse->password);
                    fflush(stdout);
                    server->clientConnection->send_as(slaveResponse);
                    delete slaveResponse;
                    return nullptr;
                }
                server->slavesState[i] = SlaveState::NotWorking;
                delete slaveResponse;
            }
        }
    }
    return nullptr;
}
