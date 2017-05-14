#ifndef MESSAGE_H
#define MESSAGE_H
#define MAX_SIZE 24
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>
using namespace std;
class Message
{
    char data[MAX_SIZE];
public:
    Message(const Message& mes);
    Message(char* str);
    Message();
    unsigned char* getHash(const char* hashType);
    char* getData(){return data;}
    void operator++(int val);
    void operator+=(int val);
    friend ostream& operator<<(ostream& out,Message& m);
    bool operator !=(Message& mes);
};



#endif
