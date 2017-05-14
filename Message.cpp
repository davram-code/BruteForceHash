#include "Message.h"
#include <math.h>
Message::Message(char *str)
{
    memset((void *)data, 0, MAX_SIZE);
    int size = strlen(str);
    strcpy(data,str);
}
void Message::operator++(int val)
{
    int carry = 0;
    int currentSize = strlen(data);
    bool shift = false;
    for (int i = currentSize - 1; i >= 0; i--)
    {
        if (i == 0 && data[i] == 0x7E)
        {
            shift = true;
            data[0] = ' ';
            break;
        }
        if (data[i] == 0x7E)
        {
            data[i] = 0x20;
        }
        else
        {
            data[i] = data[i] + 1;
            break;
        }
    }
    if (shift == false)
        return;
    // char *aux = new char(currentSize+1);
    // strcpy(aux, data);
    for (int j = currentSize - 1; j >= 0; j--)
    {
        data[j + 1] = data[j];
    }
    data[0] = ' ';
}
void Message::operator+=(int val)
{
    /*
    int stringValue = 0;
    int stringSize = strlen(data);
    int i = 0;
    char aux[MAX_SIZE];
    for (i = stringSize - 1; i >= 0; i--)
    {
        stringValue += (data[i] - 32) * pow(95, stringSize - i - 1);
    }
    stringValue += val;
    for (i = 0; i < MAX_SIZE && stringValue > 0; i++)
    {
            data[i] = stringValue % 95 + 32;
            stringValue /= 95;
        
    }
    strcpy(aux, data);
    for (int j = i - 1; j >= 0; j--)
    {
        data[i - j - 1] = aux[j];
    }*/
    int carry = 0;
    char aux;
    int i;
    int stringSize = strlen(data);
    char aux2[MAX_SIZE];
    strcpy(aux2, data);
    for (int j = 0; j < stringSize; j++)
    {
        data[j] = aux2[stringSize - j - 1];
    }
    for (i = 0; i < MAX_SIZE && (val || carry); i++)
    {
        if (data[i] != 0)
        {
            aux = data[i];
            data[i] = ((val + carry + data[i] - 32) % 95) + 32;
            carry = (val % 95 + aux +carry - 32) / 95;
            val /= 95;
        }
        else
        {
            data[i] = ((val) % 95 + carry) + 31;
            carry = (val % 95 + carry) / 95;
            val /= 95;
        }
    }
    strcpy(aux2, data);
    stringSize = i > stringSize ? i : stringSize;
    for (int j = 0; j < stringSize; j++)
    {
        data[j] = aux2[stringSize - j - 1];
    }
}
ostream &operator<<(ostream &out, Message &m)
{
    out << m.data;
    return out;
}
bool Message::operator!=(Message &mes)
{
    int result = strcmp(this->data, mes.data);

    if (result == 0)
        return false;
    return true;
}
Message::Message(const Message &mes)
{
    memcpy(this->data, mes.data, MAX_SIZE);
}
Message::Message()
{
    memset((void *)data, 0, MAX_SIZE);
    data[0] = ' ';
}
unsigned char *Message::getHash(const char *hashType)
{
    if (strcmp(hashType, "MD5") == 0)
    {
        unsigned char *unhashed = new unsigned char[strlen(data)];
        for (int i = 0; i < strlen(data); i++)
            unhashed[i] = (unsigned char)data[i];
        /*Have no idea why 1024, if you put less it will crash*/
        unsigned char *hash = new unsigned char[1024];
        MD5(unhashed, strlen(data), hash);
        delete[] unhashed;
        return hash;
    }
}