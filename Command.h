#ifndef Command_h
#define Command_h

#include "Arduino.h"

enum CommandStatus {
  successful,
  outOfBufferError,
  errorAtPosition
};

class Command
{
public:
    Command(char *str);
    Command(char *str, char *buffer, uint16_t bufferSize);
    uint8_t getCount();
    char *get(uint8_t i);
    CommandStatus getStatus();
    uint16_t getErrorPosition();

private:
    char *_buffer;
    uint16_t _bufferSize;
    uint16_t _inBuffer;
    uint8_t _count;
    CommandStatus _status;
    uint16_t _errorPosition;

    Command(char *buffer, uint16_t bufferSize);
    void build(char *str, char *buffer, uint16_t bufferSize);
    void put(char c);
    char getLast();
};

#endif