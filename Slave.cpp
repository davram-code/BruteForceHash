#include "Slave.h"
Slave::Slave(const char *_serverIP, short _serverPort)
{
    serverIP = strdup(_serverIP);
    serverPort = _serverPort;
    con = new connection_t();
    currentTask = nullptr;
}

void Slave::connectToServer()
{
    con->connect_to(serverIP, serverPort);
}
void Slave::getTask()
{
    if (currentTask)
    {
        delete currentTask;
        currentTask = nullptr;
    }
    con->receive_as(&currentTask);
}

void Slave::executeCurrentTask()
{
    Message *_currentMessage = new Message(currentTask->beginMessage);
    Message &currentMessage = *_currentMessage;

    if (strcmp(currentTask->hashType, "MD5") == 0)
    {
        printf("Current Task:[%s]->[%s]\n", currentTask->beginMessage.getData(), currentTask->endMessage.getData());
        while (currentMessage != currentTask->endMessage)
        {
            unsigned char *hashMessage = nullptr;
            hashMessage = currentMessage.getHash("MD5");
            //printf("Now trying: [%s]\n",currentMessage.getData());
            fflush(stdout);
            int i = 0;
            for (i = 0; i < MD5_DIGEST_LENGTH; i++)
            {
                if (hashMessage[i] != currentTask->hash[i])
                {
                    delete[] hashMessage;
                    hashMessage = nullptr;
                    break;
                }
            }
            /*All characters are identicall => this is th word we want*/
            if (i == MD5_DIGEST_LENGTH)
            {
                SlaveResponse *response = new SlaveResponse;
                response->decrypted = true;
                strcpy(response->password, currentMessage.getData());
                con->send_as(response, sizeof(SlaveResponse));
                delete response;
                if (hashMessage)
                {
                    delete[] hashMessage;
                    hashMessage = nullptr;
                }
                delete &currentMessage;
                return;
            }
            currentMessage++;
            if (hashMessage)
            {
                delete[] hashMessage;
                hashMessage = nullptr;
            }
        }
        SlaveResponse *response = new SlaveResponse;
        response->decrypted == false;
        con->send_as(response, sizeof(SlaveResponse));
        delete response;

        delete &currentMessage;
    }
}