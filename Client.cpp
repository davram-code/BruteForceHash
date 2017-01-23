#include"Client.h"

bool Client::connectToServer(const char * ip, unsigned short port)
{

    serverIP=strdup(ip);
    serverPort=port;
    return connection->connect_to(ip,port);
}
Client::Client()
{
    connection=new connection_t();
}
void Client::setTask(const char* hashType,unsigned char* hash)
{
    memcpy(currentTask.hashType,hashType,10);
    memcpy(currentTask.hash,hash,128);
}
void Client::sendTaskToServer()
{
    connection->send_as(&currentTask);
}
void Client::waitResponse()
{
    SlaveResponse* serverResponse=new SlaveResponse;
    connection->receive_as(&serverResponse);
    if(serverResponse->decrypted==true)
    {
        printf("Password was decrypted: %s!",serverResponse->password);
    }
    else
    {
        printf("Password wasn't decrypted!");
    }

}