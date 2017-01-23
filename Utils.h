#ifndef UTILS_H
#define UTILS_H
#include "Message.h"
class Task{
public:
    Message beginMessage;
    Message endMessage;
    char hashType[10];
    unsigned char hash[128];
    int hashLength=0;

    Task(char* begin,char* end):beginMessage(begin),endMessage(end)
    {}
    Task():beginMessage(" "),endMessage(" "){}
    Task(Message& begin, Message& end):beginMessage(begin),endMessage(end)
    {}
    void printStats()
    {
        printf("Search from '%s' to '%s', hash = ",beginMessage.getData(),endMessage.getData());
        for(int i=0;i<hashLength;i++)
            printf("%x ",hash[i]);
        printf("\nHash type = %s\n",hashType);
        fflush(stdout);
    }
};
struct ClientTask
{
    char hashType[10];
    unsigned char hash[128];
};
struct SlaveResponse
{
    bool decrypted;
    char password[24];
    // maybe when close somethig...
};
enum class SlaveState{
    Working,
    NotWorking
};

#endif
