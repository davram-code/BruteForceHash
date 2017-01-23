#include <iostream>
#include<stdio.h>
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
    
    FILE* hash_in = fopen("hash.in","rb");
    if(hash_in==NULL)
    {
        printf("FILE NOT FOUND!");
        return 0;
    }
    printf("\nCLientTaskSize:%d\n",sizeof(ClientTask));
    unsigned char hash[128];

    fread(hash,1,16,hash_in);
    fclose(hash_in);
    for(int i=0;i<16;i++)
        printf("%x ",hash[i]);
    fflush(stdout);
    Client* client=new Client();
    client->connectToServer((const char*)"127.0.0.1",CLIENT_PORT);
    client->setTask("MD5",hash);
    client->sendTaskToServer();
    client->waitResponse();

    return 0;
}

// const char* x = "Hello";
    // unsigned char* y = new unsigned char[6];
    // for(int i=0;i<5;i++)
    //     y[i]=static_cast<unsigned char>(x[i]);
    // unsigned char* z =new unsigned char[100];
    
    

    // MD5(y,5,z);
    // for(int i=0;i<MD5_DIGEST_LENGTH;i++)
    //     printf("%02x ",z[i]);