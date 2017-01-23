#include <iostream>
#include "Utils.h"
#include "Slave.h"
#include "Config.h"
using namespace std;

int main()
{
    Slave slave(SERVER_IP, SLAVES_PORT);
    slave.connectToServer();
    if(slave.isConnected())
    {
        printf("Slave connected to %s on port %d!\n",SERVER_IP,SLAVES_PORT);
    }
    while (true)
    {
        slave.getTask();
        slave.printCurrentTask();
        slave.executeCurrentTask();
    }
}