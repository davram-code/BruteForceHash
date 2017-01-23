#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include "Message.h"
#include "Server.h"
#include "Config.h"
using namespace std;

int main(int argc, char **argv)
{
    Server *server = new Server(MAX_SLAVES, SLAVES_PORT, CLIENT_PORT);
    /*Opens a new thread in which a slaves are waited to connect to server*/
    server->waitSlaves();
    /*Blocks until client connects*/
    server->waitClient();
    /*Blocks until receives task*/
    server->receiveTask();
    /*Print informations about current task*/
    server->printCurrentTask();
    /*Starts a new thread where check if slaves sent somenthing*/
    server->waitResponseFromSlaves();
    /*Give Tasks to slaves*/
    /*Runs in the main thread*/
    server->putSlavesToWork(TASK_COMPLEXITY);

    return 0;
}