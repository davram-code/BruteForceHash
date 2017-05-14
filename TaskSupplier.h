#ifndef TASKSUPPLIER_H
#define TASKSUPPLIER_H
#define MAX_PASSWD_SIZE 24
#include "Message.h"
#include "Utils.h"
class TaskSupplier
{
    int taskComplexity;
    Message currentMessage;
    char hashType[10];
    unsigned char hash[128];
    int hashLength;
    int currentID=0;
public:
    TaskSupplier(int _taskComplexity,const char* _hashType,const unsigned char* _hash);
    Message getCurrentMessage(){return currentMessage;}
    /*WARNING: this returns an allocated message. Must use delete to avoid memory leaks*/
    Task* getNextTask();
};




#endif