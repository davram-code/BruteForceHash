#include "TaskSupplier.h"

TaskSupplier::TaskSupplier(int _taskComplexity,const char* _hashType,const unsigned char * _hash)
    :currentMessage()
{
    taskComplexity = _taskComplexity;
    strcpy(hashType,_hashType);
    memcpy(hash,_hash,128);
    if(strcmp(_hashType,"MD5")==0)
        hashLength=16;
}

Task* TaskSupplier::getNextTask()
{
    
    Message begin(currentMessage);
    currentMessage+=taskComplexity;
    Task* task = new Task(begin,currentMessage);
    strcpy(task->hashType,hashType);
    task->hashLength=hashLength;
    memcpy(task->hash,hash,128);
    task->hashLength=hashLength;
    return task;

}