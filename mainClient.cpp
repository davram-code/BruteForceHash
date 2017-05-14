#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/md5.h>
#include "Message.h"
#include <string.h>
#include "Client.h"
#include <unistd.h>
#include "Config.h"
#define AES_BLOCK_SIZE 16
using namespace std;

int main(int argc, char **argv)
{
    if(argc!=2)
    {
        printf("Usage: ./mainClient <ip_server>");
        exit(1);
    }
    FILE *hash_in = fopen("hash.in", "rb");
    if (hash_in == NULL)
    {
        printf("FILE NOT FOUND!");
        return 0;
    }
    printf("\nCLientTaskSize:%d\n", sizeof(ClientTask));
    unsigned char hash[128];

    fread(hash, 1, 16, hash_in);
    fclose(hash_in);
    for (int i = 0; i < 16; i++)
        printf("%x ", hash[i]);
    fflush(stdout);
    Client *client = new Client();
    client->connectToServer(argv[1], CLIENT_PORT);
    client->setTask("MD5", hash);
    client->sendTaskToServer();
    client->waitResponse();

    return 0;
}
