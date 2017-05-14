#include "Client.h"

bool Client::connectToServer(const char *ip, unsigned short port)
{

    serverIP = strdup(ip);
    serverPort = port;
    return connection->connect_to(ip, port);
}
Client::Client()
{
    connection = new connection_t();
}
void Client::setTask(const char *hashType, unsigned char *hash)
{
    memcpy(currentTask.hashType, hashType, 10);
    memcpy(currentTask.hash, hash, 128);
}
void Client::sendTaskToServer()
{
    connection->send_as(&currentTask);
    beginWorking = chrono::steady_clock::now();
}
void Client::waitResponse()
{
    SlaveResponse *serverResponse = new SlaveResponse;
    connection->receive_as(&serverResponse);
    if (serverResponse->decrypted == true)
    {
        printf("Password was decrypted: %s!\n", serverResponse->password);
        cout << (chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now()- beginWorking)).count() ;
        cout << " miliseconds!";
    }
    else
    {
        printf("Password wasn't decrypted!");
    }
}