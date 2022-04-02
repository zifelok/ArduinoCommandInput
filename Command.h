#ifndef Command_h
#define Command_h

#include "Arduino.h"

class Command
{
public:
    Command(char *str);
    Command(char *str, char *buffer, uint16_t bufferSize);
    uint8_t getCount();
    char *get(uint8_t i);

private:
    char *_buffer;
    uint16_t _bufferSize;
    uint16_t _inBuffer;
    uint8_t _count;
    Command(char *buffer, uint16_t bufferSize);
    void build(char *str, char *buffer, uint16_t bufferSize);
    bool put(char c);
    char getLast();
};

#endif