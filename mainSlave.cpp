#include <iostream>
#include "Utils.h"
#include "Slave.h"
#include "Config.h"
using namespace std;

int main(int argc, char** argv)
{
    if(argc!=2)
    {
        printf(".Usage: ./mainSlave <server_ip>");
        exit(1);
    }
    Slave slave(argv[1], SLAVES_PORT);
    slave.connectToServer();
    if(slave.isConnected())
    {
        printf("Slave connected to %s on port %d!\n",argv[1],SLAVES_PORT);
    }
    while (true)
    {
        slave.getTask();
        slave.printCurrentTask();
        slave.executeCurrentTask();
    }
}