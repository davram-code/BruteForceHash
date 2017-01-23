#include <stdio.h>
#include"Message.h"
#include <stdlib.h>
#include "TaskSupplier.h"
#include <unistd.h>

using namespace std;
int main(int argc, char** argv)
{
    int i;

    Message y(" ");

    Task * task;
    TaskSupplier ts(100000,"MD5","h49eodlpleutikrn");
    while(true)
    {
        task=ts.getNextTask();
        printf("[%s]  [%s]\n",task->beginMessage.getData(),task->endMessage.getData());
       Message x=task->beginMessage;
       while(x!=task->endMessage)
       {
           x++;
           cout<<x<<endl;
       }
        fflush(stdout);
        delete task;
        sleep(1);
    }
    // for(int i=0;i<100000;i++)
    // {
    //     cout<<"["<<x<<"]"<<"\t"<<"["<<y<<"]"<<endl;
    //     y+=100000;
    //     sleep(1 );
    // }


}